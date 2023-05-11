#include "GameMemory.h"
#include "GameUtils.h"
#include "GameConstants.h"
#include "GameResources.h"
#include "GameLog.h"
#include "GameStatus.h"

#define __init__(cls)   ((cls *)malloc(sizeof(cls)))


static DK_Drawable G_Images[] = {
    {
        .identifier     = 0,
        .filename       = DK_MEDIA_IMAGES__MISSING_DEFAULT,
        .transparent    = false
    },
    {
        .identifier     = 1,
        .filename       = DK_MEDIA_IMAGES__SPLASH_ART,
        .transparent  = false
    },
    {
        .identifier     = 2,
        .filename       = DK_MEDIA_IMAGES__MAIN_TITLE,
        .transparent    = false,
        .transform      = true,
        .transform_rect = {
            .x = 0,
            .y = 0,
            .w = DK_WINDOW_START_WIDTH,
            .h = DK_WINDOW_START_HEIGHT
        }
    }
};

static void GameMemory_LoadAllImages(SDL_Renderer *);

void DK_GameMemoryLoadAllResources(SDL_Renderer *renderer)
{    
    GameMemory_LoadAllImages(renderer);            
}

static void GameMemory_LoadAllImages(SDL_Renderer *renderer)
{    
    for (int i = 0; i < DK_MEDIA_IMAGES_COUNT; i++)
    {        
        G_Images[i].surface = DK_GameUtilsLoadImage(G_Images[i].filename, G_Images[i].transparent, 0, 0);
        G_Images[i].texture = SDL_CreateTextureFromSurface(renderer, G_Images[i].surface);
        DK_GameLogDebug("%s@%d :: Image loaded %s: %pS", __func__, __LINE__, G_Images[i].filename, G_Images[i].surface);
    }    
    DK_GameLogDebug("%s@%d :: All images files loaded in memory!", __func__, __LINE__);
}

DK_Drawable *DK_GameMemoryGetResourceImage(const char *key)
{
    DK_GameLogDebug("%s@%d :: Start searching for Resource image in memory: %s", __func__, __LINE__, key);

    for (int i = 0; i < DK_MEDIA_IMAGES_COUNT; i++)
    {
        DK_Drawable drawable = G_Images[i];        
        if (strcmp(drawable.filename, key) == 0)
        {            
            DK_GameLogDebug("%s@%d :: Resource image found: %s!", __func__, __LINE__, drawable.filename);
            return &G_Images[i];
        }
    }

    return NULL;
}