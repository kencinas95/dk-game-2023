#include "main.h"
#include "GameError.h"
#include "GameLog.h"

void DK_GameErrorRaise(const DK_GameError error, Boolean breaks)
{        
    printf(SDL_GetError());
    switch(error)
    {
        case DK_ERROR_SDL_INIT:
        case DK_ERROR_SDL_WINDOW_CREATION:
        case DK_ERROR_CANNOT_FIND_IMAGE:
            fprintf(stderr, "SDL Internal Error described above.");
            break;
        default:
            fprintf(stderr, "Unknown Error %d...", error);
            break;
    }

    if (breaks)
    {
        DK_GameLogInfo("Exiting...");
        exit(-1);
    }
}