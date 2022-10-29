#include "rules.h"
#include "texture.h"
#include "gFunctions.h"

extern SDL_Renderer* gRenderer  ; 
extern LTexture allRules;
extern LTexture background ;
extern state currState ;


void handleEvent_rules(SDL_Event e)
{
    SDL_RenderClear( gRenderer );
    SDL_SetRenderDrawColor ( gRenderer , 255 , 255 , 255, 255) ;
    SDL_RenderCopy ( gRenderer , allRules.mTexture, NULL , NULL );
    SDL_RenderPresent( gRenderer );
    if(e.type== SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
    {
        
        currState = mainMenu ;
    }
}

void handle_rules()
{
    
}