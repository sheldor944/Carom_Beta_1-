#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include "gFunctions.h"
#include "mainMenu.h"
#include "allModes.h"
#include "playerIntro.h"
#include "rules.h"
#include "leaderboard.h"
#include "singlePlayerMode.h"
#include "2_player_mode.h"
#include "fourPlayerMode.h"
#include<SDL2/SDL_mixer.h>
#include "music.h"

extern enum state currState;

int main()
{
	// Start up SDL and create window
	if (!init())
		printf("Failed to initialize!\n");
	else
	{
		// Load media
		if (!loadMedia())
			printf("Failed to load media!\n");
		else
		{
			// Main loop flag
			bool quit = false;

			// Event handler
			SDL_Event e;
			initAllPieces();

			currState = mainMenu;

			// While application is running
			while (!quit)
			{
				// Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					
					// User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					// handleEvent_mainMenu(e);
					switch (currState)
					{
					case mainMenu:
						handleEvent_mainMenu(e);
						break;
					case allModes:
						handleEvent_allModes(e);
						break;
					case playerIntro:
						handleEvent_playerIntro(e);
						break;
					case rules:
						handleEvent_rules(e);
						break;
					case leaderboard:
						handleEvent_leaderboard(e);
						break;
					case singlePlayerMode:
						handleEvent_singlePlayerMode(e);
						break;
					case twoPlayerMode:
						handleEvent_2PlayerMode(e);
						break;
					case fourPlayerMode:
						handleEvent_4PlayerMode(e);
						break;
					}
				}

				switch (currState)
				{
				case mainMenu:
					handle_mainMenu();
					break;
				case allModes:
					handle_allModes();
					break;
				case playerIntro:
					handle_playerIntro();
					break;
				case rules:
					handle_rules();
					break;
				case leaderboard:
					handle_leaderboard();
					break;
				case singlePlayerMode:
					handle_singlePlayerMode();
					break;
				case twoPlayerMode:
					handle_2PlayerMode();
					break;
				case fourPlayerMode:
					handle_4PlayerMode();
					break;
				}
			}
		}
	}

	// Free resources and close SDL
	close();

	return 0;
}