#include "StdAfx.h"
#include "BaseClass.h"
#include "Funcs.h"
#include "Player.h"
#include "Map.h"
#include "KI.h"
#include "UI.h"

#ifndef GAME_H
#define GAME_H

class Game : public Base
{
	unsigned int totalFood;
	Player *player1;
	Map *map;
	KI *ki;
	SDL_Surface *blocks;
	const char *name;
	Ui *ui;
public:
	Game(const char *mapName, const char *blockName);
	~Game();
	void handleEvents();
	void logic();
	void render();
};

#endif