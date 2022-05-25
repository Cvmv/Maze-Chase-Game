#include "StdAfx.h"
#include "BaseClass.h"
#include "Entry.h"
#include "Funcs.h"
#include "Globals.h"

#ifndef HIGHSCORE_H
#define HIGHSCORE_H

class Highscore : public Base
{
	vector<Entry*> entries;
	SDL_Surface *back;
	SDL_Rect backRect;
	SDL_Color color, activeColor;
	bool currentMouse, prevMouse;
public:
	Highscore(const char *filename);
	~Highscore();
	void handleEvents();
	void logic();
	void render();
};


#endif