#include "Highscore.h"

Highscore::Highscore(const char *filename)
{
	currentMouse = prevMouse = false;
	
	ifstream highscoreFile(filename); //fill entries
	string line;
	int i = 0;
	while(!highscoreFile.fail() && i < 5)	
	{
		getline(highscoreFile, line);
		if(line != "")
		{
			entries.push_back(new Entry(&line));
			line = "";
			i++;
		}
	}
	highscoreFile.close();
	sort(entries.begin(), entries.end(), compareEntries); 
	reverse(entries.begin(), entries.end());

	color.r = color.g = color.b = 255;
	activeColor.b = 0;
	activeColor.g = 255;
	activeColor.r = 0;
	
	back = TTF_RenderText_Solid(font, "back", color);
	backRect.h = back->clip_rect.h;
	backRect.w = back->clip_rect.w;
	backRect.x = 1;
	backRect.y = height - backRect.h - 1;
	for(unsigned int i = 0; i < entries.size(); i++)
	{
		entries[i]->render(color, i*50);
	}
}

Highscore::~Highscore()
{
	SDL_FreeSurface(back);
}

void Highscore::handleEvents()
{
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			nextState = StateExit;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if(collision(event.motion.x, event.motion.y, &backRect))
				nextState = StateMenu;
			break;

		case SDL_MOUSEMOTION:
			if(collision(event.motion.x, event.motion.y, &backRect))
				currentMouse = true;
			else
				currentMouse = false;
			break;

		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
			case SDLK_RETURN:
				nextState = StateMenu;
				break;
			case SDLK_ESCAPE:
				nextState = StateMenu;
				break;
			}
		}
	}
}

void Highscore::logic()
{
	if(currentMouse != prevMouse)
	{
		if(currentMouse)
		{
			SDL_FreeSurface(back);
			back = TTF_RenderText_Solid(font, "back", activeColor);
		}
		else
		{
			SDL_FreeSurface(back);
			back = TTF_RenderText_Solid(font, "back", color);
		}
		prevMouse = currentMouse;
	}
}

void Highscore::render()
{
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	for(unsigned int i = 0; i < entries.size(); i++)
	{
		entries[i]->show();
	}
	SDL_BlitSurface(back, NULL, screen, &backRect);
}
