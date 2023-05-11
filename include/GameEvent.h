#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include "main.h"

#define DKEVENT(x)      DK_GAME_EVENT_##x

typedef enum 
{
    DKEVENT(QUIT),
    DKEVENT(USER_KEY_PRESS),
} DKGameEvent;

typedef struct
{
    DKGameEvent     dk_event;
    SDL_Event       sdl_event;
} DK_GameEvent;

typedef void (*DK_GameEventConsumer)(DK_GameEvent event);

Boolean DK_GameEventRegisterConsumer(DKGameEvent, DK_GameEventConsumer);

Boolean DK_GameEventHandle();

#endif