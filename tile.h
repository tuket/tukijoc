#include<iostream>
#include<SDL/SDL.h>
#include "./geometry/rectangle.h"


#ifndef TILE_H
#define TILE_H

class Tile: public Rectangle{
private:
	SDL_Surface* img;
	bool material;
public:
	void setImg(const char* file){img=loadImg(file);}
	SDL_Surface* getImg(){return img;}
	
	void setMaterial(bool material){this->material=material;}
	bool isMaterial(){return material;}
	
	Tile(const char* file, bool material, int w=32, int h=32):material(material), Rectangle(w,h){img=loadImg(file);}
	~Tile(){SDL_FreeSurface(img);}
	
};

#endif		/*	TILE_H	*/
