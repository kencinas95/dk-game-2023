#ifndef SDL_MAIN_HANDLED
#define SDL_MAIN_HANDLED
#endif

#include "main.h"
#include "GameObject.h"

int main(int argc, char *argv[])
{ 
    DK_GameObjectInit();
    DK_GameObjectMainLoop();
    return EXIT_SUCCESS;
}