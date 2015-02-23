#include "pos.h"

#ifndef SHAPE_H
#define SHAPE_H

class Shape{
protected:
	Pos pos;
public:
	Pos getPos()const{return pos;}
		int getPosX()const{return pos.x;}
		int getPosY()const{return pos.y;}
	void setPos(const Pos& pos){this->pos=pos;}
	void setPos(const int x, const int y){pos.x=x;pos.y=y;}
		void setPosX(const int x){pos.x=x;}
		void setPosY(const int y){pos.y=y;}
	virtual bool intersection(const Shape& s)const;
	virtual bool intersectionWithPos(Shape& s, const Pos pos);
	
	Shape():pos(0,0){}
	Shape(const Pos& pos):pos(pos){}
	Shape(const int x,const  int y):pos(x,y){}
	~Shape(){}
};

#endif		/*	SHAPE_H	*/
