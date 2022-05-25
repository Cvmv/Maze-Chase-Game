#include "Entry.h"

Entry::Entry(string *src)
{
	if(*src != "")
	{
		name.insert(0, *src, 0, src->find(','));
		string tempPoints;
		stringstream stream;
		tempPoints.insert(0, *src, src->find(',')+1, src->length() - src->find(',')-1);
		stream << tempPoints;
		stream >> points;
	}
}

Entry::Entry(int ipoints, string *iname)
	:points(ipoints), name(*iname)
{
	
}

Entry::~Entry()
{
	SDL_FreeSurface(pointsSurf);
	SDL_FreeSurface(nameSurf);
}

void Entry::render(SDL_Color color, int y)
{
	stringstream stream;
	string stringPoints;

	stream << points;
	stream >> stringPoints;

	if(name == "")
		name = " ";
	nameSurf = TTF_RenderText_Solid(font, name.c_str(), color);
	pointsSurf = TTF_RenderText_Solid(font, stringPoints.c_str(), color);

	nameRect.h = nameSurf->clip_rect.h;
	nameRect.w = nameSurf->clip_rect.w;
	nameRect.x = 20;
	nameRect.y = y;

	pointsRect.h = pointsSurf->clip_rect.h;
	pointsRect.w = pointsSurf->clip_rect.w;
	pointsRect.x = screen->clip_rect.w - pointsRect.w - 20;
	pointsRect.y = y;
}

void Entry::show()
{
	SDL_BlitSurface(nameSurf, NULL, screen, &nameRect);
	SDL_BlitSurface(pointsSurf, NULL, screen, &pointsRect);
}

void Entry::write(ofstream &outFile)
{
	outFile << name << "," << points << endl;
}

bool compareEntries(Entry *left, Entry *right)
{
	return *left < *right;
}
