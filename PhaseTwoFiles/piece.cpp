#include <bits/stdc++.h>
#include "piece.h"
#include "gFunctions.h"
#include "maths.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int holeWidth;
extern int holeHeight;
extern int striked;
extern int totalPieces;

extern piece pieces[]; 

piece::piece(int initialPosX, int initialPosY)
{
	mVelX = 0;
	mVelY = 0;

	mPosX = initialPosX;
	mPosY = initialPosY;

    potted = 0;
    possibleToStrike = 1;

    collider.x = mPosX + (texture.getWidth()) / 2;
    collider.y = mPosY + (texture.getHeight()) / 2;
    collider.r = texture.getWidth() / 2;
}

void piece::initialize(double initialPosX, double initialPosY)
{
    speed = 0;
    mPosX = initialPosX;
    mPosY = initialPosY;

    mVelX = 0;
    mVelY = 0;

    potted = 0;
    possibleToStrike = 1;

    collider.x = mPosX + (texture.getWidth()) / 2;
    collider.y = mPosY + (texture.getHeight()) / 2;
    collider.r = texture.getWidth() / 2;
}

void piece::handleEvent(SDL_Event e)
{
    int mousePosX;
    int mousePosY;
    SDL_GetMouseState(&mousePosX, &mousePosY);
    if(e.type == SDL_MOUSEBUTTONDOWN) std::cout << mousePosX << " " << mousePosY << std::endl; 

    // Adjusts the velocity of the striker before it is striked
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 && !striked)
    {
        switch( e.key.keysym.sym )
        {
            // case SDLK_UP: mVelY -= beforeStrikeSpeed; break;
            // case SDLK_DOWN: mVelY += beforeStrikeSpeed; break;
            case SDLK_LEFT: mVelX -= beforeStrikeSpeed; break;
            case SDLK_RIGHT: mVelX += beforeStrikeSpeed; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 && !striked)
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            // case SDLK_UP: mVelY += beforeStrikeSpeed; break;
            // case SDLK_DOWN: mVelY -= beforeStrikeSpeed; break;
            case SDLK_LEFT: mVelX += beforeStrikeSpeed; break;
            case SDLK_RIGHT: mVelX -= beforeStrikeSpeed; break;
        }
    }
    
    if(possibleToStrike){
        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE){
            if(speed <= 60) speed += 5;
        }
        else if(e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_SPACE){
            int mousePosX;
            int mousePosY;
            SDL_GetMouseState(&mousePosX, &mousePosY);
            striked = 1;

            mVelX = (double) speed * (mousePosX - collider.x) / dist(collider.x, collider.y, mousePosX, mousePosY);
            mVelY = (double) speed * (mousePosY - collider.y) / dist(collider.x, collider.y, mousePosX, mousePosY);
        }
    }
}

void piece::move(int id, int currPlayerID)
{
    if(striked){
        mPosX += mVelX;
        if(mPosX <= 35){
            mPosX -= mVelX;
            mVelX *= -1;
        }
        else if(mPosX + texture.getWidth() >= 945){
            mPosX -= mVelX;
            mVelX *= -1;
        }
        shiftColliders();

        mPosY += mVelY;
        if(mPosY <= 35){
            mPosY -= mVelY;
            mVelY *= -1;
        }
        else if(mPosY + texture.getHeight() >= 945){
            mPosY -= mVelY;
            mVelY *= -1;
        }
        shiftColliders();

        // handling collisions
        for(int i = 0; i < totalPieces; i++){
            // a piece can not collide with itself, so collision has to be checked with other pieces
            // collisions have to be checked with pieces that have not been potted yet
            if(i != id && !pieces[i].potted){
                if(checkCollision(pieces[id].collider, pieces[i].collider)){
                    // taking a step back
                    mPosX -= mVelX;
                    mPosY -= mVelY;
                    shiftColliders();

                    handleCollision(pieces[id], pieces[i]);
                }
            }
        }

        if(id != 0 && isPotted()) potted = 1;

        if(mVelX != 0 && striked) mVelX -= 0.02 * mVelX;
        if(mVelY != 0 && striked) mVelY -= 0.02 * mVelY;

        if(abs(mVelX) < 0.005) mVelX = 0;
        if(abs(mVelY) < 0.005) mVelY = 0;

        shiftColliders();
    }
    else{
        mPosX += mVelX;
        if(mPosX <= 195){
            mPosX -= mVelX;
            if(striked) mVelX *= -1;
        }
        else if(mPosX + texture.getWidth() >= 785){
            mPosX -= mVelX;
            if(striked) mVelX *= -1;
        }
        shiftColliders();

        if(id == 0){
            bool collisionFlag = 0;
            for(int i = 1; i < totalPieces; i++){
                if(checkCollision(pieces[0].collider, pieces[i].collider)){
                    collisionFlag = 1;
                    break;
                }
            }
            if(collisionFlag) possibleToStrike = 0;
            else possibleToStrike = 1;
        }
    }
}

void piece::render()
{
	texture.render((int) mPosX, (int) mPosY);
}

void piece::freeTexture()
{
	texture.free();
}

void piece::shiftColliders()
{
    collider.x = mPosX + (texture.getWidth()) / 2;
    collider.y = mPosY + (texture.getHeight()) / 2;
    collider.r = texture.getWidth() / 2;
}

void piece::handleCollision(piece &piece1, piece &piece2)
{
    circle circle1 = piece1.collider;
    circle circle2 = piece2.collider;

    double n_x = circle1.x - circle2.x;
    double n_y = circle1.y - circle2.y;

    double c = (n_x * (piece2.mVelX - piece1.mVelX) + n_y * (piece2.mVelY - piece1.mVelY)) / (distanceSq(n_x, n_y, 0, 0));

    piece1.mVelX += c * n_x;
    piece2.mVelX -= c * n_x;

    piece1.mVelY += c * n_y;
    piece2.mVelY -= c * n_y;
}

bool piece::isPotted()
{
    double width = collider.r * 2.0;
    bool insidePocket = 0;
    if(mPosX <= 62 && mPosY <= 65) insidePocket = 1;
    else if(mPosX + width >= 917 && mPosY <= 65) insidePocket = 1;
    else if(mPosX <= 62 && mPosY + width >= 917) insidePocket = 1;
    else if(mPosX + width >= 917 && mPosY + width >= 922) insidePocket = 1;

    if(insidePocket){
        mVelX = 0;
        mVelY = 0;
    }

    return insidePocket;
}