#include "mainMenu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "texture.h"
#include "gFunctions.h"
#include <bits/stdc++.h>
#include "music.h"
using namespace std;

extern SDL_Renderer *gRenderer;
extern LTexture mainMenuScreen;
extern LTexture playButton;
extern LTexture glowingPlay;
extern LTexture glowingRules;

extern state currState;

void handleEvent_mainMenu(SDL_Event e)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    if (e.type == SDL_MOUSEBUTTONDOWN && x >= 910 && x <= 1180 && y >= 564 && y <= 697)
    {
        //  cout << "hoise to \n";
        playSelectSound();
        currState = allModes;
    }
    if (e.type == SDL_MOUSEBUTTONDOWN && x >= 910 && x <= 1180 && y >= 785 && y <= 918)
    {
        playSelectSound();
        //  cout << "Rules a giyechi \n ";
        currState = rules;
    }
}
void handle_mainMenu()
{
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_RenderClear(gRenderer);

    SDL_RenderCopy(gRenderer, mainMenuScreen.mTexture, NULL, NULL);

    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x >= 910 && x <= 1180 && y >= 564 && y <= 697)
    {
        SDL_RenderCopy(gRenderer, glowingPlay.mTexture, NULL, NULL);
    }
    if (x >= 910 && x <= 1180 && y >= 785 && y <= 918)
    {
        SDL_RenderCopy(gRenderer, glowingRules.mTexture, NULL, NULL);
    }
    SDL_RenderPresent(gRenderer);

    // Playing the music
    playBackgroundMusic();

    return;
}