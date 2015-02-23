#include "aux.h"

double getDistance(Pos p1, Pos p2){
	return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}

SDL_Surface* loadImg(const char* file){
	SDL_Surface* bad=SDL_LoadBMP(file);
	SDL_Surface* good=NULL;
	if(bad==NULL){
		std::cerr<<"loading: "<<file<<std::endl;
	}
	else{
		good=SDL_DisplayFormat(bad);
	}
	SDL_FreeSurface(bad);
	Uint32 colorkey = SDL_MapRGB( good->format, 0x00, 0xff,0xff );
	SDL_SetColorKey( good, SDL_SRCCOLORKEY, colorkey );
	return good;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination ) {
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface( source, NULL, destination, &offset );
}
