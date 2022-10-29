#ifndef PIECE 
#define PIECE

#include "texture.h"
#include "circle.h"

struct piece
{
    // constructor
    piece(int initialPosX = 0, int initialPosY = 0);

    // variables
    LTexture texture; // the texture associated with the piece

    double speed = 0; // controls the speed of the piece after striking
    double beforeStrikeSpeed = 10; // speed of the striker before striking

    double mVelX;
    double mVelY;

    double mPosX;
    double mPosY;

    bool potted;
    bool possibleToStrike;

    circle collider;

    // functions
    void initialize(double initialPosX, double initialPosY);

    void handleEvent(SDL_Event e); // changes the properties based on what events occur
    
    void move(int id, int currPlayerID); // handles motion for the piece with index id

    void render(); // renders the texture in this class

    void freeTexture(); // frees the texture

    void shiftColliders(); // shifts colliders when the position changes

    void handleCollision(piece &piece1, piece &piece2);

    // checks if a piece has been potted
    bool isPotted();
};

#endif