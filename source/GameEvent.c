#include "main.h"
#include "GameEvent.h"
#include "GameError.h"
#include "GameLog.h"

#define __init__(cls)   ((cls*)malloc(sizeof(cls)))

struct GameEventConsumerNode
{
    DKGameEvent event;
    DK_GameEventConsumer consumer;
    struct GameEventConsumerNode *next;
};

static struct GameEventConsumerNode *G_Consumers = NULL;

static void GameEventNotifyConsumers(DK_GameEvent event)
{
    DK_GameLogDebug("%s@%d :: Starting Event Notifictation for consumers...", __func__, __LINE__);
    if (G_Consumers == NULL)
    {
        DK_GameErrorRaise(DK_ERROR_NO_CONSUMERS_DEFINED, 1);
    }

    struct GameEventConsumerNode *node = G_Consumers;
    do
    {
        if (node->event == event.dk_event)
        {
            node->consumer(event);
        }        
        node = node->next;
    } while(node != NULL);
}

Boolean DK_GameEventRegisterConsumer(DKGameEvent event, DK_GameEventConsumer consumer)
{
    struct GameEventConsumerNode *node;
    
    if (G_Consumers == NULL)
    {
        G_Consumers = __init__(struct GameEventConsumerNode);
        node = G_Consumers;        
    } else {
        while(node->next != NULL)
        {
            node = node->next;
        }        
        node->next = __init__(struct GameEventConsumerNode);
        node = node->next;        
    }

    node->consumer = consumer;
    node->event = event;
    node->next = NULL;

    return 0;
}

Boolean DK_GameEventHandle()
{
    SDL_Event       sdl_event;    
    if(SDL_PollEvent(&sdl_event))
    {
        DK_GameEvent    dk_event = { 
            .sdl_event = sdl_event
        };

        if (sdl_event.type == SDL_QUIT)
        {
            dk_event.dk_event = DK_GAME_EVENT_QUIT;
            DK_GameLogDebug("%s@%d :: QUIT Event.", __func__, __LINE__);            
        }
        else if (sdl_event.type == SDL_KEYDOWN)
        {
            dk_event.dk_event = DK_GAME_EVENT_USER_KEY_PRESS;
            DK_GameLogDebug("%s@%d :: USER KEY PRESS Event.", __func__, __LINE__);
        }
        else
        {
            // Nothing...
            DK_GameLogDebug("%s@%d :: No major event found.", __func__, __LINE__);
            return true;
        }

        GameEventNotifyConsumers(dk_event);
        if (dk_event.dk_event == DK_GAME_EVENT_QUIT)
        {
            return false;
        }
    }

    return true;
}
