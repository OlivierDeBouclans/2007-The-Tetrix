#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>


/*********************************PAUSE S**************************************/

void PauseS( SDL_Surface *Ecran)
{/* Initialisation */
 int Continuer = 1;
 SDL_Event Event;
 
 /* Boucle de la pause */
 while(Continuer)
       {SDL_WaitEvent(&Event);
        if ( Event.key.keysym.sym == SDLK_SPACE ) { Continuer = 0;}
        if ( Event.type == SDL_QUIT ) { exit(0); }
       }

 //free(&Continuer);
 //free(&Event);           
}


/*********************************PAUSE E**************************************/


void PauseE( SDL_Surface *Ecran)
{/* Initialisation */
 int Continuer = 1;
 SDL_Event Event;
  
 /* Boucle de la pause */
 while(Continuer)
       {SDL_WaitEvent(&Event);
        if (Event.type == SDL_KEYDOWN) 
           {if ( Event.key.keysym.sym == SDLK_RETURN || Event.key.keysym.sym == SDLK_ESCAPE ) 
               { Continuer = 0;}}
        if ( Event.type == SDL_QUIT ) { exit(0); }
       }
  
 //free(&Continuer);
 //free(&Event);       
}
       





