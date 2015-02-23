#include "circle.h"
#include "rectangle.h"
#include "shape.h"

bool Circle::intersection(const Shape& s)const{
	if			(const Circle* c=dynamic_cast<const Circle*>(&s))return intersection(*c);
	else if		(const Rectangle* c=dynamic_cast<const Rectangle*>(&s))return intersection(*c);
	else return false;
}

bool Circle::intersection(const Circle& c)const{
	return (pos.x-c.getPos().x)*(pos.y-c.getPos().y) < (radius+c.getRadius())*(radius+c.getRadius());
}

bool Circle::intersection(const Rectangle& r)const{
	return r.intersection(*this);
}

bool Circle::intersectionWithPos(Shape& s, const Pos p){
	Pos aux=s.getPos();
	s.setPos(p);
	bool res= intersection(s);
	s.setPos(aux);
	return res;
}
