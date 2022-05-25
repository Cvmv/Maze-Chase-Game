#include "StdAfx.h"
#include "BaseClass.h"
#include "Globals.h"
#include "Entry.h"
#include "Funcs.h"

#ifndef NEWHIGHSCORE_H
#define NEWHIGHSCORE_H

class NewHighscore : public Base
{
	string name, fileName;
	int isActive, wasActive;
	bool nameChanged, pressed, somethingActive;
	SDL_Surface *pointsSurf, *nameSurf, *headSurf, *UISurf[2];
	SDL_Rect pointsRect, nameRect, headRect, UIRect[2];
	string text[2];
	SDL_Color color, activeColor;
public:
	NewHighscore(const char *filename);
	~NewHighscore();
	void handleEvents();
	void logic();
	void render();
	void writeToFile();
};

#endif