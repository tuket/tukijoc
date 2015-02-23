#include<math.h>
#include<stdlib.h>
#include "pos.h"
#include "rectangle.h"
#include "circle.h"

bool Rectangle::containsPos(const Pos& pos)const{
	return (getPos().x < pos.x < getPos().x+width)	&&	(getPos().y < pos.y < getPos().y+height);
}

bool Rectangle::intersection(const Shape& s)const {
	if			(const Circle* c=dynamic_cast<const Circle*>(&s))return intersection(*c);
	else if		(const Rectangle* c=dynamic_cast<const Rectangle*>(&s))return intersection(*c);
	else return false;
}

bool Rectangle::intersection(const Rectangle& r)const {
	return 	(	((r.getPos().x<=pos.x) && (pos.x<=r.getPos().x+r.getWidth()))		||	((r.getPos().x<=pos.x+width) && (pos.x+width<=r.getPos().x+r.getWidth())	) )	&&
			(	((r.getPos().y<=pos.y) && (pos.y<=r.getPos().y+r.getHeight()))	||	((r.getPos().y<=pos.y+height) && (pos.y+height<=r.getPos().y+r.getHeight())) );
}
bool Rectangle::intersection(const Circle& c)const {
	return
		(
			( getPos().x<c.getPos().x && c.getPos().x<getPos().x+width			)	&&
			(
				( c.containsPos(c.getPos().x, getPos().y) 			)	||
				( c.containsPos(c.getPos().x, getPos().y+height) 	)
			)
		)||
		(
			( getPos().y<c.getPos().y && c.getPos().y<getPos().y+height			)	&&
			(
				( c.containsPos(c.getPos().y, getPos().x)			)	||
				( c.containsPos(c.getPos().y, getPos().x+width)		)
			)
		)||
		(
			c.containsPos(pos)								||
			c.containsPos((Pos){pos.x, pos.y+height})		||	
			c.containsPos((Pos){pos.x+width, pos.y})		||
			c.containsPos((Pos){pos.x+width, pos.y+height})
		);
}

bool Rectangle::intersectionWithPos(Shape& s, const Pos p){
	Pos aux=s.getPos();
	s.setPos(p);
	bool res= intersection(s);
	s.setPos(aux);
	return res;
}
