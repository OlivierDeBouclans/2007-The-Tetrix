#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include "main.h"
#include "option.h"


/************************Affichage des options*********************************/

void AffichageDesOptions ( SDL_Surface *Ecran)
{/* Initialisation */
 int Continuer = 1, i = 0, FormatDeLEcran = 1, Niveau = 0, Handicap = 0;
 FILE* FichierINI;
 SDL_Event Event;
 static SDL_Surface *Fond, *PetitCarre[3], *Ligne;
 static SDL_Rect Coordonnee0 = {0,0}, CoordonneCarre[3], CoordonneeLigne = {22,232};
 
 SDL_EnableKeyRepeat(50,100);
 /* Initialisation des coordonnées des petit carré */
 CoordonneCarre[0].x = 142;
 CoordonneCarre[0].y = 215;
 CoordonneCarre[1].x = 196;
 CoordonneCarre[1].y = 258;
 CoordonneCarre[2].x = 130;
 CoordonneCarre[2].y = 301;

 /* Lecture des options */
 Options( &FormatDeLEcran, &Niveau, &Handicap);
 
 /* Placement du curseur pour l'écran */
 if(FormatDeLEcran == 2) {CoordonneCarre[0].x = 313;}
 
 
 /* Placement du curseur pour le niveau */
 switch(Niveau)
       {case 1: CoordonneCarre[1].x += 21;
        break;
        case 2: CoordonneCarre[1].x += 2*21;
        break;
        case 3: CoordonneCarre[1].x += 3*21;
        break;
        case 4: CoordonneCarre[1].x += 4*21;
        break;
        case 5: CoordonneCarre[1].x += 5*21;
        break;
        case 6: CoordonneCarre[1].x += 6*21;
        break;
        case 7: CoordonneCarre[1].x += 7*21;
        break;
        case 8: CoordonneCarre[1].x += 8*21;
        break;
        case 9: CoordonneCarre[1].x += 9*21;
        break;}
  
 /* Placement du curseur pour l'handicap */
 switch(Handicap)
       {case 1: CoordonneCarre[2].x += 21;
        break;
        case 2: CoordonneCarre[2].x += 2*21;
        break;
        case 3: CoordonneCarre[2].x += 3*21;
        break;
        case 4: CoordonneCarre[2].x += 4*21;
        break;
        case 5: CoordonneCarre[2].x += 5*21;
        break;}
             
 /* Initialisation des surface */
 Fond = SDL_LoadBMP("Ressources\\Ecran Options.bmp");
 Ligne = SDL_LoadBMP("Ressources\\Options 1.bmp");
 PetitCarre[0] = SDL_LoadBMP("Ressources\\Options Chiffre.bmp");
 PetitCarre[1] = SDL_LoadBMP("Ressources\\Options Chiffre.bmp");
 PetitCarre[2] = SDL_LoadBMP("Ressources\\Options Chiffre.bmp");
 SDL_SetColorKey( PetitCarre[0], SDL_SRCCOLORKEY, SDL_MapRGB(PetitCarre[0]->format, 0, 0, 0));
 SDL_SetColorKey( PetitCarre[1], SDL_SRCCOLORKEY, SDL_MapRGB(PetitCarre[1]->format, 0, 0, 0));
 SDL_SetColorKey( PetitCarre[2], SDL_SRCCOLORKEY, SDL_MapRGB(PetitCarre[2]->format, 0, 0, 0));

 /* Blit des surfaces */
 SDL_BlitSurface( Fond, NULL, Ecran,  &Coordonnee0);
 SDL_BlitSurface( Ligne, NULL, Ecran, &CoordonneeLigne);
 SDL_BlitSurface( PetitCarre[0], NULL, Ecran, &CoordonneCarre[0]);
 SDL_BlitSurface( PetitCarre[1], NULL, Ecran, &CoordonneCarre[1]);
 SDL_BlitSurface( PetitCarre[2], NULL, Ecran, &CoordonneCarre[2]);
 SDL_Flip(Ecran);

 /* Boucle de choix des options */
 while(Continuer)
      {SDL_WaitEvent(&Event);
       if(Event.type == SDL_QUIT){exit(0);}
       if(Event.type == SDL_KEYDOWN){
         switch(Event.key.keysym.sym)
             {case SDLK_ESCAPE:
                   Continuer = 0;
              break;
              case SDLK_DOWN:
                   if(CoordonneeLigne.y < 322) {CoordonneeLigne.y += 45;}
                   if(CoordonneeLigne.y == 232){Ligne = SDL_LoadBMP("Ressources\\Options 1.bmp");}
                   if(CoordonneeLigne.y == 277){Ligne = SDL_LoadBMP("Ressources\\Options 2.bmp");}
                   if(CoordonneeLigne.y == 322){Ligne = SDL_LoadBMP("Ressources\\Options 3.bmp");}
                   SDL_BlitSurface( Fond, NULL, Ecran, &Coordonnee0);
                   SDL_BlitSurface( Ligne, NULL, Ecran, &CoordonneeLigne);
                   SDL_BlitSurface( PetitCarre[0], NULL, Ecran, &CoordonneCarre[0]);
                   SDL_BlitSurface( PetitCarre[1], NULL, Ecran, &CoordonneCarre[1]);
                   SDL_BlitSurface( PetitCarre[2], NULL, Ecran, &CoordonneCarre[2]);
                   SDL_Flip(Ecran);
              break;
              case SDLK_UP:
                   if(CoordonneeLigne.y > 232) {CoordonneeLigne.y -= 45;}
                   if(CoordonneeLigne.y == 232){Ligne = SDL_LoadBMP("Ressources\\Options 1.bmp");}
                   if(CoordonneeLigne.y == 277){Ligne = SDL_LoadBMP("Ressources\\Options 2.bmp");}
                   if(CoordonneeLigne.y == 322){Ligne = SDL_LoadBMP("Ressources\\Options 3.bmp");}
                   SDL_BlitSurface( Fond, NULL, Ecran, &Coordonnee0);
                   SDL_BlitSurface( Ligne, NULL, Ecran, &CoordonneeLigne);
                   SDL_BlitSurface( PetitCarre[0], NULL, Ecran, &CoordonneCarre[0]);
                   SDL_BlitSurface( PetitCarre[1], NULL, Ecran, &CoordonneCarre[1]);
                   SDL_BlitSurface( PetitCarre[2], NULL, Ecran, &CoordonneCarre[2]);
                   SDL_Flip(Ecran);
              break;
              case SDLK_RIGHT:
                   if(CoordonneeLigne.y == 232){ CoordonneCarre[0].x = 313;}
                   if(CoordonneeLigne.y == 277 && CoordonneCarre[1].x < 380){ CoordonneCarre[1].x += 21;}
                   if(CoordonneeLigne.y == 322 && CoordonneCarre[2].x < 230){ CoordonneCarre[2].x += 21;}
                   SDL_BlitSurface( Fond, NULL, Ecran, &Coordonnee0);
                   SDL_BlitSurface( Ligne, NULL, Ecran, &CoordonneeLigne);
                   SDL_BlitSurface( PetitCarre[0], NULL, Ecran, &CoordonneCarre[0]);
                   SDL_BlitSurface( PetitCarre[1], NULL, Ecran, &CoordonneCarre[1]);
                   SDL_BlitSurface( PetitCarre[2], NULL, Ecran, &CoordonneCarre[2]);
                   SDL_Flip(Ecran);
              break;
              case SDLK_LEFT:
                   if(CoordonneeLigne.y == 232){ CoordonneCarre[0].x = 142;}
                   if(CoordonneeLigne.y == 277 && CoordonneCarre[1].x > 196){ CoordonneCarre[1].x -= 21;}
                   if(CoordonneeLigne.y == 322 && CoordonneCarre[2].x > 130){ CoordonneCarre[2].x -= 21;}
                   SDL_BlitSurface( Fond, NULL, Ecran, &Coordonnee0);
                   SDL_BlitSurface( Ligne, NULL, Ecran, &CoordonneeLigne);
                   SDL_BlitSurface( PetitCarre[0], NULL, Ecran, &CoordonneCarre[0]);
                   SDL_BlitSurface( PetitCarre[1], NULL, Ecran, &CoordonneCarre[1]);
                   SDL_BlitSurface( PetitCarre[2], NULL, Ecran, &CoordonneCarre[2]);
                   SDL_Flip(Ecran);
              break;
              case SDLK_RETURN:
                   if(CoordonneCarre[0].x == 142){FormatDeLEcran = 1 ;}
                   if(CoordonneCarre[0].x == 313){FormatDeLEcran = 2 ;}
                   Niveau   = (CoordonneCarre[1].x - 196)/ 21 ;
                   Handicap = (CoordonneCarre[2].x - 130)/ 21 ;
                   Continuer = 0;
              break;}}
}
 
       
 /* Ecriture des nouvelles options */
 FichierINI = fopen( "Files\\Tetrix.ini", "w");
 if ( FichierINI == NULL) {exit(0);}
 fprintf(FichierINI, "%ld %ld %ld", FormatDeLEcran, Niveau, Handicap);
 fclose(FichierINI);
 
 /* Redimensionnement de l'écran */
 if ( FormatDeLEcran == 1 ) {Ecran = SDL_SetVideoMode( ( 10 * CARRE ) + MARGE, LONGUEURE, 32, SDL_HWSURFACE  | SDL_DOUBLEBUF | SDL_FULLSCREEN);}
 if ( FormatDeLEcran == 2 ) {Ecran = SDL_SetVideoMode( ( 10 * CARRE ) + MARGE, LONGUEURE, 32, SDL_HWSURFACE  | SDL_DOUBLEBUF );} 

 /* Fermeture */
 free(&Event);
 free(FichierINI);
 free(&Continuer);
 free(&i);
 free(&FormatDeLEcran);
 free(&Niveau);
 free(&Handicap);
 free(&Coordonnee0);
 free(&CoordonneeLigne);
 free(&CoordonneCarre[0]);
 free(&CoordonneCarre[1]);
 free(&CoordonneCarre[2]);
 SDL_FreeSurface(Fond);
 SDL_FreeSurface(PetitCarre[0]);
 SDL_FreeSurface(PetitCarre[1]);
 SDL_FreeSurface(PetitCarre[2]);
 SDL_FreeSurface(Ligne);
}


/*****************************Options (prise en charge des options)************/

void Options( int *FormatDeLEcran, int *Niveau, int *Handicap)
{/* Initialisation */
 FILE* FichierINI;
 FichierINI = fopen( "Files\\Tetrix.ini", "r");
 if ( FichierINI == NULL) {exit(0);}
 
 /* Lecture des options */
 fscanf(FichierINI, "%ld %ld %ld", FormatDeLEcran, Niveau, Handicap);
 
 /* Fermeture */
 fclose(FichierINI);
 free(FichierINI);
}



