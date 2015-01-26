#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "score.h"

/********************************Affichage du score****************************/

void AffichageDuScore( SDL_Surface *Ecran)
{/* Déclaration des variables et surfaces */
 static SDL_Surface *Fond;
 static SDL_Surface *AffichageDuScore[10];
 static int Lignes[10] = {0}, Points[10] = {0}, i = 0, j = 0;
 static char TexteDuScore[10][50];
 static SDL_Rect Coordonne0 = {0,0}, CoordonneScore[10];

 /* Déclaration TTF */ 
 FILE* FichierScore;
 SDL_Color Vert = {0,255,0};
 TTF_Font *Police;
 
 /* Initialisations des coordonnées des scores */
 CoordonneScore[0].x = 30;
 CoordonneScore[0].y = 100;
 CoordonneScore[1].x = 30;
 CoordonneScore[1].y = 130;
 CoordonneScore[2].x = 30;
 CoordonneScore[2].y = 160;
 CoordonneScore[3].x = 30;
 CoordonneScore[3].y = 190;
 CoordonneScore[4].x = 30;
 CoordonneScore[4].y = 220;
 CoordonneScore[5].x = 30;
 CoordonneScore[5].y = 250;
 CoordonneScore[6].x = 30;
 CoordonneScore[6].y = 280;
 CoordonneScore[7].x = 30;
 CoordonneScore[7].y = 310;
 CoordonneScore[8].x = 30;
 CoordonneScore[8].y = 340;
 CoordonneScore[9].x = 30;
 CoordonneScore[9].y = 370;
 
 /* Initialisation */ 
 Police = TTF_OpenFont("Fonts\\times.ttf", 20);
 Fond = SDL_LoadBMP("Ressources\\Ecran Score.bmp");
 FichierScore = fopen( "Files\\men5.scrs", "r");
 
 /* Lecture des scores */
 //if ( FichierScore == NULL) {exit(0);};
 fscanf(FichierScore, "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", &Lignes[0], &Points[0], &Lignes[1], &Points[1] ,&Lignes[2], &Points[2],&Lignes[3], &Points[3],&Lignes[4], &Points[4],&Lignes[5], &Points[5],&Lignes[6], &Points[6],&Lignes[7], &Points[7], &Lignes[8], &Points[8], &Lignes[9], &Points[9]);

 /* Ecriture des scores */ 
 sprintf(TexteDuScore[0], "Le premier à fait %ld points en %ld lignes",   Points[0], Lignes[0]);
 sprintf(TexteDuScore[1], "Le second à fait %ld points en %ld lignes",    Points[1], Lignes[1]);
 sprintf(TexteDuScore[2], "Le troisième à fait %ld points en %ld lignes", Points[2], Lignes[2]);
 sprintf(TexteDuScore[3], "Le quatrième à fait %ld points en %ld lignes", Points[3], Lignes[3]);
 sprintf(TexteDuScore[4], "Le cinquième à fait %ld points en %ld lignes", Points[4], Lignes[4]);
 sprintf(TexteDuScore[5], "Le sixième à fait %ld points en %ld lignes",   Points[5], Lignes[5]);
 sprintf(TexteDuScore[6], "Le septième à fait %ld points en %ld lignes",  Points[6], Lignes[6]);
 sprintf(TexteDuScore[7], "Le huitième à fait %ld points en %ld lignes",  Points[7], Lignes[7]);
 sprintf(TexteDuScore[8], "Le neuvième à fait %ld points en %ld lignes",  Points[8], Lignes[8]);
 sprintf(TexteDuScore[9], "Le dixième à fait %ld points en %ld lignes",   Points[9], Lignes[9]);
 
 /* Inscriptions des score */
 AffichageDuScore[0] = TTF_RenderText_Blended( Police, TexteDuScore[0], Vert);
 AffichageDuScore[1] = TTF_RenderText_Blended( Police, TexteDuScore[1], Vert);   
 AffichageDuScore[2] = TTF_RenderText_Blended( Police, TexteDuScore[2], Vert);   
 AffichageDuScore[3] = TTF_RenderText_Blended( Police, TexteDuScore[3], Vert);   
 AffichageDuScore[4] = TTF_RenderText_Blended( Police, TexteDuScore[4], Vert);   
 AffichageDuScore[5] = TTF_RenderText_Blended( Police, TexteDuScore[5], Vert);   
 AffichageDuScore[6] = TTF_RenderText_Blended( Police, TexteDuScore[6], Vert);   
 AffichageDuScore[7] = TTF_RenderText_Blended( Police, TexteDuScore[7], Vert);   
 AffichageDuScore[8] = TTF_RenderText_Blended( Police, TexteDuScore[8], Vert);   
 AffichageDuScore[9] = TTF_RenderText_Blended( Police, TexteDuScore[9], Vert);
 
 /* Blit des surfaces */ 
 SDL_BlitSurface ( Fond, NULL, Ecran, &Coordonne0);
 SDL_BlitSurface ( AffichageDuScore[0], NULL, Ecran, &CoordonneScore[0]);
 SDL_BlitSurface ( AffichageDuScore[1], NULL, Ecran, &CoordonneScore[1]);
 SDL_BlitSurface ( AffichageDuScore[2], NULL, Ecran, &CoordonneScore[2]);
 SDL_BlitSurface ( AffichageDuScore[3], NULL, Ecran, &CoordonneScore[3]);
 SDL_BlitSurface ( AffichageDuScore[4], NULL, Ecran, &CoordonneScore[4]);
 SDL_BlitSurface ( AffichageDuScore[5], NULL, Ecran, &CoordonneScore[5]);
 SDL_BlitSurface ( AffichageDuScore[6], NULL, Ecran, &CoordonneScore[6]);
 SDL_BlitSurface ( AffichageDuScore[7], NULL, Ecran, &CoordonneScore[7]);
 SDL_BlitSurface ( AffichageDuScore[8], NULL, Ecran, &CoordonneScore[8]);
 SDL_BlitSurface ( AffichageDuScore[9], NULL, Ecran, &CoordonneScore[9]);
 SDL_Flip(Ecran);
 
 /* Attente pour quitter */
 PauseE(Ecran);             
  
 /* Fermeture */
 fclose(FichierScore);  
 SDL_FreeSurface(Fond);
 SDL_FreeSurface(AffichageDuScore[0]);
 SDL_FreeSurface(AffichageDuScore[1]);
 SDL_FreeSurface(AffichageDuScore[2]);
 SDL_FreeSurface(AffichageDuScore[3]);
 SDL_FreeSurface(AffichageDuScore[4]);
 SDL_FreeSurface(AffichageDuScore[5]);
 SDL_FreeSurface(AffichageDuScore[6]);
 SDL_FreeSurface(AffichageDuScore[7]);
 SDL_FreeSurface(AffichageDuScore[8]);
 SDL_FreeSurface(AffichageDuScore[9]);
}



/********************************Entré du score********************************/

int EntreDuScore(int NombreDeLignes, int NombreDePoints)
{/* Initialisation */
 int Lignes[10] = {0}, Point[10] = {0}, Valide = 0, i = 0, j = 0;
 FILE* FichierScore;
 FichierScore = fopen( "Files\\men5.scrs", "r");

 /* Lecture des scores */
// if ( FichierScore == NULL) {exit(0);};
 fscanf(FichierScore, "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", &Lignes[0], &Point[0], &Lignes[1], &Point[1] ,&Lignes[2], &Point[2],&Lignes[3], &Point[3],&Lignes[4], &Point[4],&Lignes[5], &Point[5],&Lignes[6], &Point[6],&Lignes[7], &Point[7], &Lignes[8], &Point[8], &Lignes[9], &Point[9]);
 
 /* Comparaison des scores du score */
 for (i=0; i<=9; i++)
     {if( NombreDePoints > Point[i] && Valide == 0)
         { Valide = 1;
           for(j=9; j>i; j--) 
              {Point[j] = Point[j-1];
               Lignes[j] = Lignes[j-1];}
           Point[i] = NombreDePoints;
           Lignes[i] = NombreDeLignes;
         }
      }
 
 /* Ecriture du score */
 fclose(FichierScore);
 FichierScore == fopen( "Files\\men5.scrs", "w+");
// if ( FichierScore == NULL) {exit(0);};
 fprintf( FichierScore, "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", Lignes[0], Point[0], Lignes[1], Point[1] ,Lignes[2], Point[2], Lignes[3], Point[3], Lignes[4], Point[4], Lignes[5], Point[5], Lignes[6], Point[6], Lignes[7], Point[7], Lignes[8], Point[8], Lignes[9], Point[9]);
 
 /* Retourne s'il y a eut un record */
 fclose(FichierScore);
 return Valide;
}
