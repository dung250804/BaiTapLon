#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"


int main(int argc, char* args[])
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;

	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

	RenderWindow window("GAME v1.0", 1280, 720);

	SDL_Texture* testTex = window.loadTexture("Graphics/moveRight.png");



    std::vector<Entity> entitiees = {Entity(Vector2f(0, 0), testTex),
                         			 Entity(Vector2f(50, 0), testTex),
                          			 Entity(Vector2f(100, 0), testTex),
                          			 Entity(Vector2f(150, 0), testTex)};
    {
	    Entity wilson(Vector2f(100, 50), testTex);

	    entitiees.push_back(wilson);

	}



	bool gameRunning = true;

	SDL_Event event;

	const float timeStep = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	while (gameRunning)
	{
	    int startTicks = SDL_GetTicks();

	    float newTime = utils::hireTimeInSeconds();
	    float frameTime = newTime - currentTime;

	    currentTime = newTime;

	    accumulator += frameTime;

	    while(accumulator >= timeStep)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                    gameRunning = false;
            }

            accumulator -= timeStep;
        }

        const float alpha = accumulator / timeStep;

		window.clear();


		for (Entity& e : entitiees)
		{
			window.render(e);
		}

		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;

		if(frameTicks < 1000 / SDL_RENDERER_PRESENTVSYNC)
            SDL_Delay(1000 / SDL_RENDERER_PRESENTVSYNC - frameTicks);

	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}
