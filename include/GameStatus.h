#ifndef GAMESTATUS_H
#define GAMESTATUS_H

#include "main.h"

typedef enum
{
    DK_GAME_STATUS_STARTUP,
    DK_GAME_STATUS_LOADING_RESOURCES,    
    DK_GAME_STATUS_RUNNING,
    DK_GAME_STATUS__BROKEN,
    DK_GAME_STATUS_QUIT,
} DK_GameStatus;


void DK_GameStatusUpdate(DK_GameStatus);

Boolean DK_GameStatusCheck(DK_GameStatus);

#endif