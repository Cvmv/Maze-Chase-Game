#include "Globals.h"

SDL_Surface *screen = NULL;
TTF_Font *font = NULL;
SDL_Event event;
Gamestate stateID = StateNull;
Gamestate nextState = StateNull;
Base *currentState = NULL;
unsigned int points = 0;
int blockSize = 25;
int lives = 0;
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
string fontname = "/usr/share/fonts/TTF/DejaVuSans.ttf";