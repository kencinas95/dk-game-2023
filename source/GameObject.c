#include "main.h"
#include "GameConstants.h"
#include "GameObject.h"
#include "GameWindow.h"
#include "GameStatus.h"
#include "GameEvent.h"
#include "GameError.h"
#include "GameMemory.h"
#include "GameUtils.h"
#include "GameLog.h"

#define FPS     30

static void startup();
static void quit(void);


void DK_GameObjectInit()
{    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        DK_GameErrorRaise(DK_ERROR_SDL_INIT, true);
    }
    atexit(quit);
    
    DK_GameWindowCreate();    
    startup();
}

void DK_GameObjectMainLoop()
{                
    Uint32 nexttime = SDL_GetTicks64() + FPS;
    do
    {        
        DK_GameEventHandle();        
        if (DK_GameStatusCheck(DK_GAME_STATUS_RUNNING))
        {                                    
            DK_GameStateUpdate();
            DK_GameStateDraw();            
            SDL_Delay(DK_GameUtilsGetRenderingRateFrame(&nexttime, FPS));
        }        
    } while (DK_GameStatusCheck(DK_GAME_STATUS_RUNNING));    
}

void static startup()
{    
    DK_GameStatusUpdate(DK_GAME_STATUS_STARTUP);
    DK_GameLogDebug("%s@%d :: Starting up...", __func__, __LINE__);    
    
    DK_Drawable drawable = {
        .surface = DK_GameUtilsLoadImage(DK_MEDIA_IMAGES__SPLASH_ART, false, 0, 0),
        .transform = true,        
        .transform_rect = {
            .x = 0,
            .y = 0,
            .w = DK_WINDOW_START_WIDTH,
            .h = DK_WINDOW_START_HEIGHT
        },        
    };   
    drawable.texture = SDL_CreateTextureFromSurface(DK_GameWindowRenderer(), drawable.surface);

    DK_GameWindowDraw(1, drawable);        
    SDL_Delay(500);                    

    DK_GameMemoryLoadAllResources(DK_GameWindowRenderer());
    
    DK_GameStatusUpdate(DK_GAME_STATUS_RUNNING);    
    
}

void quit(void)
{    
    DK_GameLogInfo("%s@%d :: Game shutting down...", __func__, __LINE__);
    DK_GameWindowDestroy();
    SDL_Quit();    
}

