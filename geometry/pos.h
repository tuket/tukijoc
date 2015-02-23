#ifndef POS_H
#define POS_H

struct Pos{
	int x;
	int y;
	inline Pos operator+(const Pos& a){
		Pos c(a.x+x, a.y+y);
		return c;
	
	}
	Pos():x(0),y(0){}
	Pos(const Pos& pos):x(pos.x), y(pos.y){}
	Pos(const int x, const int y):x(x),y(y){}
};



#endif		/*	POS_H	*/
