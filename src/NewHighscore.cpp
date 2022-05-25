#include "NewHighscore.h"
#include <SDL2/SDL_events.h>
#include <string>

NewHighscore::NewHighscore(const char *filename)
	:name(""), fileName(filename)
{
	isActive = wasActive = 0;
	somethingActive = true;
	nameChanged = pressed = false;
	//SDL_EnableUNICODE(SDL_ENABLE);
	color.r = color.b = color.g = 255;
	activeColor.r = activeColor.b = 0;
	activeColor.g = 255;

	text[0] = "OK";
	text[1] = "No";

	stringstream stream;
	stream << points;
	string pointsString;
	stream >> pointsString;
	pointsString += " points!";
	pointsString.insert(0, "You got ");

	pointsSurf = TTF_RenderText_Solid(font, pointsString.c_str(), color);
	headSurf = TTF_RenderText_Solid(font, "Enter your name!", color);
	nameSurf = TTF_RenderText_Solid(font, " ", color);
	UISurf[0] = TTF_RenderText_Solid(font, text[0].c_str(), color);
	UISurf[1] = TTF_RenderText_Solid(font, text[1].c_str(), color);

	pointsRect = pointsSurf->clip_rect;
	pointsRect.x = screen->clip_rect.w/2 - pointsRect.w/2;
	pointsRect.y = 20;

	headRect = headSurf ->clip_rect;
	headRect.x = screen->clip_rect.w/2 - headRect.w/2;
	headRect.y = 20 + pointsRect.h + 20;

	UIRect[1] = UISurf[1] ->clip_rect;
	UIRect[1].x = screen->clip_rect.w - UIRect[1].w - 5;
	UIRect[1].y = screen->clip_rect.h - UIRect[1].h;
	
	UIRect[0] = UISurf[0] ->clip_rect;
	UIRect[0].x = 5;//screen->clip_rect.w - UIRect[1].w - UIRect[0].w - 20;;
	UIRect[0].y = screen->clip_rect.h - UIRect[0].h;

	nameRect = nameSurf->clip_rect;
	nameRect.x = screen->clip_rect.w/2 - nameRect.w/2;
	nameRect.y = 20;

}

NewHighscore::~NewHighscore()
{
	SDL_FreeSurface(pointsSurf);
	SDL_FreeSurface(nameSurf);
	SDL_FreeSurface(headSurf);
	SDL_FreeSurface(UISurf[0]);
	SDL_FreeSurface(UISurf[1]);
	//SDL_EnableUNICODE(SDL_DISABLE);
}

void NewHighscore::handleEvents()
{
	string temp;
	string input;
	while(SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			nextState = StateExit;
			break;
		case SDL_TEXTINPUT:
			temp = name;
			
			if(name.length() <= 10) {
				input = event.text.text;
				if(input != ",") {
					name += input;
				}
			}
			if(name != temp)
			{
				nameChanged = true;
			}
			break;
		case SDL_KEYDOWN:
			if(event.key.keysym.sym == SDLK_BACKSPACE && name.length() != 0)
				name.erase(name.length()-1);
		
			if(name != temp)
			{
				nameChanged = true;
			}

			switch(event.key.keysym.sym)
			{
			case SDLK_LEFT:
				isActive--;
				if(isActive < 0)
					isActive = 1;
				break;
			case SDLK_RIGHT:
				isActive++;
				if(isActive >= 2)
					isActive = 0;
				break;
			case SDLK_RETURN:
				pressed = true;
				break;
			}

			break;
		case SDL_MOUSEMOTION:
			for(int i = 0; i < 2; i++)
			{
				if(collision(event.motion.x, event.motion.y, &UIRect[i]))
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
		}
	}
}

void NewHighscore::logic()
{
	if(nameChanged)
	{	
		string surfName;
		if(name == "")
			surfName = " ";
		else
		 	surfName = name;
		SDL_FreeSurface(nameSurf);
		nameSurf = TTF_RenderText_Solid(font, surfName.c_str(), color);
		nameRect = nameSurf->clip_rect;
		nameRect.x = screen->clip_rect.w/2 - nameRect.w/2;
		nameRect.y = screen->clip_rect.h/2 - nameRect.h/2;
	}
	if(isActive != wasActive)
	{
		if(isActive == -1)
		{
			SDL_FreeSurface(UISurf[wasActive]);
			UISurf[wasActive] = TTF_RenderText_Solid(font, text[wasActive].c_str(), color);
			wasActive = isActive;
		}
		else
		{
			if(wasActive != -1)
			{
				SDL_FreeSurface(UISurf[wasActive]);
				UISurf[wasActive] = TTF_RenderText_Solid(font, text[wasActive].c_str(), color);
			}
			SDL_FreeSurface(UISurf[isActive]);
			UISurf[isActive]  = TTF_RenderText_Solid(font, text[isActive].c_str(), activeColor);
			wasActive = isActive;
		}
	}
	if(pressed)
	{
		pressed = false;
		if(isActive == 0)
		{
			writeToFile();
			points = 0;
			nextState = StateMenu;
		}
		else if(isActive == 1)
		{
			points = 0;
			nextState = StateMenu;
		}
	}
}

void NewHighscore::render()
{
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	SDL_BlitSurface(pointsSurf, NULL, screen, &pointsRect);
	SDL_BlitSurface(headSurf, NULL, screen, &headRect);
	SDL_BlitSurface(nameSurf, NULL, screen, &nameRect);
	SDL_BlitSurface(UISurf[0], NULL, screen, &UIRect[0]);
	SDL_BlitSurface(UISurf[1], NULL, screen, &UIRect[1]);
}

void NewHighscore::writeToFile()
{
	vector<Entry*> entries;
	ifstream inFile(fileName);
	string line;
	int i = 0;
	while(!inFile.fail() && i < 5)	//entries bef�llen
	{
		getline(inFile, line);
		if(line != "")
		{
			entries.push_back(new Entry(&line));
			line = "";
			i++;
		}
	}
	inFile.close();

	entries.push_back(new Entry(points, &name));
	sort(entries.begin(), entries.end(), compareEntries);
	reverse(entries.begin(), entries.end());

	ofstream outFile(fileName);
	for(unsigned int i = 0; i < entries.size(); i++)
	{
		entries[i]->write(outFile);
	}
	outFile.close();
}