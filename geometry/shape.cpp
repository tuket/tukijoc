#include "shape.h"

bool Shape::intersection(const Shape& s)const{
	return false;
}

bool Shape::intersectionWithPos(Shape& s, const Pos p){
	Pos aux=s.getPos();
	s.setPos(p);
	bool res= intersection(s);
	s.setPos(aux);
	return res;
}
