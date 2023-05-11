#ifndef GAMERESOURCES_H
#define GAMERESOURCES_H

#include "main.h"
#include "GameConstants.h"

#define DK_GET_RESOURCE(x)  (x >> 0xFFFF >> 1)

typedef struct DK_Drawable_t
{    
    Uint16                      identifier;
    char                        filename[512];
    SDL_Surface                 *surface;     
    SDL_Texture                 *texture;
    Boolean                     transparent;    
    SDL_Rect                    rect;    
    Boolean                     transform;
    SDL_Rect                    transform_rect;
} DK_Drawable;

typedef struct
{
    char                        filename[128];
    Mix_Music                   *music;    
} DK_GameResourceMusic;

#endif