#include "UI.h"

Ui::Ui()
{
	uiX = 0;
	uiY = 275;
	uiWidth = 400;
	uiHeight = 25;
	oldPoints = points;
	oldLives = lives;
	uiFont = NULL;
	uiFont = TTF_OpenFont(fontname.c_str(), 25);
	uiColor.b = 0;
	uiColor.g = 255;
	uiColor.r = 255;

	pointsRect.x = pointsRect.y = pointsRect.w = pointsRect.h = 0;
	livesRect.x  = livesRect.y  = livesRect.w  = livesRect.h  = 0;

	background = SDL_CreateRGBSurface(0,uiWidth,uiHeight,32,0,0,0,0);
	bgRect.w = background->clip_rect.w;
	bgRect.h = background->clip_rect.h;
	bgRect.x = uiX;
	bgRect.y = uiY;

	// creating pointsSurf
	string pointsString = "";
	stringstream pointsStream;
	pointsStream << points;
	pointsStream >> pointsString;
	pointsSurf = TTF_RenderText_Solid(uiFont, pointsString.c_str(), uiColor);

	// creating livesSurf
	string livesString = "";
	stringstream livesStream;//(lives);
	livesStream << lives;
	livesStream >> livesString;
	livesSurf = TTF_RenderText_Solid(uiFont, livesString.c_str(), uiColor);

	pointsRect.w = pointsSurf->clip_rect.w;
	pointsRect.h = pointsSurf->clip_rect.h;
	pointsRect.x = 0;
	pointsRect.y = 0;
	SDL_BlitSurface(pointsSurf, NULL, background, &pointsRect);

	livesRect.w = livesSurf->clip_rect.w;
	livesRect.h = livesSurf->clip_rect.h;
	livesRect.x = width - livesRect.w;
	livesRect.y = 0;
	SDL_BlitSurface(livesSurf, NULL, background, &livesRect);
}

Ui::~Ui()
{	
	SDL_FreeSurface(pointsSurf);
	SDL_FreeSurface(livesSurf);
	SDL_FreeSurface(background);
	TTF_CloseFont(uiFont);
}

void Ui::logic()
{
	if (points != oldPoints)
	{
		string pointsString;
		stringstream pointsStream;
		pointsStream << points;
		pointsStream >> pointsString;
		SDL_FreeSurface(pointsSurf);
		pointsSurf = TTF_RenderText_Solid(uiFont, pointsString.c_str(), uiColor);
	}
	if (lives != oldLives)
	{
		string livesString;
		stringstream livesStream;
		livesStream << lives;
		livesStream >> livesString;
		SDL_FreeSurface(livesSurf);
		livesSurf = TTF_RenderText_Solid(uiFont, livesString.c_str(), uiColor);
	}
	if(lives != oldLives || points != oldPoints)
	{
		SDL_FreeSurface(background);
		background = SDL_CreateRGBSurface(0,uiWidth,uiHeight,32,0,0,0,0);
		
		//pointsRect.w = pointsSurf->clip_rect.w;
		//pointsRect.h = pointsSurf->clip_rect.h;
		pointsRect.x = 0;
		pointsRect.y = 0;
		SDL_BlitSurface(pointsSurf, NULL, background, &pointsRect);

		livesRect.w = livesSurf->clip_rect.w;
		livesRect.h = livesSurf->clip_rect.h;
		livesRect.x = width - livesRect.w;
		livesRect.y = 0;
		SDL_BlitSurface(livesSurf, NULL, background, &livesRect);
		oldLives = lives;
		oldPoints = points;
	}
}

void Ui::show()
{
	SDL_BlitSurface(background, NULL, screen, &bgRect);
}
