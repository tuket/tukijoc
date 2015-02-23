#include<iostream>
#include<SDL/SDL.h>
#include<math.h>
#include "geometry/pos.h"

#ifndef AUX_H
#define AUX_H


struct Speed{
	int x;
	int y;
	
	Speed(int x, int y):x(x), y(y){}
};

double getDistance(Pos p1, Pos p2);
SDL_Surface* loadImg(const char* file);
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );

#endif		/*	AUX_H */
