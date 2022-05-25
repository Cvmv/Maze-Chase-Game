#include "StdAfx.h"
#include "Globals.h"

#ifndef UI_H
#define UI_H

class Ui
{
	TTF_Font *uiFont;
	SDL_Color uiColor;
	SDL_Surface *pointsSurf, *livesSurf, *background;
	SDL_Rect pointsRect, livesRect, bgRect;
	unsigned int uiX, uiY, uiHeight, uiWidth, oldPoints, oldLives;
public:
	Ui();
	~Ui();
	void logic();
	void show();
};

#endif