#include <stdarg.h>

#include "GameError.h"
#include "GameWindow.h"
#include "GameConstants.h"
#include "GameLog.h"


static SDL_Window   *G_Window = NULL;
static SDL_Surface  *G_Surface = NULL;
static SDL_Renderer *G_Renderer = NULL;

SDL_Renderer *DK_GameWindowRenderer()
{
    return G_Renderer;
}

void DK_GameWindowCreate()
{
    G_Window = SDL_CreateWindow(
        DK_WINDOW_TITLE, 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        DK_WINDOW_START_WIDTH, 
        DK_WINDOW_START_HEIGHT,
        SDL_SWSURFACE);
    
    if (G_Window == NULL)
    {
        DK_GameErrorRaise(DK_ERROR_SDL_WINDOW_CREATION, 1);
    }
    
    G_Surface = SDL_GetWindowSurface(G_Window);
    G_Renderer = SDL_CreateRenderer(G_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);    
}


void DK_GameWindowDestroy()
{
    SDL_DestroyWindow(G_Window);
    free(G_Surface);
}

void DK_GameWindowDraw(int surfaces, ...)
{
    DK_GameLogDebug("%s@%d :: Starting drawing...", __func__, __LINE__);
    
    SDL_RenderClear(G_Renderer);
    
    va_list ap;
    va_start(ap, surfaces);

    for (int i = 0; i < surfaces; i++)
    {
        DK_Drawable drawable = va_arg(ap, DK_Drawable);        
        if (drawable.texture == NULL)
        {
            DK_GameLogDebug("Creating texture for surface %p", drawable.surface);
            drawable.texture = SDL_CreateTextureFromSurface(G_Renderer, drawable.surface);
        }
                
        if (drawable.transform)
        {
            DK_GameLogDebug("%s@%d :: Transform %s - w: %d, h: %d", __func__, __LINE__, drawable.filename, drawable.transform_rect.w, drawable.transform_rect.h);
            SDL_RenderCopy(G_Renderer, drawable.texture, NULL, NULL);
        } else {
            DK_GameLogDebug("Not Transform...");
            SDL_RenderCopy(G_Renderer, drawable.texture, NULL, &drawable.rect);
        }
            
    }    
    SDL_RenderPresent(G_Renderer);
}