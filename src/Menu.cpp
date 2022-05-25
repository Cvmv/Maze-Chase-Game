#include "Menu.h"

Menu::Menu()
	//:isActive(0), wasActive(1), somethingActive(false)
{
	//cout << "WTF\n";
	isActive = 0;
	wasActive = 1;
	somethingActive = pressed = false;
	text[0] = "Start";
	text[1] = "Highscore";
	text[2] = "Quit";
	states[0] = StateGame;
	states[1] = StateHighscore;
	states[2] = StateExit;
	surf[3] = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
	SDL_FillRect(surf[3], NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	color.b = 255;
	color.g = 255;
	color.r = 255;
	activeColor.b = 0;
	activeColor.g = 255;
	activeColor.r = 0;
	surf[0] = TTF_RenderText_Solid(font, text[0].c_str(), color);
	surf[1] = TTF_RenderText_Solid(font, text[1].c_str(), color);
	surf[2] = TTF_RenderText_Solid(font, text[2].c_str(), color);
	rects[0] = surf[0]->clip_rect;
	rects[0].x = screen->clip_rect.w/2 - surf[0]->clip_rect.w/2;
	rects[0].y = screen->clip_rect.h/2 - surf[0]->clip_rect.h/2 - 42 +34;
	rects[1] = surf[1]->clip_rect;
	rects[1].x = screen->clip_rect.w/2 - surf[1]->clip_rect.w/2;
	rects[1].y = screen->clip_rect.h/2 - surf[1]->clip_rect.h/2 +34;
	rects[2] = surf[2]->clip_rect;
	rects[2].x = screen->clip_rect.w/2 - surf[2]->clip_rect.w/2;
	rects[2].y = screen->clip_rect.h/2 - surf[2]->clip_rect.h/2 + 42 +56;
}

Menu::~Menu()
{
	SDL_FreeSurface(surf[0]);
	SDL_FreeSurface(surf[1]);
	SDL_FreeSurface(surf[2]);
	SDL_FreeSurface(surf[3]);
}

void Menu::handleEvents()
{
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			nextState = StateExit;
			break;
		case SDL_MOUSEMOTION:
			for(int i = 0; i < 3; i++)
			{
				if(collision(event.motion.x, event.motion.y, &rects[i]))
				{
					isActive = i;
					somethingActive = true;
				}
			}
			if(!somethingActive)
			{
				isActive = -1;
			}
			somethingActive = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if(event.button.button == SDL_BUTTON_LEFT)
				pressed = true;

		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
			case SDLK_UP:
				isActive--;
				if(isActive < 0)
					isActive = 2;
				break;
			case SDLK_DOWN:
				isActive++;
				if(isActive > 2)
					isActive = 0;
				break;
			case SDLK_RETURN:
				pressed = true;
				break;
			case SDLK_d:
				nextState = StateNewHighscore;
				break;
			}
		}
	}
}

void Menu::logic()
{
	if(isActive != wasActive)
	{
		if(isActive == -1)
		{
			SDL_FreeSurface(surf[wasActive]);
			surf[wasActive] = TTF_RenderText_Solid(font, text[wasActive].c_str(), color);
			wasActive = isActive;
		}
		else
		{
			if(wasActive != -1)
			{
				SDL_FreeSurface(surf[wasActive]);
				surf[wasActive] = TTF_RenderText_Solid(font, text[wasActive].c_str(), color);
			}
			SDL_FreeSurface(surf[isActive]);
			surf[isActive]  = TTF_RenderText_Solid(font, text[isActive].c_str(), activeColor);
			wasActive = isActive;
		}
	}
	if(pressed)
	{
		pressed = false;
		if(isActive != -1)
		{
			nextState = states[isActive];
		}
	}
}

void Menu::render()
{
	SDL_BlitSurface(surf[3], NULL, screen, NULL);
	SDL_BlitSurface(surf[0], NULL, screen, &rects[0]);
	SDL_BlitSurface(surf[1], NULL, screen, &rects[1]);
	SDL_BlitSurface(surf[2], NULL, screen, &rects[2]);
}