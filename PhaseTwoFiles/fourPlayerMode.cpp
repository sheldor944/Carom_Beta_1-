#include "fourPlayerMode.h"
#include "texture.h"
#include "gFunctions.h"

extern SDL_Renderer *gRenderer;
extern LTexture baseBackground;
extern state currState;

void handleEvent_4PlayerMode(SDL_Event e)
{

    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
    {
        currState = allModes;
    }
}

void handle_4PlayerMode()
{
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

    SDL_RenderCopy(gRenderer, baseBackground.mTexture, NULL, NULL);
    SDL_RenderPresent(gRenderer);
}