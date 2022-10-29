#include "allModes.h"
#include "texture.h"
#include "gFunctions.h"
#include "music.h"

extern SDL_Renderer *gRenderer;
extern LTexture baseBackground;
extern state currState;
extern LTexture allmodesScreen;
extern LTexture glowingTwoPlayer;
extern LTexture glowingFourPlayer;
extern LTexture glowingSinglePlayer;

void handleEvent_allModes(SDL_Event e)
{
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
    {
        currState = mainMenu;
        playSelectSound();
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN && x > 435 && x < 836 && y > 303 && y < 437)
    {
        currState = singlePlayerMode;
        playSelectSound();
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN && x > 435 && x < 836 && y > 510 && y < 644)
    {
        currState = twoPlayerMode;
        playSelectSound();
    }

    else if (e.type == SDL_MOUSEBUTTONDOWN && x > 435 && x < 836 && y > 709 && y < 845)
    {
        currState = fourPlayerMode;
        playSelectSound();
    }
}

void handle_allModes()
{
    SDL_RenderClear(gRenderer);
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);

    SDL_RenderCopy(gRenderer, allmodesScreen.mTexture, NULL, NULL);

    int x, y;
    SDL_GetMouseState(&x, &y);

    if (x > 435 && x < 836 && y > 303 && y < 437)
    {
        SDL_RenderCopy(gRenderer, glowingSinglePlayer.mTexture, NULL, NULL);
    }
    if (x > 435 && x < 836 && y > 510 && y < 644)
    {
        SDL_RenderCopy(gRenderer, glowingTwoPlayer.mTexture, NULL, NULL);
    }
    if (x > 435 && x < 836 && y > 709 && y < 845)
    {
        SDL_RenderCopy(gRenderer, glowingFourPlayer.mTexture, NULL, NULL);
    }

    SDL_RenderPresent(gRenderer);
}