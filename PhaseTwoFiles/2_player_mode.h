#ifndef TWO_PLAYER_MODE
#define TWO_PLAYER_MODE

#include <SDL2/SDL.h>

void initAllPieces();
void handle_2PlayerMode();
void handleEvent_2PlayerMode(SDL_Event e);

#endif