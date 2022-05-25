#include "StdAfx.h"

#ifndef OBJECT_H
#define OBJECT_H

class Object
{
protected:
	SDL_Rect rect;
public:
	Object();
	~Object();
	void init(int x, int y);
	void move(int x, int y);
};

#endif