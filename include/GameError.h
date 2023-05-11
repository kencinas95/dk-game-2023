#ifndef GAMEERROR_H
#define GAMEERROR_H

#include "main.h"

#ifndef DKERR
#define DKERR(x) DK_ERROR_##x
#endif

typedef enum
{
    // SDL Related
    DKERR(SDL_INIT) = 1000,
    DKERR(SDL_WINDOW_CREATION),

    // ASDASDAS
    DKERR(CANNOT_FIND_IMAGE),

    //asdasdasd
    DKERR(NO_CONSUMERS_DEFINED),

} DK_GameError;

void DK_GameErrorRaise(const DK_GameError, Boolean);

#endif