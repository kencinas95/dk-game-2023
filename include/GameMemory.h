#ifndef GAMEMEMORY_H
#define GAMEMEMORY_H

#include "main.h"
#include "GameResources.h"

typedef struct DKGameMemoryEntry DK_GameMemoryEntry;
struct DKGameMemoryEntry
{
    unsigned long               hashkey;
    unsigned char               *key;
    DK_Drawable                 *value;
    DK_GameMemoryEntry          *next;
};

typedef struct
{
    DK_GameMemoryEntry  *entries;
    unsigned int        count;
} DK_GameMemoryStack;


DK_GameMemoryStack *DK_GameMemoryStackInit();
void DK_GameMemoryStackInsert(char *, DK_GameMemoryStack **);
DK_GameMemoryEntry *DK_GameMemoryGet(char *, DK_GameMemoryStack *);


#endif