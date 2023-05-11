#include "states/GameStateMainMenu.h"


void DK_GameRunnerMainMenuInit()
{

}

void DK_GameRunnerMainMenuEventHandler(SDL_Event event)
{
    switch(event.type)
    {
        case SDL_KEYDOWN:
            if (event.keysym.sym == SDLK_ESCAPE)
            {
                DK_GameStatusUpdate(DK_GAME_STATUS_QUIT);
            }
            break;
    }
}

void DK_GameRunnerMainMenuWindowDraw()
{

}