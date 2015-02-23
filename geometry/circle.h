#include "pos.h"
#include "shape.h"

#ifndef RECTANGLE_H
class Rectangle;
#endif		/*	RECTANGLE_H	*/

#ifndef CIRCLE_H
#define CIRCLE_H

class Circle : public Shape{
private:
	int radius;
public:
	int getRadius()const{return radius;}
	void setRadius(int radius){this->radius=radius;}
	
	bool containsPos(const Pos& pos)const{return (this->pos.x-pos.x)*(this->pos.x-pos.x)+(this->pos.y-pos.y)*(this->pos.y-pos.y)	<	radius*radius;}
	bool containsPos(const int x, const int y)const{return (this->pos.x-x)*(this->pos.x-x)+(this->pos.y-y)*(this->pos.y-y)	<	radius*radius;}
	bool intersection(const Shape& s)const;
	bool intersection(const Circle& c)const;
	bool intersection(const Rectangle& r)const;
	bool intersectionWithPos(Shape& s, const Pos p);
	
	Circle():Shape(0,0),radius(0){}
	Circle(Pos pos):Shape(pos),radius(0){}
	Circle(int radius):Shape(0,0),radius(radius){}
	Circle(Pos pos, int radius):Shape(pos),radius(radius){}
	Circle(int x, int y, int radius):Shape(x,y),radius(radius){}
};

#endif		/*	CIRCLE_H	*/
