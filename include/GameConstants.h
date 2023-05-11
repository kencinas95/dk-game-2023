#ifndef GAMECONSTANTS_H
#define GAMECONSTANTS_H

#include "main.h"

// Game Version
#define DK_GAME_VERSION  "0.0.0-alpha"

// Window constants
#define DK_WINDOW_TITLE         "Devil Knights: Fallen Souls - 2023"
#define DK_WINDOW_START_WIDTH   640
#define DK_WINDOW_START_HEIGHT  480

// Game Media root path
#define DK_MEDIA_ROOT   "resources/media"

// Game Media images section
#define DK_MEDIA_IMAGES_ROOT                DK_MEDIA_ROOT "/images"
#define DK_MEDIA_IMAGES__MISSING_DEFAULT    DK_MEDIA_IMAGES_ROOT "/missing.png"
#define DK_MEDIA_IMAGES__SPLASH_ART         DK_MEDIA_IMAGES_ROOT "/splash-art.png"
#define DK_MEDIA_IMAGES__MAIN_TITLE         DK_MEDIA_IMAGES_ROOT "/main-title.png"
#define DK_MEDIA_IMAGES_COUNT               3

// Game Media music section
#define DK_MEDIA_MUSIC_ROOT                 DK_MEDIA_ROOT "/music"
#define DK_MEDIA_MUSIC__MAIN                DK_MEDIA_MUSIC_ROOT "/main.ogg"
#define DK_MEDIA_MUSIC__INTRO               DK_MEDIA_MUSIC_ROOT "/intro.ogg"
#define DK_MEDIA_MUSIC_COUNT                2

#endif