#include<fstream>
#include<iostream>
#include "scenario.h"
#include "roi.h"
#include "tuki.h"
#include "tile.h"
#include "./geometry/pos.h"
//#include "./geometry/rectangle.h"   
//#include "./geometry/circle.h"  
#include "./geometry/shape.h"                                            

using namespace std;

const string Scenario::mapsFolder="maps/";

void Scenario::show()const{
	int cx, cy;		//camera x, camera y
	cx=tuki->getPos().x-screenR.w/2;
	cy=tuki->getPos().y-screenR.h/2;
	
	/*
	cout << "SHOW" << endl << "------------" << endl;
	cout << "cx: " << cx << endl;
	cout << "cy: " << cy << endl;
	cout << "pWidth: " << pWidth << endl;
	cout << "pHeight: " << pHeight << endl;
	cout << "screenR.w" << screenR.w << endl;
	cout << "screenR.h" << screenR.h << endl;
	*/
	
	if(cx<0)	cx=0;
	else if(cx > getWidth()*32-screenR.w)	cx=getWidth()*32-screenR.w;
	
	if(cy<0)	cy=0;
	else if(cy > getHeight()*32-screenR.h)	cy=getHeight()*32-screenR.h;
	
	SDL_Rect raux;
	for(int j=cy/32; j < (cy+screenR.h)/32; j++){
		raux.y=j*32-cy;
		for(int i=cx/32; i<= (cx+screenR.w)/32 && i<mTile[0].size(); i++){
			raux.x=i*32-cx;
			apply_surface( raux.x, raux.y, mTile[j][i]->getImg(), screen );
		}
	}
	
}

bool Scenario::canBeThere(const Pos& newPos, const Shape& shape)const{
	if			(const Circle* aux=dynamic_cast<const Circle*>(&shape))return canBeThere(newPos,*aux);
	else if		(const Rectangle* aux=dynamic_cast<const Rectangle*>(&shape))return canBeThere(newPos,*aux);
	else{
	 cout<<"mec"<<endl;
	 return false;}
}

bool Scenario::canBeThere(const Pos& newPos, const Circle& shape)const{
	Circle aux;
	aux.setPos(newPos);
	Rectangle leftBorder(0, 0, -1, pHeight);
	Rectangle rightBorder(pWidth, 0, 1, pHeight);
	Rectangle topBorder(0, 0, pWidth, -1);
	Rectangle botBorder(0, pHeight, pWidth, 1);
	
	if(
		aux.intersection(leftBorder) ||
	 	aux.intersection(rightBorder) ||
	 	aux.intersection(topBorder) ||
	  	aux.intersection(botBorder)
	  )
	  return false;
	  
	for(int i=0; i<mTile.size(); i++)
		for(int j=0; j<mTile[i].size(); j++)
		{
			cout<<mTile[i][j]->isMaterial()<<"--"<<mTile[i][j]->intersection(aux)<<endl;
			if(mTile[i][j]->isMaterial() && mTile[i][j]->intersection(aux))return false;
		}
		
	return true;
}

bool Scenario::canBeThere(const Pos& newPos, const Rectangle& shape)const{
	Rectangle aux;
	aux.setPos(newPos);
	
	cout << "pos: " << aux.getPosX() << endl;
	
	Rectangle leftBorder(20, 0, 22, getHeight()*32);
	Rectangle rightBorder(getWidth()*32-30, 0, 22, getHeight()*32);
	Rectangle topBorder(0, 0, getWidth()*32, 22);
	Rectangle botBorder(0, getHeight()*32-1, getWidth()*32, 22);
	
	/*
	cout<<"aux.x"<<aux.getPos().x<<"aux.y"<<aux.getPos().y<<"aux.width"<<aux.getWidth()<<"aux.height"<<aux.getHeight()<<endl;
	cout<<"mTile.size()Rectangle"<<mTile.size()<<endl<<"aux.intersection(leftBorder)"<<aux.intersection(leftBorder)<<endl<<"aux.intersection(rightBorder)"<<aux.intersection(rightBorder)<<endl<<"aux.intersection(topBorder)"<<aux.intersection(topBorder)<<endl<<"aux.intersection(botBorder)"<<aux.intersection(botBorder)<<endl;
	*/
	
	if(aux.intersection(leftBorder) || aux.intersectionWithPos(rightBorder, rightBorder.getPos()) || aux.intersection(topBorder) || aux.intersection(botBorder)) return false;
	for(int i=0; i<mTile.size(); i++)
		for(int j=0; j<mTile[i].size(); j++){
			//cout << "pos = " << 
			//cout<<mTile[i][j]->isMaterial()<<"--"<<mTile[i][j]->intersection(aux)<<endl;
			if(mTile[i][j]->isMaterial() && aux.intersectionWithPos(*mTile[i][j],Pos(j*32,(i)*32)))return false;}
	return true;
}

void Scenario::destroyRoiInArea(Shape aod){
	for(int i=0;i<roi.size();i++)	
		if(roi[i].hit(aod)){
			if(roi[i].decLives()){
				roi.erase(roi.begin()+i);
			}
		}
}

Scenario::Scenario(char* map, SDL_Rect screenR, SDL_Surface* screen): screen(screen),screenR(screenR), pWidth(screenR.w),pHeight(screenR.h){
	ifstream read((mapsFolder+map).c_str(), ifstream::in);
	int widthTiles, heightTiles;
	Pos tukiStartingPos;
	read>>widthTiles;
	read>>heightTiles;
	read>>tukiStartingPos.x;
	Tuki::setStartingPosX(tukiStartingPos.x);
	read>>tukiStartingPos.y;
	Tuki::setStartingPosY(tukiStartingPos.y);
	read>>winTile.x;
	read>>winTile.y;
	int* mt=new int[heightTiles*widthTiles];
	for(int j=0;j<heightTiles;j++){
		for(int i=0;i<widthTiles;i++){
			read>>mt[j*widthTiles+i];
			cout<<mt[j*widthTiles+i];
		}
	cout<<endl;
	}
	string ti;	
	while(read>>ti)		//!read.eof()
	{
		string fileMat="tiles/";
		fileMat+=ti;
		ifstream fm(fileMat.c_str());
		int material;
		fm>>material;
		
		string fileImg="img/tiles/";
		fileImg+=ti;
		fileImg+=".bmp";
		cout<<fileImg<<endl;
		tiles.push_back(new Tile(fileImg.c_str(), material?true:false));
	}
	cout<<"heightTiles: "<<heightTiles<<endl;
	cout<<"widthTiles: "<<widthTiles<<endl;
	mTile= vector< vector<Tile*> >(heightTiles, vector<Tile*>(widthTiles));
	cout<<"mTile.size()"<<mTile.size()<<endl;
	cout<<"mTile[0].size()"<<mTile[0].size()<<endl;
	for(int j=0;j<heightTiles;j++)
		for(int i=0;i<widthTiles;i++){
			mTile[j][i]=tiles[ mt[j*widthTiles+i] ];
			mTile[j][i]->setPos(i*32, (heightTiles-j)*32);
			mTile[j][i]->setWidth(32);
			mTile[j][i]->setHeight(32);
		}
	cout<<"2mTile.size()"<<mTile.size()<<endl;
	cout<<"2mTile[0].size()"<<mTile[0].size()<<endl;
	read.close();
}

void Scenario::ref(){
	tuki->ref();
	for(int i=0; i<roi.size(); i++) roi[i].ref();
}

void Scenario::addRoi(Roi r){
	roi.push_back(r);
}


Scenario::~Scenario(){
		SDL_FreeSurface(screen);
		for(int i=0;i<tiles.size();i++) delete tiles[i];
	}
