#include "roi.h"
#include "scenario.h"
#include<string>
#include<iostream>

using namespace std;

string Roi::roiFolder="roi/";

bool Roi::canIBeThere(Pos nPos){
	scenario->canBeThere(nPos,*this);
}

void Roi::ref(){
	Pos nPos(getPos().x+speed.x, getPos().y);
	if(canIBeThere(nPos))speed.x=-(speed.x);
	else setPos(nPos);
}

