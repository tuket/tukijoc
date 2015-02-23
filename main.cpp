#include<stdio.h>
#include<SDL/SDL.h>
#include "scenario.h"
#include "tuki.h"
#include "roi.h"
#include "aux.h"
#include "tile.h"
using namespace std;


int main(){
	bool rightP=false;
	bool leftP=false;
	SDL_Rect screenR={0, 0, 480, 320};
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )	return false;    
	SDL_Surface* screen = SDL_SetVideoMode( 480, 320, 0, SDL_ANYFORMAT);
	SDL_WM_SetCaption( "Tukijoc", NULL );
	Scenario scenario("1",screenR,screen);
	Tuki tuki(11,21,&scenario);
	scenario.addTuki(&tuki);
	SDL_Event event;
	bool end=false;
	while(!end){
		
		scenario.ref();

		scenario.show();
		tuki.show(screen);
		apply_surface(60,60,(*tuki.getSprites())[0],screen);
		SDL_Flip(screen);
		while( SDL_PollEvent( &event ) ){
			if( event.type == SDL_KEYDOWN ){
        		switch( event.key.keysym.sym ){
				    case SDLK_UP:
				    	tuki.jump();
				    	break;
				    case SDLK_LEFT: 
				    	if(rightP)tuki.stop();
				    	else tuki.moveLeft();
				    	leftP=true;
				    	break;
				    case SDLK_RIGHT: 
				    	if(leftP)tuki.stop();
				    	else tuki.moveRight();
				    	rightP=true;
				    	break;
				    case SDLK_SPACE:
				    	tuki.attack();
				    	break; 
        		}
    		}	
			else if( event.type == SDL_KEYUP ){
				switch( event.key.keysym.sym ){
				    case SDLK_LEFT: 
				    	if(!rightP)tuki.stop();
				    	else tuki.moveRight();
				    	leftP=false;
				    	break;
				    case SDLK_RIGHT: if(!leftP)
				    	tuki.stop();
				    	else tuki.moveLeft();
				    	rightP=false;
				    	break;    
        		}
			}
			else if( event.type == SDL_QUIT )	end = true;
		}
		SDL_Delay(100);
	}
	
	
	SDL_Quit();
    return 0;    
}
