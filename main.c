#include <stdlib.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include <SDL.h>
#include "menu.h"
#include "pause.h"
#include "main.h"


int main(int argc, char *argv[])
{/* Initialisation principale */
 
 /* Initialisation de l'écran */
 SDL_Rect Coordonnee0 = {0,0};
 SDL_Surface *Ecran;
 SDL_Surface *Fond;

 int Stop = 0, FormatDeLEcran = 2, Niveau = 0, Handicap = 0;

 SDL_Init(SDL_INIT_VIDEO);
 TTF_Init();
 SDL_WM_SetCaption("The Tetrix", NULL);
 SDL_WM_SetIcon(SDL_LoadBMP("Ressources\\Icone.bmp"), NULL);
 SDL_ShowCursor(SDL_DISABLE);

 /* Prise en compte des options */
 Options( &FormatDeLEcran, &Niveau, &Handicap); 
 		 
 if ( FormatDeLEcran == 1 ) {Ecran = SDL_SetVideoMode( ( 10 * CARRE ) + MARGE, LONGUEURE, 32, SDL_HWSURFACE  | SDL_DOUBLEBUF | SDL_FULLSCREEN);}
 if ( FormatDeLEcran == 2 ) {Ecran = SDL_SetVideoMode( ( 10 * CARRE ) + MARGE, LONGUEURE, 32, SDL_HWSURFACE  | SDL_DOUBLEBUF );} 
 
 /* Affichage initiale */

 Fond = SDL_LoadBMP("Ressources\\Ecran Titre.bmp");
 SDL_BlitSurface( Fond, NULL, Ecran, &Coordonnee0);
 SDL_Flip(Ecran);
 PauseS(Ecran);
 SDL_FreeSurface(Fond);
 
 /* Lancement du jeu */
 CaracteristiqueDesBloc();
 while (!Stop)
 {Menu(Ecran, &Stop);}
 
 /* Fermeture */ 
 free(&Stop);
 free(&FormatDeLEcran);
 free(&Niveau);
 free(&Handicap);
 free(&Coordonnee0);
 SDL_FreeSurface(Ecran);
 SDL_FreeSurface(Fond);
 TTF_Quit();
 SDL_Quit();
 return 0;
}
