#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "pause.h"
#include "score.h"
#include "option.h"
#include "jeu.h"
#include "menu.h"

/* Variable globale (pour la mémoire des menus) */
int z = 0;

void Menu( SDL_Surface *Ecran, int *Stop)
{/* Initialisation */
 int Continuer = 1;
 SDL_Event Event;
 static SDL_Surface *Fond, *Barre[5];
 static SDL_Rect Coordonnee0 = {0,0};
 static SDL_Rect CoordonneeBarre[5];
  
 /* Initialisation des coordonnées des barres */
 CoordonneeBarre[0].x = 30 ;
 CoordonneeBarre[0].y = 373;
 CoordonneeBarre[1].x = 30 ;
 CoordonneeBarre[1].y = 433;
 CoordonneeBarre[2].x = 30 ;
 CoordonneeBarre[2].y = 490;
 CoordonneeBarre[3].x = 30 ;
 CoordonneeBarre[3].y = 547;
 CoordonneeBarre[4].x = 318;
 CoordonneeBarre[4].y = 563;
 
 /* Initialisation des surfaces */  
 Fond = SDL_LoadBMP("Ressources\\Ecran Menu.bmp" );
 Barre[0]   = SDL_LoadBMP("Ressources\\Menu Barre1.bmp");
 Barre[1]   = SDL_LoadBMP("Ressources\\Menu Barre2.bmp");
 Barre[2]   = SDL_LoadBMP("Ressources\\Menu Barre3.bmp");
 Barre[3]   = SDL_LoadBMP("Ressources\\Menu Barre4.bmp");
 Barre[4]   = SDL_LoadBMP("Ressources\\Menu Barre5.bmp");
 SDL_SetColorKey( Barre[4], SDL_SRCCOLORKEY, SDL_MapRGB(Barre[4]->format, 0, 0, 0));

 /* Blitt des Surfaces */
 SDL_BlitSurface( Fond,     NULL, Ecran, &Coordonnee0);
 SDL_BlitSurface( Barre[z], NULL, Ecran, &CoordonneeBarre[z]);
 SDL_Flip(Ecran);
 
 /* Boucle du choix dans le menu */
 while(Continuer)
      {SDL_WaitEvent(&Event);
       //if(Event.type == SDL_QUIT){exit(0);}
       if(Event.type == SDL_KEYDOWN){
        switch(Event.key.keysym.sym)
               {case SDLK_DOWN: 
                     z +=1;
                     if (z==5){z=4;}
                     SDL_BlitSurface( Fond,     NULL, Ecran, &Coordonnee0);
                     SDL_BlitSurface( Barre[z], NULL, Ecran, &CoordonneeBarre[z]);
                     SDL_Flip(Ecran);
               break;
               case SDLK_UP:
                    z -=1;
                    if (z==-1){z=0;}
                    SDL_BlitSurface( Fond,     NULL, Ecran, &Coordonnee0);
                    SDL_BlitSurface( Barre[z], NULL, Ecran, &CoordonneeBarre[z]);
                    SDL_Flip(Ecran);
               break;
               case SDLK_RETURN: 
                    Continuer = 0;
               break;}}
       }
       
 /* Pré-fermeture */       
 free(&Continuer);
 free(&Coordonnee0);
 free(&CoordonneeBarre[0]);
 free(&CoordonneeBarre[1]);
 free(&CoordonneeBarre[2]);
 free(&CoordonneeBarre[3]);
 free(&CoordonneeBarre[4]);
 free(&Event);
 SDL_FreeSurface(Fond);       
 SDL_FreeSurface(Barre[1]);
 SDL_FreeSurface(Barre[2]); 
 SDL_FreeSurface(Barre[3]); 
 SDL_FreeSurface(Barre[4]); 
 SDL_FreeSurface(Barre[5]); 
 
 /* Conséquences du choix */
 switch(z)
       {case 0: 
             Tetrix(*Ecran);
        break;
        case 1:      
             AffichageDesOptions(Ecran);
        break;
        case 2:
             Fond = SDL_LoadBMP("Ressources\\Ecran Commandes.bmp");
             SDL_BlitSurface( Fond, NULL, Ecran, &Coordonnee0);
             SDL_Flip(Ecran);
             SDL_FreeSurface(Fond);       
             PauseE(*Ecran);
        break;
        case 3:      
              AffichageDuScore(Ecran);
        break;
        case 4:
               SDL_FreeSurface(Ecran);
               SDL_FreeSurface(Fond);
               TTF_Quit();
               SDL_Quit();
               //exit(0);
        break;}    
}
 
