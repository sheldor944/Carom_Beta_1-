#ifndef gFUNCTIONS
#define gFUNCTIONS

#include "circle.h"
#include "piece.h"

// the state of the program
enum state
{
	mainMenu,
	allModes,
	playerIntro,
	rules,
	leaderboard,
	singlePlayerMode,
	twoPlayerMode,
	fourPlayerMode,
	result
};

struct Pair
{
	int x, y;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

// checks if the circles A and B are colling or not
bool checkCollision(circle A, circle B);

// checks if all pieces have stopped moving
bool motionOver();

// checks if the pieces having id from id1 to id2 are potted 
bool checkGameOver(int id1, int id2);

#endif 