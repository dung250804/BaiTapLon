#include "Menu.h"

using namespace std;

Menu::Menu(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    screenW = SCREEN_WIDTH;
    screenH = SCREEN_HEIGHT;

    optionsNumber = 1;
    optionChoosen = 0;

    transVelo = 0;

    blinkTimes = 0;

    menuIsRunning = true;
    doneTransition = true;
    menuToInstruction = false;

    menuMusic = loadSong("sound/MenuTheme.mp3");
    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(menuMusic, -1);
    }

    frameTime = SDL_GetTicks();
}

Menu :: ~Menu()
{
}

void Menu::loadMenuIMG(SDL_Renderer* renderer)
{
    menuTexture = BaseObject::loadTexture("Menu/StartMenu1.png", renderer);

    play = BaseObject::loadTexture("button/play_button.png", renderer);
    playChoosen = BaseObject::loadTexture("button/play_button1.png", renderer);
    playPos.w = 180;
    playPos.x = (screenW - playPos.w) / 2;
    playPos.h = 50;
    playPos.y = (screenH / 2) + playPos.h;

    instruction = BaseObject::loadTexture("button/instructionButton.png", renderer);
    instructionChoosen = BaseObject::loadTexture("button/instructionButton1.png", renderer);
    instructionPos.w = 250;
    instructionPos.x = (screenW - instructionPos.w) / 2;
    instructionPos.h = 50;
    instructionPos.y = playPos.y + 2 * playPos.h;


    instruction1 = BaseObject::loadTexture("Menu/instruct_real1.png", renderer);
    instruction1Pos.w = 1280;
    instruction1Pos.x = screenW;
    instruction1Pos.h = 640;
    instruction1Pos.y = 0;

    instruction2 = BaseObject::loadTexture("Menu/instruct_real.png", renderer);
    instruction2Pos.w = 1280;
    instruction2Pos.x = instruction1Pos.x + instruction1Pos.w + 50;
    instruction2Pos.h = 640;
    instruction2Pos.y = 0;

    pointArrowRight = BaseObject::loadTexture("button/ArrowR1.png", renderer);
    pointArrowRightPos.w = 55;
    pointArrowRightPos.x = instructionPos.x - 75;
    pointArrowRightPos.h = 60;
    pointArrowRightPos.y = playPos.y - 5;

    pointArrowLeft = BaseObject::loadTexture("button/ArrowL1.png", renderer);
    pointArrowLeftPos = pointArrowRightPos;
    pointArrowLeftPos.x = instructionPos.x + instructionPos.w + 20;

    instructionReturn = BaseObject::loadTexture("button/instructionReturn.png", renderer);
    instructionReturnPos.w = 400;
    instructionReturnPos.x = (screenW - instructionReturnPos.w) / 2;
    instructionReturnPos.h = 15;
    instructionReturnPos.y = screenH - instructionReturnPos.h - 20;

    SDL_QueryTexture(instructionReturn, NULL, NULL, &instructionReturnRect.w, &instructionReturnRect.h);
    instructionReturnRect.h /= 2;
    instructionReturnRect.x = instructionReturnRect.y = 0;

    /*buttonInstruction = BaseObject::loadTexture("Menu/buttonInstruction.png", renderer);
    buttonInstructionPos.w = 600;
    buttonInstructionPos.x = (screenW - buttonInstructionPos.w) / 2;
    buttonInstructionPos.h = 40;
    buttonInstructionPos.y = screenH - buttonInstructionPos.h - 20;*/

    SDL_QueryTexture(buttonInstruction, NULL, NULL, &buttonInstructionRect.w, &buttonInstructionRect.h);
    buttonInstructionRect.h /= 2;
    buttonInstructionRect.x = buttonInstructionRect.y = 0;
}

void Menu::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        if (optionChoosen == 0) {
            if (e.key.keysym.sym == SDLK_DOWN) {
                pointArrowRightPos.y = pointArrowLeftPos.y = instructionPos.y - 5;
                optionsNumber = 2;
            }
            if (e.key.keysym.sym == SDLK_UP) {
                pointArrowRightPos.y = pointArrowLeftPos.y = playPos.y - 5;
                optionsNumber = 1;
            }
            if (e.key.keysym.sym == SDLK_SPACE) {
                optionChoosen = optionsNumber;
                if (optionChoosen == 1) blinkingTime = SDL_GetTicks();
                else if (optionChoosen == 2) {
                    menuToInstruction = true;
                    pointArrowRightPos.x = screenW;
                    pointArrowLeftPos.x = -pointArrowLeftPos.w;
                }
            }
        }
        else if (optionChoosen == 2) {
            if (doneTransition) {
                if (e.key.keysym.sym == SDLK_RIGHT) {
                    transVelo = -20;
                    doneTransition = false;
                }
                if (e.key.keysym.sym == SDLK_LEFT) {
                    transVelo = 20;
                    doneTransition = false;
                }
            }
            if (e.key.keysym.sym == SDLK_BACKSPACE) {
                optionChoosen = 0;
                instructionPos.y = playPos.y + 2 * playPos.h;
                instruction1Pos.x = screenW;
                instruction2Pos.x = instruction1Pos.x + instruction1Pos.w + 50;

                pointArrowRightPos.x = instructionPos.x - 75;
                pointArrowLeftPos.x = instructionPos.x + instructionPos.w + 20;
                pointArrowRightPos.y = pointArrowLeftPos.y = instructionPos.y - 5;
            }
        }
    }
}

void Menu::render(SDL_Renderer* renderer)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, menuTexture, NULL, NULL);

    if (optionChoosen == 0) {
        if (optionsNumber == 1) {
            SDL_RenderCopy(renderer, playChoosen, NULL, &playPos);
            SDL_RenderCopy(renderer, instruction, NULL, &instructionPos);
        }
        else if (optionsNumber == 2) {
            SDL_RenderCopy(renderer, play, NULL, &playPos);
            SDL_RenderCopy(renderer, instructionChoosen, NULL, &instructionPos);
        }
        SDL_RenderCopy(renderer, pointArrowLeft, NULL, &pointArrowLeftPos);
        SDL_RenderCopy(renderer, pointArrowRight, NULL, &pointArrowRightPos);
        SDL_RenderCopy(renderer, buttonInstruction, &buttonInstructionRect, &buttonInstructionPos);
        if (SDL_GetTicks() - frameTime >= 500) {
            buttonInstructionRect.y += buttonInstructionRect.h;
            frameTime = SDL_GetTicks();
        }
        if (buttonInstructionRect.y >= 2 * buttonInstructionRect.h) buttonInstructionRect.y = 0;
    }
    if (optionChoosen == 2) {

        pointArrowRightPos.y = pointArrowLeftPos.y = instruction1Pos.y + instruction1Pos.h / 2 - 30;

        if (instructionPos.y > 125) {
            instructionPos.y -= 20;
        }

        SDL_RenderCopy(renderer, instruction, NULL, &instructionPos);

        if (instruction1Pos.x > 0 && menuToInstruction) {
            instruction1Pos.x -= 40;
            instruction2Pos.x -= 40;
            if (instruction1Pos.x <= 0) {
                pointArrowRightPos.x = screenW - pointArrowRightPos.w - 50;
            }
        }

        if (instruction1Pos.x < 0) menuToInstruction = false;

        if (transVelo > 0) {
            if (instruction1Pos.x < 0) {
                instruction1Pos.x += transVelo;
                instruction2Pos.x += transVelo;
            }
            else if (instruction1Pos.x >= 0) {
                transVelo = 0;
                doneTransition = true;
                pointArrowRightPos.x = screenW - pointArrowRightPos.w - 50;
                pointArrowLeftPos.x = -pointArrowLeftPos.w;
            }
        }
        else if (transVelo < 0) {
            if (instruction2Pos.x > 0) {
                instruction1Pos.x += transVelo;
                instruction2Pos.x += transVelo;
            }
            else if (instruction2Pos.x <= 0) {
                transVelo = 0;
                doneTransition = true;
                pointArrowRightPos.x = screenW;
                pointArrowLeftPos.x = 50;
            }
        }
        SDL_RenderCopy(renderer, instruction1, NULL, &instruction1Pos);
        SDL_RenderCopy(renderer, instruction2, NULL, &instruction2Pos);

        SDL_RenderCopy(renderer, pointArrowLeft, NULL, &pointArrowLeftPos);
        SDL_RenderCopy(renderer, pointArrowRight, NULL, &pointArrowRightPos);

        SDL_RenderCopy(renderer, instructionReturn, &instructionReturnRect, &instructionReturnPos);
        if (SDL_GetTicks() - frameTime >= 500) {
            instructionReturnRect.y += instructionReturnRect.h;
            frameTime = SDL_GetTicks();
        }
        if (instructionReturnRect.y >= 2 * instructionReturnRect.h) instructionReturnRect.y = 0;
    }
    SDL_RenderPresent(renderer);
    if (optionChoosen == 1 && blinkTimes < 3 && SDL_GetTicks() - blinkingTime >= 100) {
        Mix_HaltMusic();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        blinkingTime = SDL_GetTicks();
        blinkTimes++;
    }
    if (blinkTimes >= 3) {
        menuIsRunning = false;
        SDL_Delay(1000);
    }
}

void DrawEndGameSelection(BaseObject gLoseTexture, SDL_Event* e, SDL_Renderer* gRenderer, bool& Play_Again)
{
    //gLoseTexture.Free();
    if (Play_Again)
    {
        bool End_Game = false;
        while (!End_Game)
        {
            while (SDL_PollEvent(e) != 0)
            {
                if (e->type == SDL_QUIT)
                {
                    Play_Again = false;
                    End_Game = true;
                }

                if (e->type == SDL_KEYDOWN)
                {
                    End_Game = true;
                    Play_Again = false;
                    /*
                    switch (e->key.keysym.sym)
                    {
                    case SDLK_SPACE:
                        End_Game = true;
                        break;
                    case SDLK_ESCAPE:
                        End_Game = true;
                        Play_Again = false;
                        break;
                    }
                    */
                }
            }

            gLoseTexture.Render(gRenderer, NULL);

            SDL_RenderPresent(gRenderer);
            gLoseTexture.Free();
        }
    }

}