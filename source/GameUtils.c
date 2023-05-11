#include "main.h"
#include "GameUtils.h"
#include "GameConstants.h"
#include "GameError.h"

static SDL_Color GetPixelColor(const SDL_Surface *, const uint8_t, const uint8_t);


SDL_Surface *DK_GameUtilsLoadImage(const char *imagepath, Boolean trasparency, uint8_t x, uint8_t y)
{
    SDL_Surface *surface = IMG_Load(imagepath);
    
    if (surface == NULL)
    {
        if ((surface = IMG_Load(DK_MEDIA_IMAGES__MISSING_DEFAULT)) == NULL)
        {
            DK_GameErrorRaise(DK_ERROR_CANNOT_FIND_IMAGE, 1);            
        }
    }

    if (trasparency)
    {        
        surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);
        SDL_Color color = GetPixelColor(surface, 0, 0);
        SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, color.r, color.g, color.b));
    }
    
    return surface;
}

Uint32 DK_GameUtilsGetRenderingRateFrame(Uint32 *nexttime, Uint32 fps)
{
    Uint32 now = SDL_GetTicks64();
    Uint32 result = 0;
    
    if (*nexttime > now)
    {    
        result = *nexttime - now;
    }

    *nexttime += fps;
    
    return result;
}

static SDL_Color GetPixelColor(const SDL_Surface *surface, const uint8_t x, const uint8_t y)
{
    const Uint8 bpp = surface->format->BytesPerPixel;
    Uint8 *pixel = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
    Uint32 data = *(Uint32*)pixel;
    SDL_Color color = {0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE};
    SDL_GetRGB(data, surface->format, &color.r, &color.g, &color.b);
    return color;
}