#include "StdAfx.h"
#include "BaseClass.h"
#ifndef GLOBALS_H
#define GLOBALS_H

#define width  400
#define height 300
#define FPS     30

extern SDL_Surface *screen;
extern TTF_Font *font;
extern SDL_Event event;
extern Gamestate stateID, nextState;
extern Base *currentState;
extern unsigned int points;
extern int lives;
extern int blockSize;

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;
extern string fontname;

#endif