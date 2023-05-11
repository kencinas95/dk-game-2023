#include "GameStatus.h"

// Global static 
static volatile DK_GameStatus G_Status = DK_GAME_STATUS_STARTUP;

Boolean DK_GameStatusCheck(DK_GameStatus status)
{
    return status == G_Status;
}

void DK_GameStatusUpdate(DK_GameStatus status)
{
    G_Status = status;
}