#include <SDL.h>
#include <stdio.h>
#include "RenderWindow.h"

int main( int argc, char* args[] )
{
	RenderWindow window("1945 Demo", 1280,720);

    bool GameRunning = true;
    SDL_Event event;

    while(GameRunning){
        while( SDL_PollEvent( &event ) != 0 )
                {
                    if( event.type == SDL_QUIT )
                    {
                        GameRunning = false;
                    }
                }
    }

    window.CleanUp();
    SDL_Quit();

	return 0;
}


