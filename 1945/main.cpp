#include "Engine.h"

int main(int argc, char* argv[]){

    Engine::GameLoop()->Init();

    while(Engine::GameLoop()->IsRunning()){
        Engine::GameLoop()->Events();
        Engine::GameLoop()->Update();
        Engine::GameLoop()->Render();
    }

    Engine::GameLoop()->Clean();
    return 0;
}
