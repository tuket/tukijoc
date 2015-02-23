#include "tuki.h"
#include "scenario.h"
#include "aux.h"
#include<string>
#include<iostream>

using namespace std;

Pos Tuki::startingPos;

const char* Tuki::files[]={"img/tuki/left1.bmp","img/tuki/left2.bmp","img/tuki/left3.bmp","img/tuki/leftAtt.bmp",
									"img/tuki/right1.bmp","img/tuki/right2.bmp","img/tuki/right3.bmp","img/tuki/rightAtt.bmp"};

inline bool Tuki::canIBeThere(Pos nPos){
	scenario->canBeThere(nPos,*this);
}

void Tuki::attack(){
	Circle c(pos+distPosBeak(),5);
	scenario->destroyRoiInArea(c);
	cur=(SpriteCur)((cur<4)?3:7);
	counter=-30;
}


void Tuki::ref(){
	if(speed.x==0){
		cur=(SpriteCur)((cur<4)?0:4);
		counter=0;
	}
	else if(speed.x<0){
		counter++;
		if(counter==30){
			cur=(SpriteCur)((cur+1)%3);
			counter=0;
		}
	}
	else{
		counter++;
		if(counter==30){
			cur=(SpriteCur)(((cur+1-4)%3)+4);
			counter=0;
		}
	}
	
	cout << "tuki pos = " << pos.x << ", " << pos.y << endl;
	
	Pos newPosX(pos.x+speed.x, pos.y);
	Pos newPosY(pos.x, pos.y+speed.y);
	Pos newPosXY(pos.x+speed.x, pos.y+speed.y);
	if(canIBeThere(newPosXY)){
		setPos(newPosXY);
		(speed.y)++;
	}
	else if(canIBeThere(newPosX)){
		setPos(newPosX);
		speed.y=0;
	}
	else if(canIBeThere(newPosY)){
		setPos(newPosY);
		(speed.y)++;
	}
	else{
		speed.y=0;
	}
}

void Tuki::show(SDL_Surface* screen){

	int x, y;
	
	if(getPos().x < scenario->getScreenWidth()/2  ) x = getPos().x;
	else if( getPos().x > scenario->getWidth()*32 - scenario->getScreenWidth()/2 ) 
		x = scenario->getScreenWidth() - (scenario->getWidth()*32 - getPos().x);
	else x = scenario->getScreenWidth()/2;
	
	if(cur<3){
		apply_surface(x-10,getPos().y-21,sprites[cur],screen);
	}
	else if(cur>3 && cur!=7 ){
		apply_surface(x,getPos().y-21,sprites[cur],screen);
	}
	else if(cur==3){
		apply_surface(x-12,getPos().y-19,sprites[cur],screen);
	}
	else{	//cur==7
		apply_surface(x,getPos().y-19,sprites[cur],screen);
	}
}

Tuki::Tuki(int x, int y, int w, int h, Scenario* scenario):scenario(scenario), Rectangle(x,y,w,h), speed(0,0), cur(right1),startingLives(5), counter(0){
	for(int i=0;i<8;i++){
		sprites[i]= loadImg(files[i]);
	}
}

Tuki::Tuki(int w, int h, Scenario* scenario):scenario(scenario),Rectangle(Tuki::startingPos,w,h), speed(0,0), cur(right1),startingLives(5), counter(0){
	for(int i=0;i<8;i++){
		sprites.push_back(loadImg(files[i]));
	}
}

Tuki::~Tuki(){
	for(int i=0;i<8;i++){
		SDL_FreeSurface(sprites[i]);
	}
}
