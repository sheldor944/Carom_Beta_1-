#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include "circle.h"
#include "gFunctions.h"
#include "maths.h"
#include <math.h>
#include "piece.h"

// Screen dimension constants
int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 980;

int totalPieces = 3;

piece pieces[3];

LTexture background;
LTexture board;
LTexture mainMenuScreen;
LTexture allRules;
LTexture baseBackground;
LTexture playButton;
LTexture allmodesScreen;
LTexture singlePlayerScreen;
LTexture glowingPlay;
LTexture glowingRules;
LTexture glowingSinglePlayer;
LTexture glowingRapid;
LTexture glowingVsComputer;
LTexture glowingTwoPlayer;
LTexture glowingFourPlayer;

// Music
Mix_Music *gMusic = NULL;
Mix_Music *clockTicSound = NULL;
Mix_Music *collisionSound = NULL;

Mix_Chunk *hardCollisionSound = NULL;
Mix_Chunk *selectionSound = NULL;

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The window renderer
SDL_Renderer *gRenderer = NULL;

int striked = 0;
int paused = 0;

state currState;

// Pair strikerLimit[] = {Pair{}};

bool init()
{
	// Initialization flag
	bool success = true;

	// Initialize SDL
	//  Added SDL AUdio
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		// Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		// Create window
		gWindow = SDL_CreateWindow("CAROM", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	if (!background.loadFromFile("images/background.png"))
	{
		printf("Background could not be loaded\n");
		success = false;
	}

	if (!board.loadFromFile("images/board.png"))
	{
		printf("Board could not be loaded\n");
		success = false;
	}

	for (int i = 0; i < totalPieces; i++)
	{
		if (!pieces[i].texture.loadFromFile("images/black.png"))
		{
			printf("Image could not be loaded\n");
			success = false;
		}
	}

	// mainMenu and UI
	if (!mainMenuScreen.loadFromFile("images/mainMenu.jpeg"))
	{
		printf("Image could not be loaded for mainMeny\n");
		success = false;
	}
	if (!allRules.loadFromFile("images/rules.jpeg"))
	{
		printf("Rules cannot be loaded \n");
		success = false;
	}
	if (!baseBackground.loadFromFile("images/baseBackground.jpeg"))
	{
		printf("Base Background could not be loaded\n");
		success = false;
	}
	if (!playButton.loadFromFile("images/black.png"))
	{
		printf("Could not load play Button \n");
		success = false;
	}
	if (!allmodesScreen.loadFromFile("images/allmode.jpeg"))
	{
		printf("Couild not load all mode menu \n");
		success = false;
	}
	if (!singlePlayerScreen.loadFromFile("images/singlePlayer.jpeg"))
	{
		printf("Couild not load all single player menu  \n");
		success = false;
	}
	if (!glowingPlay.loadFromFile("images/glowingPlay.png"))
	{
		printf("Couild not load all glowing play   \n");
		success = false;
	}
	// edit neederd
	if (!glowingPlay.loadFromFile("images/glowingPlay.png"))
	{
		printf("Couild not load all glowing play   \n");
		success = false;
	}
	if (!glowingRules.loadFromFile("images/glowingRules.png"))
	{
		printf("Couild not load all glowingRules   \n");
		success = false;
	}

	if (!glowingSinglePlayer.loadFromFile("images/glowingSinglePlayer.png"))
	{
		printf("Couild not load all glowingSinglePlayer   \n");
		success = false;
	}
	if (!glowingRapid.loadFromFile("images/glowingRapid.png"))
	{
		printf("Couild not load all glowingRapid   \n");
		success = false;
	}
	if (!glowingVsComputer.loadFromFile("images/glowingVsComputer.png"))
	{
		printf("Couild not load all glowingVsComputer   \n");
		success = false;
	}
	if (!glowingTwoPlayer.loadFromFile("images/glowingTwoPlayer.png"))
	{
		printf("Couild not load all glowingTwoPlayer   \n");
		success = false;
	}
	if (!glowingFourPlayer.loadFromFile("images/glowingFourPlayer.png"))
	{
		printf("Couild not load all glowingFourPlayer   \n");
		success = false;
	}

	// Loadin music
	// Mix_OpenAudio(48000 , AUDIO_S16SYS , 6.1 , 4096);
	gMusic = Mix_LoadMUS("music/test.mp3");
	if (gMusic == NULL)
	{
		printf("Could not load music \n");
		success = false;
	}
	clockTicSound = Mix_LoadMUS("music/clockTicSound.mp3");

	if (clockTicSound == NULL)
	{
		printf("Could not load musclockTicSoundic \n");
		success = false;
	}
	collisionSound = Mix_LoadMUS("music/collisionSound.mp3");
	if (gMusic == NULL)
	{
		printf("Could not load collisionSound \n");
		success = false;
	}

	hardCollisionSound = Mix_LoadWAV("music/hardCollision.wav");

	if (hardCollisionSound == NULL)
	{
		printf("could not load HardCollision \n");
		success = false;
	}

	selectionSound = Mix_LoadWAV("music/selectionSound.wav");

	if (selectionSound == NULL)
	{
		printf(" Could not load selsction sound \n");
		success = false;
	}

	return success;
}

void close()
{
	// Free loaded images
	for (int i = 0; i < totalPieces; i++)
	{
		pieces[i].freeTexture();
	}

	background.free();
	board.free();

	// Music
	Mix_FreeMusic(gMusic);

	// Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	// Quit SDL subsystems
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}

bool checkCollision(circle A, circle B)
{
	bool collided = 1;

	double sumOfRadii = A.r + B.r;
	double sqOfSum = sumOfRadii * sumOfRadii;
	if (distanceSq(A.x, A.y, B.x, B.y) > sqOfSum)
		collided = 0;

	return collided;
}

bool motionOver()
{
	bool over = 1;
	for (int i = 0; i < totalPieces; i++)
	{
		if (pieces[i].potted)
			continue;
		if (pieces[i].mVelX != 0 || pieces[i].mVelY != 0)
		{
			over = 0;
			break;
		}
	}

	return over;
}

bool checkGameOver(int id1, int id2)
{
	bool over = 1;
	for (int i = id1; i <= id2; i++)
	{
		if (!pieces[i].potted)
		{
			over = 0;
			break;
		}
	}
	return over;
}
