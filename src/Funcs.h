#include "StdAfx.h"
#include "Globals.h"
#ifndef FUNCS_H
#define FUNCS_H

bool collision(const SDL_Rect *rec1, const SDL_Rect *rec2);
bool collision(int x, int y, const SDL_Rect *rec2);
bool loadFiles();
bool init();
void cleanUp();
SDL_Rect makeRect(int x, int y, int w, int h);

#endif