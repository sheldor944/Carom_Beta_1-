#include "singlePlayerMode.h"
#include "texture.h"
#include "gFunctions.h"
#include "music.h"

extern SDL_Renderer *gRenderer;
extern LTexture singlePlayerScreen;
extern state currState;
extern LTexture glowingRapid;
extern LTexture glowingVsComputer;

void handleEvent_singlePlayerMode(SDL_Event e)
{

    int x, y;
    SDL_GetMouseState(&x, &y);

    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
    {
        currState = allModes;
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN && x > 435 && x < 836 && y > 309 && y < 433)
    {

        currState = twoPlayerMode;
        playSelectSound();
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN && x > 435 && x < 836 && y > 569 && y < 700)
    {
        currState = twoPlayerMode;
        playSelectSound();
    }
}

void handle_singlePlayerMode()
{
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

    SDL_RenderCopy(gRenderer, singlePlayerScreen.mTexture, NULL, NULL);

    int x, y;
    SDL_GetMouseState(&x, &y);

    if (x > 435 && x < 836 && y > 309 && y < 433)
    {
        SDL_RenderCopy(gRenderer, glowingRapid.mTexture, NULL, NULL);
    }
    if (x > 435 && x < 836 && y > 569 && y < 700)
    {
        SDL_RenderCopy(gRenderer, glowingVsComputer.mTexture, NULL, NULL);
    }
    SDL_RenderPresent(gRenderer);
}