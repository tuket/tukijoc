#include<SDL/SDL.h>
#include<iostream>
#include<string>
#include<vector>
#include "aux.h"
#include "geometry/rectangle.h"
#include "geometry/circle.h"
#include "geometry/shape.h"

#ifndef SCENARIO_H
class Scenario;
#endif		/*	SCENARIO_H	*/

#ifndef TUKI_H
#define TUKI_H

#define NUM_SP 8;

enum SpriteCur{left1=0, left2, left3, leftAtt, right1, right2, right3, rightAtt};

class Tuki: public Rectangle{
	private:
		int counter;
		int startingLives;
		static Pos startingPos;
		static const char* files[];
		static const int velX=4;
		static const int velY=8;
		static const int radioOfDes=12;
		
		Speed speed;
		Scenario* scenario;
		std::vector<SDL_Surface*> sprites;
		SpriteCur cur;
		Pos distPosBeak(){return ( cur<4?Pos(0,14):Pos(16,14) );}
		
	public:
		std::vector<SDL_Surface*> *getSprites(){return &sprites;}
	
		void setStartingLives(const int startingLives){this->startingLives=startingLives;}
		int getStartingLives()const{return startingLives;}
	
		static void setStartingPos(const Pos sp){startingPos=sp;}
			static void setStartingPosX(const int x){startingPos.x=x;}
			static void setStartingPosY(const int y){startingPos.y=y;}	
			
		static Pos getStartingPos(){return startingPos;}
			static int getStartingPosX(){return startingPos.x;}
			static int getStartingPosY(){return startingPos.y;}
	
		Speed getSpeed()const{return speed;}
			int getSpeedX()const{return speed.x;}
			int getSpeedY()const{return speed.y;}
		
		void setSpeed(const Speed speed){this->speed=speed;}
			void setSpeedX(const int x){speed.x=x;}
			void setSpeedY(const int y){speed.y=y;}
		
		bool canIBeThere(Pos nPos);
		void stop(){setSpeedX(0); cur=(SpriteCur)((cur<4)?0:4);}
		void moveRight(){setSpeedX(velX); cur=(SpriteCur)((cur+(cur<4?5:9))%8);}
		void moveLeft(){setSpeedX(-velX); cur=(SpriteCur)((cur+(cur<4?9:5))%8);}
		void jump(){setSpeedY(-velY);}
		
		void attack();
		void ref();
		
		void show(SDL_Surface* screen);
		
		Tuki(int x, int y, int w, int h, Scenario* scenario);
		Tuki(int w, int h, Scenario* scenario);
		~Tuki();
};

#endif		/*	TUKI_H	*/
