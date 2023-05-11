#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "main.h"
#include "GameResources.h"

void DK_GameWindowCreate();
void DK_GameWindowDestroy();
 
void DK_GameWindowClearDrawables();
int DK_GameWindowPrepareDrawable(const char *);
void DK_GameWindowRemoveDrawable(int);

void DK_GameWindowDraw(int, ...);


SDL_Renderer *DK_GameWindowRenderer();

#endif