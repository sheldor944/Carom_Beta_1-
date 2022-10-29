#include "2_player_mode.h"
#include "piece.h"
#include "gFunctions.h"

extern SDL_Window *gWindow;
extern SDL_Renderer *gRenderer;

extern LTexture background;
extern LTexture board;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern int striked;
extern enum state currState;

extern int totalPieces;
extern piece pieces[];

bool allPotted;
int currPlayerID = 0;

void initAllPieces()
{
    pieces[2].initialize(200, 200);
    pieces[1].initialize(200, SCREEN_HEIGHT - 300);
    pieces[0].initialize(200, 774);

    allPotted = false;
}

void handleEvent_2PlayerMode(SDL_Event e)
{
    pieces[0].handleEvent(e);
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
    {
        currState = mainMenu ;
    }
}

void handle_2PlayerMode()
{
    if (striked)
    {
        for (int i = 0; i < totalPieces; i++)
        {
            if (!pieces[i].potted)
                pieces[i].move(i, -1);
        }

        if (motionOver())
        {
            striked = 0;
            if (checkGameOver(1, 2))
                allPotted = true;
            pieces[0].initialize(200, 774);
            if (!allPotted)
            {
                // currPlayerID ^= 1;
            }
        }
    }
    else
    {
        pieces[0].move(0, currPlayerID);
    }

    if (allPotted)
    {
        currState = result;
        return;
    }

    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // clearing the screen
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0xFF);
    SDL_RenderClear(gRenderer);

    // rendering the background and the board
    SDL_RenderCopy(gRenderer, background.mTexture, NULL, NULL);
    board.render(0, 0);

    if (!striked)
    {
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderDrawLine(gRenderer, (pieces[0].mPosX * 2 + pieces[0].texture.getWidth()) / 2, (pieces[0].mPosY * 2 + pieces[0].texture.getHeight()) / 2, mouseX, mouseY);
    }

    for (int i = 0; i < totalPieces; i++)
    {
        if (!pieces[i].potted)
            pieces[i].render();
    }

    SDL_RenderPresent(gRenderer);
}