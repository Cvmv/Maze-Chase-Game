#include "StdAfx.h"
#ifndef BASECLASS_H
#define BASECLASS_H

class Base
{
public:
	virtual void handleEvents() = 0;
	virtual void logic() = 0;
	virtual void render() = 0;
	virtual ~Base(){};
};

enum Gamestate
{
	StateNull,
	StateMenu,
	StateGame,
	StateNewHighscore,
	StateHighscore,
	StateExit
};


#endif