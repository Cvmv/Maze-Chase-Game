#include "StdAfx.h"
#include "Globals.h"

#ifndef ENTRY_H
#define ENTRY_H

class Entry
{
	int points;
	string name;
	SDL_Surface *pointsSurf, *nameSurf;
	SDL_Rect pointsRect, nameRect;
public:
	Entry(string *src);;
	Entry(int ipoints, string *iname);
	~Entry();
	void write(ofstream &outFile);
	void render(SDL_Color color, int y);
	void show();
	bool operator<(const Entry &h) const {return points < h.points;}
};

bool compareEntries(Entry *left, Entry *right);

#endif