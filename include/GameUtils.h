#ifndef GAMEUTILS_H
#define GAMEUTILS_H

#include "main.h"

SDL_Surface *DK_GameUtilsLoadImage(const char *, Boolean, uint8_t, uint8_t);

Uint32 DK_GameUtilsGetRenderingRateFrame(Uint32*, Uint32);

#endif