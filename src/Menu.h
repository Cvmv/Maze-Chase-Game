#include "StdAfx.h"
#include "BaseClass.h"
#include "Globals.h"
#include "Funcs.h"
#ifndef MENU_H
#define MENU_H

class Menu : public Base
{
	bool somethingActive, pressed;
	SDL_Color color, activeColor;
	int isActive, wasActive;
	string text[3];
	SDL_Surface *surf[4];
	SDL_Rect rects[3];
	Gamestate states[3];
public:
	Menu();
	~Menu();
	void handleEvents();
	void logic();
	void render();
};
#endif