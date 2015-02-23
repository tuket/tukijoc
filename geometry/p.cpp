#include "rectangle.h"
#include "shape.h"
#include<iostream>

using namespace std;

int main(){
	Rectangle u(30,30,1,1);
	Shape uu(u);
	Rectangle dos(0,0,1,50);
	cout<<dos.intersection(uu)<<endl;
}
