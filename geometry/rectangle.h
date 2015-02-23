#include "pos.h"
#include "shape.h"

#ifndef CIRCLE_H
class Circle;
#endif		/*	CIRCLE_H */

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle : public Shape{
private:
	int width;
	int height;
public:
	int getWidth()const{return width;}
	int getHeight()const{return height;}
	
	void setWidth(int width){this->width=width;}
	void setHeight(int height){this->height=height;}
	
	bool containsPos(const Pos& pos)const;
	bool intersection(const Shape& s)const;
	bool intersection(const Rectangle& r)const;
	bool intersection(const Circle& c)const;
	bool intersectionWithPos(Shape& s, const Pos p);

	
	Rectangle():Shape(),width(0),height(0){}
	Rectangle(int w, int h):Shape(),width(w),height(h){}
	Rectangle(Pos p, int w, int h):Shape(p), width(w),height(h){}
	Rectangle(int x, int y, int w, int h):Shape(x,y), width(w), height(h){}
		
};

#endif		/*	RECTANGLE_H	*/
