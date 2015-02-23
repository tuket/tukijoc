#include<SDL/SDL.h>
#include<vector>
#include "aux.h"
#include "geometry/circle.h"

#ifndef SCENARIO_H
class Scenario;
#endif		/*	SCENARIO_H	*/

#ifndef ROI_H
#define ROI_H

class Roi:public Circle{
public:
	static std::string roiFolder;
	static std::vector<SDL_Surface> images;
	static std::vector<Roi>* roi;
private:
	int id;
	int img;
	Scenario* scenario;

	Speed speed;
	int lives;
	
public:
	bool canIBeThere(Pos nPos);
	void show(SDL_Surface& screen);
	Speed getSpeed()const{return speed;}
		int getSpeedX()const{return speed.x;}
		int getSpeedY()const{return speed.y;}
		
	bool hit(const Shape& aod){return intersection(aod);}
	
	int decLives(){return --lives;}
	
	void ref();
	
	Roi(int img, int x, int y, int r, int lives, int sx, Scenario* scenario) : Circle(x,y,r), lives(lives), speed(sx,0), img(img), scenario(scenario){}
	
};

#endif		/*	ROI_H	*/
