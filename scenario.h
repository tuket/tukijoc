#include<string>
#include<vector>
#include<iostream>
#include<SDL/SDL.h>
#include "aux.h"


#ifndef TUKI_H
class Tuki;
#endif		/*	TUKI_H	*/
#ifndef TILE_H
class Tile;
#endif		/*	TILE_H	*/
#ifndef ROI_H
class Roi;
#endif		/*	ROI_H	*/
#ifndef SHAPE_H
class Shape;
#endif		/*	SHAPE_H	*/
#ifndef CIRCLE_H
class Circle;
#endif		/*	CIRCLE_H	*/
#ifndef RECTANGLE_H
class Rectangle;
#endif		/*	RECTANGLE_H	*/



#ifndef SCENARIO_H
#define SCENARIO_H

class Scenario{

private:
	static const std::string mapsFolder;

private:
	SDL_Surface* screen;
	SDL_Rect screenR;		//={.x=0, .y=0, .w=480, .h=320};
	Tuki* tuki;
	std::vector<Roi> roi;
			//the set of tiles
	std::vector< std::vector<Tile*> > mTile;		//organization of tiles in the map
	int pWidth;
	int pHeight; 
	Pos winTile;
	
	
	
public:
	
	std::vector<Tile*> tiles;
	
	int getWidth()const{return mTile[0].size();}
	int getHeight()const{return mTile.size();}
	
	int getScreenWidth(){ return screenR.w; }
	int getScreenHeight(){ return screenR.h; }
	
	bool outOfLimits(const Pos pos)const{return pos.x<0 || pos.y <0 || pos.x>pWidth || pos.y>pHeight;}
	bool canBeThere(const Pos& pos, const Shape& shape)const;
	bool canBeThere(const Pos& pos, const Circle& shape)const;
	bool canBeThere(const Pos& pos, const Rectangle& shape)const;
	void destroyRoiInArea(Shape aoe);
	
	void addRoi(Roi r);
	void addTuki(Tuki* tuki){this->tuki=tuki;}
	
	void ref();
	void show()const;
	
	Scenario(char* map,SDL_Rect screenR, SDL_Surface* screen);
	~Scenario();
};

#endif		/*	SCENARIO_H	*/
