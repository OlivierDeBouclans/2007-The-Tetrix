#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "pause.h"
#include "main.h"
#include "jeu.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "option.h"

static Caracteristiques Bloc[23];

/******************************FONCTION TETRIX*********************************/

void Tetrix( SDL_Surface *Ecran)
{//                             INITIALISATION



 /* Initialisation des surfaces*/
 static SDL_Surface *Fond, *Pause, *BlocEnCours, *BlocPlace, *BlocValide, *PreBloc, *Erreur;
 static SDL_Surface *Fin, *Lignes, *Score, *Level, *Bravo;
 SDL_Rect Coordonnee0 = {0,0}, CoordonneePreBloc = {320, 130}, CoordonneeBravo = {25,425};

 /* Initialisation de toutes les variables */
    //BLOC
 int CoordonneeDuBloc = 0;
    //OPTION
 int FormatDeLEcran = 0, Niveau = 0, Handicap = 0;
    //PARCOUR
 int i = 0, j = 0, k = 0, o = 0, m[5] = {0,0,0,0,0};
    //CADRILLAGE
 char Libre[ ( ( ( LONGUEURE / CARRE ) *10 ) + 10 ) * 10 ];
 SDL_Rect Coordonnee[ ( ( ( LONGUEURE / CARRE ) *10 ) + 10 ) * 10 ];
    //GAMEPLAY
 int Temps1 = 0, PeutContinuer = 1, Continuer = 1, ChoixDuBloc = 1, Tourner = 0;
 int Temps2, Vitesse = 1000 - Niveau*100, Poursuivre = 1, PreChoixDuBloc;
 SDL_Event Event;
    //TEXTE
 int Point = 0, NombreDeLigne = 0, TNiveau = 0;
 char NBLignes[20] = "", NBScore[20] = "", NBNiveau[20] = "";
 SDL_Rect CoordonneeLignes = {350, 320}, CoordonneeScore = {350, 410}, CoordonneeNiveau = {350,485};
 SDL_Color Vert = {0, 255, 0};
 TTF_Font *Police;

 Options( &FormatDeLEcran, &Niveau, &Handicap);
 Temps2 = SDL_GetTicks();
 PreChoixDuBloc = ( ( rand() - SDL_GetTicks() ) % 7 ) + 1;

 Bravo      = SDL_LoadBMP("Ressources\\Bloc Record.bmp");
 Pause      = SDL_LoadBMP("Ressources\\Ecran Pause.bmp");
 Fond       = SDL_LoadBMP("Ressources\\Ecran Principale.bmp");
 BlocPlace  = SDL_LoadBMP("Ressources\\Bloc Vert.bmp");
 BlocValide = SDL_LoadBMP("Ressources\\Bloc Rouge.bmp");
 Erreur     = SDL_LoadBMP("Ressources\\Bloc Erreur.bmp");
 Fin        = SDL_LoadBMP("Ressources\\Ecran Fin.bmp");
 SDL_SetColorKey( Fin, SDL_SRCCOLORKEY, SDL_MapRGB(Fin->format, 255, 255, 255));
 SDL_EnableKeyRepeat(180, 40);

 /* Initialisation du cadrillage initiale */
 for ( i=0; i<= ( LONGUEURE / CARRE ) *10; i++)
     {Libre[i] = 1;}
 for ( i= (( LONGUEURE / CARRE ) *10); i<= (( ( ( LONGUEURE / CARRE ) *10 ) + 10 ) * 10); i++)
     {Libre[i] = 0;}
 for (i=200; i>200 - 10*Handicap; i--)
     {if ( rand()%2 == 0) {Libre[i] = 0;}}

 /* Initialisation des coordonnées possibles */
 Coordonnee[0].x = 0;
 Coordonnee[0].y = 0;
 j = 0;
 for ( i=1; i < ( ( ( LONGUEURE / CARRE ) *10 ) + 10 ) * 10; i++)
     {j += CARRE;
      if ((i % 10) == 0)
         {j = 0;}
      Coordonnee[i].x = j;}
 j = 0;
 for ( i=1; i < ( ( ( LONGUEURE / CARRE ) *10 ) + 10 ) * 10; i++)
     {if ((i % 10) == 0)
         {j += CARRE;}
      Coordonnee[i].y = j;}

 /* Initialisation de l'affichage textuel */
 Police = TTF_OpenFont("Fonts\\courant.ttf", 20);
 sprintf(NBLignes, "%ld", NombreDeLigne);
 sprintf(NBScore,  "%ld", Point);
 sprintf(NBNiveau, "%ld", TNiveau);
 Lignes = TTF_RenderText_Blended( Police, NBLignes, Vert);
 Score  = TTF_RenderText_Blended( Police, NBScore, Vert);
 Level  = TTF_RenderText_Blended( Police, NBNiveau, Vert);

 //                             Le Game Play du Jeu

 /* Début de la boucle: "Tant que la partie peut continuer" */
  while(PeutContinuer){

 /* Selection du bloc... */
 if ( Tourner == 0 )
    {ChoixDuBloc = PreChoixDuBloc;
     PreChoixDuBloc = ( ( rand() - SDL_GetTicks() ) % 7 ) + 1;

    /*... avec vérification de la défaite... */
     if ( Libre[3 + Bloc[ChoixDuBloc].BlocDuBloc1] == 0 || Libre[3 + Bloc[ChoixDuBloc].BlocDuBloc2] == 0 || Libre[3 + Bloc[ChoixDuBloc].BlocDuBloc3] == 0 || Libre[3 + Bloc[ChoixDuBloc].BlocDuBloc4] == 0)
        { PeutContinuer = 0; }
    }

 /* ... et ses conséquences */
 switch(PreChoixDuBloc)
       {SDL_FreeSurface(PreBloc);
        case 1 : PreBloc = SDL_LoadBMP("Ressources\\Bloc 1-0.bmp");
        break;
        case 11: PreBloc = SDL_LoadBMP("Ressources\\Bloc 1-1.bmp");
        break;
        case 12: PreBloc = SDL_LoadBMP("Ressources\\Bloc 1-2.bmp");
        break;
        case 13: PreBloc = SDL_LoadBMP("Ressources\\Bloc 1-3.bmp");
        break;
        case 2 : PreBloc = SDL_LoadBMP("Ressources\\Bloc 2-0.bmp");
        break;
        case 3 : PreBloc = SDL_LoadBMP("Ressources\\Bloc 3-0.bmp");
        break;
        case 14: PreBloc = SDL_LoadBMP("Ressources\\Bloc 3-1.bmp");
        break;
        case 4 : PreBloc = SDL_LoadBMP("Ressources\\Bloc 4-0.bmp");
        break;
        case 15: PreBloc = SDL_LoadBMP("Ressources\\Bloc 4-1.bmp");
        break;
        case 5 : PreBloc = SDL_LoadBMP("Ressources\\Bloc 5-0.bmp");
        break;
        case 16: PreBloc = SDL_LoadBMP("Ressources\\Bloc 5-1.bmp");
        break;
        case 6 : PreBloc = SDL_LoadBMP("Ressources\\Bloc 6-0.bmp");
        break;
        case 17: PreBloc = SDL_LoadBMP("Ressources\\Bloc 6-1.bmp");
        break;
        case 18: PreBloc = SDL_LoadBMP("Ressources\\Bloc 6-2.bmp");
        break;
        case 19: PreBloc = SDL_LoadBMP("Ressources\\Bloc 6-3.bmp");
        break;
        case 7 : PreBloc = SDL_LoadBMP("Ressources\\Bloc 7-0.bmp");
        break;
        case 20: PreBloc = SDL_LoadBMP("Ressources\\Bloc 7-1.bmp");
        break;
        case 21: PreBloc = SDL_LoadBMP("Ressources\\Bloc 7-2.bmp");
        break;
        case 22: PreBloc = SDL_LoadBMP("Ressources\\Bloc 7-3.bmp");
        break;}

 switch(ChoixDuBloc)
       {SDL_FreeSurface(BlocEnCours);
        case 1 : BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 1-0.bmp");
        break;
        case 11: BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 1-1.bmp");
        break;
        case 12: BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 1-2.bmp");
        break;
        case 13: BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 1-3.bmp");
        break;
        case 2 : BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 2-0.bmp");
        break;
        case 3 : BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 3-0.bmp");
        break;
        case 14: BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 3-1.bmp");
        break;
        case 4 : BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 4-0.bmp");
        break;
        case 15: BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 4-1.bmp");
        break;
        case 5 : BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 5-0.bmp");
        break;
        case 16: BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 5-1.bmp");
        break;
        case 6 : BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 6-0.bmp");
        break;
        case 17: BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 6-1.bmp");
        break;
        case 18: BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 6-2.bmp");
        break;
        case 19: BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 6-3.bmp");
        break;
        case 7 : BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 7-0.bmp");
        break;
        case 20: BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 7-1.bmp");
        break;
        case 21: BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 7-2.bmp");
        break;
        case 22: BlocEnCours = SDL_LoadBMP("Ressources\\Bloc 7-3.bmp");
        break;}
 SDL_SetColorKey( BlocEnCours, SDL_SRCCOLORKEY, SDL_MapRGB(BlocEnCours->format, 255, 255, 255));
 SDL_SetColorKey( PreBloc, SDL_SRCCOLORKEY, SDL_MapRGB(PreBloc->format, 255, 255, 255));

 /* Initialisation avant le départ de la boucle du gameplay */
 if (Tourner == 0)
    {SDL_BlitSurface( Fond, NULL, Ecran, &Coordonnee0);
     SDL_BlitSurface( Lignes, NULL, Ecran, &CoordonneeLignes);
     SDL_BlitSurface( Score,  NULL, Ecran, &CoordonneeScore);
     SDL_BlitSurface( Level,  NULL, Ecran, &CoordonneeNiveau);
     SDL_BlitSurface( PreBloc, NULL, Ecran, &CoordonneePreBloc );
     for ( i=0; i < ( ( ( LONGUEURE / CARRE ) *10 ) + 10 ) * 10; i++ )
          {if (Libre[i] == 0)
          {SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[i]);}}
     SDL_BlitSurface( BlocEnCours, NULL, Ecran, &Coordonnee[3]);
     CoordonneeDuBloc = 3;}
 if (Tourner == 1)
    {SDL_BlitSurface( Fond, NULL, Ecran, &Coordonnee0);
     SDL_BlitSurface( Lignes, NULL, Ecran, &CoordonneeLignes);
     SDL_BlitSurface( Score,  NULL, Ecran, &CoordonneeScore);
     SDL_BlitSurface( Level,  NULL, Ecran, &CoordonneeNiveau);
     SDL_BlitSurface( PreBloc, NULL, Ecran, &CoordonneePreBloc );
     for ( i=0; i < ( ( ( LONGUEURE / CARRE ) *10 ) + 10 ) * 10; i++ )
          {if (Libre[i] == 0)
          {SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[i]);}}
     SDL_BlitSurface( BlocEnCours, NULL, Ecran, &Coordonnee[CoordonneeDuBloc]);}
 SDL_Flip(Ecran);
 Tourner = 0;
 Continuer = 1;

 /* Début de la boucle: "Tant que le bloc n'est pas bloqué" */
 while ( Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas1] != 0 && Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas2] != 0  && Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas3] != 0 && Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas4] != 0 && Continuer)
       {

 /* Début de la boucle: "Tant que le temps pour bouger n'est pas passé" */
 while ( Temps1 - Temps2 < Vitesse && Poursuivre)
       {

 /* Déroulement du temps et attente d'un évenement */
 Temps1 = SDL_GetTicks();
 SDL_PollEvent(&Event);

 /* Switch de déplacement du bloc */
 //if(Event.type == SDL_QUIT){exit(0);}
 if(Event.type == SDL_KEYDOWN){
                 switch (Event.key.keysym.sym)
                        {case SDLK_ESCAPE:
                              PeutContinuer = 0;
                              Continuer = 0;
                              Temps1 = Temps2 + Vitesse;
                         break;
                         case SDLK_PAUSE:
                              SDL_BlitSurface( Pause, NULL, Ecran, &Coordonnee0);
                              SDL_Flip(Ecran);
                              PauseS(Ecran);
                         break;
                         case SDLK_DOWN:
                             Temps1 = Temps2 + Vitesse;
                         break;
                         case SDLK_RETURN:
                             do{ CoordonneeDuBloc += 10;
                                 SDL_BlitSurface(BlocPlace, NULL, Ecran, &Coordonnee[CoordonneeDuBloc - 10 + Bloc[ChoixDuBloc].Largeur1]);
                                 SDL_BlitSurface(BlocPlace, NULL, Ecran, &Coordonnee[CoordonneeDuBloc - 10 + Bloc[ChoixDuBloc].Largeur2]);
                                 SDL_BlitSurface(BlocPlace, NULL, Ecran, &Coordonnee[CoordonneeDuBloc - 10 + Bloc[ChoixDuBloc].Largeur3]);
                                 SDL_BlitSurface(BlocPlace, NULL, Ecran, &Coordonnee[CoordonneeDuBloc - 10 + Bloc[ChoixDuBloc].Largeur4]);
                                 SDL_Flip(Ecran);}
                             while( Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas1] != 0 && Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas2] != 0  && Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas3] != 0 && Continuer);
                             SDL_BlitSurface(BlocPlace, NULL, Ecran, &Coordonnee[CoordonneeDuBloc+ Bloc[ChoixDuBloc].Largeur1]);
                             SDL_BlitSurface(BlocPlace, NULL, Ecran, &Coordonnee[CoordonneeDuBloc+ Bloc[ChoixDuBloc].Largeur2]);
                             SDL_BlitSurface(BlocPlace, NULL, Ecran, &Coordonnee[CoordonneeDuBloc+ Bloc[ChoixDuBloc].Largeur3]);
                             SDL_BlitSurface(BlocPlace, NULL, Ecran, &Coordonnee[CoordonneeDuBloc+ Bloc[ChoixDuBloc].Largeur4]);
                             SDL_Flip(Ecran);
                             CoordonneeDuBloc -= 10;
                             Temps1 = Temps2 + Vitesse;
                         break;
                         case SDLK_RIGHT:
                             CoordonneeDuBloc += 1;
                             if ( ( (CoordonneeDuBloc + Bloc[ChoixDuBloc].Largeur4 ) % 10 ) == 0 )
                                { CoordonneeDuBloc -= 1; };
                             if ( Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLaDroite1 ] == 0 || Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLaDroite2 ] == 0 || Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLaDroite3 ] == 0 || Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLaDroite4 ] == 0 )
                                { CoordonneeDuBloc -= 1; };
                             SDL_BlitSurface( Fond, NULL, Ecran, &Coordonnee0);
                             SDL_BlitSurface( Lignes, NULL, Ecran, &CoordonneeLignes);
                             SDL_BlitSurface( Score,  NULL, Ecran, &CoordonneeScore);
                             SDL_BlitSurface( Level,  NULL, Ecran, &CoordonneeNiveau);
                             SDL_BlitSurface( PreBloc, NULL, Ecran, &CoordonneePreBloc );
                             for ( i=0; i < ( ( ( LONGUEURE / CARRE ) *10 ) + 10 ) * 10; i++ )
                                 {if (Libre[i] == 0)
                                     {SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[i]);}
                                 }
                             SDL_BlitSurface( BlocEnCours, NULL, Ecran, &Coordonnee[CoordonneeDuBloc]);
                             SDL_Flip(Ecran);
                          break;
                          case SDLK_LEFT:
                             CoordonneeDuBloc -= 1;
                             if ( CoordonneeDuBloc == -1 )
                                { CoordonneeDuBloc += 1; };
                             if ( (CoordonneeDuBloc % 10 ) == 9)
                                { CoordonneeDuBloc += 1; };
                             if ( Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLaGauche1 ] == 0 || Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLaGauche2 ] == 0 || Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLaGauche3 ] == 0 || Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLaGauche4 ] == 0 )
                                { CoordonneeDuBloc += 1; };
                             SDL_BlitSurface( Fond, NULL, Ecran, &Coordonnee0);
                             SDL_BlitSurface( Lignes, NULL, Ecran, &CoordonneeLignes);
                             SDL_BlitSurface( Score,  NULL, Ecran, &CoordonneeScore);
                             SDL_BlitSurface( Level,  NULL, Ecran, &CoordonneeNiveau);
                             SDL_BlitSurface( PreBloc, NULL, Ecran, &CoordonneePreBloc );
                             for ( i=0; i < ( ( ( LONGUEURE / CARRE ) *10 ) + 10 ) * 10; i++ )
                                 {if (Libre[i] == 0)
                                     {SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[i]);}
                                 }
                             SDL_BlitSurface( BlocEnCours, NULL, Ecran, &Coordonnee[CoordonneeDuBloc]);
                             SDL_Flip(Ecran);
                          break;
                          case SDLK_RCTRL:
                              if ( Libre[CoordonneeDuBloc + Bloc[Rotation(ChoixDuBloc)].BlocDuBloc1] != 0 && Libre[CoordonneeDuBloc + Bloc[Rotation(ChoixDuBloc)].BlocDuBloc2] != 0 && Libre[CoordonneeDuBloc + Bloc[Rotation(ChoixDuBloc)].BlocDuBloc3] != 0 && Libre[CoordonneeDuBloc + Bloc[Rotation(ChoixDuBloc)].BlocDuBloc4] != 0)
                              {if ( ( CoordonneeDuBloc + Bloc[Rotation(ChoixDuBloc)].Largeur4 ) % 10 >  CoordonneeDuBloc % 10 || ChoixDuBloc == 14)
                               {Tourner = 1;
                                Poursuivre = 0;
                                Continuer = 0;}}
                          break;}
  Event.type = 0;}

 /* Fin de la boucle: "Tant que le temps pour bouger n'est pas passé" */
 }

 /* Déscente du bloc d'un carré*/
 if (Poursuivre){
 Temps1 = SDL_GetTicks();
 Temps2 = Temps1;
 SDL_BlitSurface( Fond, NULL, Ecran, &Coordonnee0);
 SDL_BlitSurface( Lignes, NULL, Ecran, &CoordonneeLignes);
 SDL_BlitSurface( Score,  NULL, Ecran, &CoordonneeScore);
 SDL_BlitSurface( Level,  NULL, Ecran, &CoordonneeNiveau);
 SDL_BlitSurface( PreBloc, NULL, Ecran, &CoordonneePreBloc );
 if ( Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas1] != 0 && Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas2] != 0  && Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas3] != 0 && Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas4] != 0)
    { CoordonneeDuBloc += 10;
 if ( Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas1] == 0 || Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas2] == 0  || Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas3] == 0 || Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas4] == 0 )
    { Continuer = 0;
      CoordonneeDuBloc -= 10;}
 for ( i=0; i < ( ( ( LONGUEURE / CARRE ) *10 ) + 10 ) * 10; i++ )
     { if (Libre[i] == 0)
          {SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[i]);}
     }
 SDL_BlitSurface( BlocEnCours, NULL, Ecran, &Coordonnee[CoordonneeDuBloc]);}
 SDL_Flip(Ecran);}

 /* Fin de la boucle: "Tant que le bloc n'est pas bloqué" */
 }

 /* Fossilisation du bloc... */
 if ( Tourner == 0)
   {if ( Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas1 + 10] == 0 || Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas2 + 10] == 0  || Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas3 + 10] == 0 || Libre[CoordonneeDuBloc + Bloc[ChoixDuBloc].BloqueurParLeBas4 + 10] == 0)
     {SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[CoordonneeDuBloc + Bloc[ChoixDuBloc].BlocDuBloc1 ]);
      SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[CoordonneeDuBloc + Bloc[ChoixDuBloc].BlocDuBloc2 ]);
      SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[CoordonneeDuBloc + Bloc[ChoixDuBloc].BlocDuBloc3 ]);
      SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[CoordonneeDuBloc + Bloc[ChoixDuBloc].BlocDuBloc4 ]);
      SDL_Flip(Ecran);
      Libre[ CoordonneeDuBloc + Bloc[ChoixDuBloc].BlocDuBloc1] = 0;
      Libre[ CoordonneeDuBloc + Bloc[ChoixDuBloc].BlocDuBloc2] = 0;
      Libre[ CoordonneeDuBloc + Bloc[ChoixDuBloc].BlocDuBloc3] = 0;
      Libre[ CoordonneeDuBloc + Bloc[ChoixDuBloc].BlocDuBloc4] = 0;
      Continuer = 1;
     }}

 /* ... ou pivotation */
 if ( Tourner == 1)
     {Poursuivre = 1;
      ChoixDuBloc = Rotation(ChoixDuBloc);}

 /* Vérification des lignes */
 for (i=0; i< ( LONGUEURE / CARRE ) * 10; i+=10)
    {if ( Libre[i] == 0 && Libre[i+1] == 0 && Libre[i+2] == 0 && Libre[i+3] == 0 && Libre[i+4] == 0 && Libre[i+5] == 0 && Libre[i+6] == 0 && Libre[i+7] == 0 && Libre[i+8] == 0 && Libre[i+9] == 0)
         {NombreDeLigne += 1;
          sprintf(NBLignes, "%ld", NombreDeLigne);
          Lignes = TTF_RenderText_Blended( Police, NBLignes, Vert);
          TNiveau = floor(NombreDeLigne / 10);
          sprintf(NBNiveau, "%ld", TNiveau);
          Level  = TTF_RenderText_Blended( Police, NBNiveau, Vert);
          o += 1;
          k += 1;
          m[o] = i;}
    }

 /* Animation des lignes completes */
 if ( k != 0)
     {for ( i=0; i<5; i++)
           {if ( k >= 1 ){
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[1]]  );
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[1]+1]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[1]+2]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[1]+3]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[1]+4]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[1]+5]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[1]+6]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[1]+7]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[1]+8]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[1]+9]);}

            if ( k >= 2 ){
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[2]]  );
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[2]+1]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[2]+2]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[2]+3]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[2]+4]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[2]+5]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[2]+6]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[2]+7]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[2]+8]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[2]+9]);}

            if ( k >= 3 ){
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[3]]  );
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[3]+1]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[3]+2]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[3]+3]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[3]+4]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[3]+5]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[3]+6]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[3]+7]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[3]+8]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[3]+9]);}

            if ( k >= 4 ){
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[4]]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[4]+1]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[4]+2]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[4]+3]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[4]+4]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[4]+5]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[4]+6]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[4]+7]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[4]+8]);
            SDL_BlitSurface( BlocPlace, NULL, Ecran, &Coordonnee[m[4]+9]);}

            SDL_Flip(Ecran);
            SDL_Delay(150);

            if ( k >= 1 ){
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[1]]  );
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[1]+1]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[1]+2]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[1]+3]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[1]+4]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[1]+5]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[1]+6]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[1]+7]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[1]+8]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[1]+9]);}

            if ( k >= 2 ){
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[2]]  );
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[2]+1]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[2]+2]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[2]+3]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[2]+4]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[2]+5]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[2]+6]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[2]+7]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[2]+8]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[2]+9]);}

            if ( k >= 3 ){
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[3]]  );
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[3]+1]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[3]+2]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[3]+3]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[3]+4]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[3]+5]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[3]+6]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[3]+7]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[3]+8]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[3]+9]);}

            if ( k >= 4 ){
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[4]]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[4]+1]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[4]+2]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[4]+3]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[4]+4]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[4]+5]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[4]+6]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[4]+7]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[4]+8]);
            SDL_BlitSurface( BlocValide, NULL, Ecran, &Coordonnee[m[4]+9]);}

            SDL_Flip(Ecran);
            SDL_Delay(150);
         }

     Point += (125*k) - 75;
     sprintf(NBScore, "%ld", Point);
     Score = TTF_RenderText_Blended( Police, NBScore, Vert);

     /* Gestions de la difficulté */
     if ( NombreDeLigne >= 10 && Niveau < 1)  {Vitesse = 900;}
     if ( NombreDeLigne >= 20 && Niveau < 2)  {Vitesse = 800;}
     if ( NombreDeLigne >= 30 && Niveau < 3)  {Vitesse = 700;}
     if ( NombreDeLigne >= 40 && Niveau < 4)  {Vitesse = 600;}
     if ( NombreDeLigne >= 50 && Niveau < 5)  {Vitesse = 500;}
     if ( NombreDeLigne >= 60 && Niveau < 6)  {Vitesse = 400;}
     if ( NombreDeLigne >= 70 && Niveau < 7)  {Vitesse = 300;}
     if ( NombreDeLigne >= 80 && Niveau < 8)  {Vitesse = 250;}
     if ( NombreDeLigne >= 90 && Niveau < 9)  {Vitesse = 200;}
     if ( NombreDeLigne >= 100) {Vitesse = 150;}
     if ( NombreDeLigne >= 110) {Vitesse = 100;}
     if ( NombreDeLigne >= 200) {Vitesse = 80 ;}

     k = 0;
     o = 0;
    }

 /* Décalage des lignes après effacement de celle complette */
 for (i=0; i< ( LONGUEURE / CARRE ) *10; i+=10)
    {if ( Libre[i] == 0 && Libre[i+1] == 0 && Libre[i+2] == 0 && Libre[i+3] == 0 && Libre[i+4] == 0 && Libre[i+5] == 0 && Libre[i+6] == 0 && Libre[i+7] == 0 && Libre[i+8] == 0 && Libre[i+9] == 0)
      {Libre[i]   = 1;
       Libre[i+1] = 1;
       Libre[i+2] = 1;
       Libre[i+3] = 1;
       Libre[i+4] = 1;
       Libre[i+5] = 1;
       Libre[i+6] = 1;
       Libre[i+7] = 1;
       Libre[i+8] = 1;
       Libre[i+9] = 1;
       for ( j=0; j <= (( LONGUEURE / CARRE ) + 10 ) * 10 ; j += 10)
            {if ( i-j >= 0 )
                 {Libre[i-j]  = Libre[i-j-10];
                  Libre[i+1-j] = Libre[i-j-9];
                  Libre[i+2-j] = Libre[i-j-8];
                  Libre[i+3-j] = Libre[i-j-7];
                  Libre[i+4-j] = Libre[i-j-6];
                  Libre[i+5-j] = Libre[i-j-5];
                  Libre[i+6-j] = Libre[i-j-4];
                  Libre[i+7-j] = Libre[i-j-3];
                  Libre[i+8-j] = Libre[i-j-2];
                  Libre[i+9-j] = Libre[i-j-1];}}
       Libre[0] = 1;
       Libre[1] = 1;
       Libre[2] = 1;
       Libre[3] = 1;
       Libre[4] = 1;
       Libre[5] = 1;
       Libre[6] = 1;
       Libre[7] = 1;
       Libre[8] = 1;
       Libre[9] = 1;}}

 /* Fin de la boucle: "tant que la partie peut continuer" */
 }

 /* Animation de l'échec */
 for (i = 0; i <= ( LONGUEURE / CARRE ) *10; i += 2)
      {SDL_BlitSurface( Erreur, NULL, Ecran, &Coordonnee[i]);
       SDL_Flip(Ecran);
       SDL_Delay(7);}
 SDL_Delay(1000);

 /* Affichage finale */
 SDL_BlitSurface( Fin, NULL, Ecran, &Coordonnee0);
 SDL_Flip(Ecran);
 Continuer = 1;

  /* S'il y a eut un record */
  if(EntreDuScore( NombreDeLigne, Point)) {SDL_BlitSurface( Bravo, NULL, Ecran, &CoordonneeBravo); SDL_Flip(Ecran);}
 PauseS(Ecran);

 /* Fermeture et libération des surfaces et variables de Jeu.c */
 TTF_CloseFont(Police);
 SDL_FreeSurface( Erreur     );
 SDL_FreeSurface( BlocValide );
 SDL_FreeSurface( BlocPlace  );
 SDL_FreeSurface( BlocEnCours);
 SDL_FreeSurface( Fond       );
 SDL_FreeSurface( PreBloc    );
 SDL_FreeSurface( Pause      );
 SDL_FreeSurface( Lignes     );
 SDL_FreeSurface( Score      );
 SDL_FreeSurface( Level      );
 SDL_FreeSurface( Fin        );
 SDL_FreeSurface( Bravo      );
}




/***********************FONCTION ROTATION**************************************/

int Rotation(int ChoixDuBloc)
{/* Fait correspondre un bloc à sa forme pivotée directement suivante */
 switch (ChoixDuBloc)
         {case 1 : ChoixDuBloc = 11;
          break;
          case 11: ChoixDuBloc = 12;
          break;
          case 12: ChoixDuBloc = 13;
          break;
          case 13: ChoixDuBloc = 1;
          break;
          case 2 : ChoixDuBloc = 2;
          break;
          case 3 : ChoixDuBloc = 14;
          break;
          case 14: ChoixDuBloc = 3;
          break;
          case 4 : ChoixDuBloc = 15;
          break;
          case 15: ChoixDuBloc = 4;
          break;
          case 5 : ChoixDuBloc = 16;
          break;
          case 16: ChoixDuBloc = 5;
          break;
          case 6 : ChoixDuBloc = 17;
          break;
          case 17: ChoixDuBloc = 18;
          break;
          case 18: ChoixDuBloc = 19;
          break;
          case 19: ChoixDuBloc = 6;
          break;
          case 7 : ChoixDuBloc = 20;
          break;
          case 20: ChoixDuBloc = 21;
          break;
          case 21: ChoixDuBloc = 22;
          break;
          case 22: ChoixDuBloc = 7;
          break;
         }
 return ChoixDuBloc;
}

/****************************Caractéristiques des bloc*************************/

void CaracteristiqueDesBloc()
{/* Initialisation des caractéristiques des blocs */
 Bloc[1].BloqueurParLeBas1    = 10;
 Bloc[1].BloqueurParLeBas2    = 11;
 Bloc[1].BloqueurParLeBas3    = 12;
 Bloc[1].BloqueurParLeBas4    = 12;
 Bloc[1].BloqueurParLaDroite1 = 1 ;
 Bloc[1].BloqueurParLaDroite2 = 12;
 Bloc[1].BloqueurParLaDroite3 = 12;
 Bloc[1].BloqueurParLaDroite4 = 12;
 Bloc[1].BloqueurParLaGauche1 = 1 ;
 Bloc[1].BloqueurParLaGauche2 = 10;
 Bloc[1].BloqueurParLaGauche3 = 10;
 Bloc[1].BloqueurParLaGauche4 = 10;
 Bloc[1].Largeur1 = 0;
 Bloc[1].Largeur2 = 1;
 Bloc[1].Largeur3 = 2;
 Bloc[1].Largeur4 = 2;
 Bloc[1].BlocDuBloc1 = 1 ;
 Bloc[1].BlocDuBloc2 = 10;
 Bloc[1].BlocDuBloc3 = 11;
 Bloc[1].BlocDuBloc4 = 12;

 Bloc[2].BloqueurParLeBas1    = 10;
 Bloc[2].BloqueurParLeBas2    = 11;
 Bloc[2].BloqueurParLeBas3    = 11;
 Bloc[2].BloqueurParLeBas4    = 11;
 Bloc[2].BloqueurParLaDroite1 = 1 ;
 Bloc[2].BloqueurParLaDroite2 = 11;
 Bloc[2].BloqueurParLaDroite3 = 11;
 Bloc[2].BloqueurParLaDroite4 = 11;
 Bloc[2].BloqueurParLaGauche1 = 0 ;
 Bloc[2].BloqueurParLaGauche2 = 10;
 Bloc[2].BloqueurParLaGauche3 = 10;
 Bloc[2].BloqueurParLaGauche4 = 10;
 Bloc[2].Largeur1 = 0;
 Bloc[2].Largeur2 = 1;
 Bloc[2].Largeur3 = 1;
 Bloc[2].Largeur4 = 1;
 Bloc[2].BlocDuBloc1 = 0 ;
 Bloc[2].BlocDuBloc2 = 1 ;
 Bloc[2].BlocDuBloc3 = 10;
 Bloc[2].BlocDuBloc4 = 11;

 Bloc[3].BloqueurParLeBas1    = 30;
 Bloc[3].BloqueurParLeBas2    = 30;
 Bloc[3].BloqueurParLeBas3    = 30;
 Bloc[3].BloqueurParLeBas4    = 30;
 Bloc[3].BloqueurParLaDroite1 = 0 ;
 Bloc[3].BloqueurParLaDroite2 = 10;
 Bloc[3].BloqueurParLaDroite3 = 20;
 Bloc[3].BloqueurParLaDroite4 = 30;
 Bloc[3].BloqueurParLaGauche1 = 0;
 Bloc[3].BloqueurParLaGauche2 = 10;
 Bloc[3].BloqueurParLaGauche3 = 20;
 Bloc[3].BloqueurParLaGauche4 = 30;
 Bloc[3].Largeur1 = 0;
 Bloc[3].Largeur2 = 0;
 Bloc[3].Largeur3 = 0;
 Bloc[3].Largeur4 = 0;
 Bloc[3].BlocDuBloc1 = 0 ;
 Bloc[3].BlocDuBloc2 = 10;
 Bloc[3].BlocDuBloc3 = 20;
 Bloc[3].BlocDuBloc4 = 30;

 Bloc[4].BloqueurParLeBas1    = 2;
 Bloc[4].BloqueurParLeBas2    = 10;
 Bloc[4].BloqueurParLeBas3    = 11;
 Bloc[4].BloqueurParLeBas4    = 11;
 Bloc[4].BloqueurParLaDroite1 = 2 ;
 Bloc[4].BloqueurParLaDroite2 = 11;
 Bloc[4].BloqueurParLaDroite3 = 11;
 Bloc[4].BloqueurParLaDroite4 = 11;
 Bloc[4].BloqueurParLaGauche1 = 1 ;
 Bloc[4].BloqueurParLaGauche2 = 10;
 Bloc[4].BloqueurParLaGauche3 = 10;
 Bloc[4].BloqueurParLaGauche4 = 10;
 Bloc[4].Largeur1 = 0;
 Bloc[4].Largeur2 = 1;
 Bloc[4].Largeur3 = 2;
 Bloc[4].Largeur4 = 2;
 Bloc[4].BlocDuBloc1 = 1 ;
 Bloc[4].BlocDuBloc2 = 2 ;
 Bloc[4].BlocDuBloc3 = 10;
 Bloc[4].BlocDuBloc4 = 11;

 Bloc[5].BloqueurParLeBas1    = 0 ;
 Bloc[5].BloqueurParLeBas2    = 11;
 Bloc[5].BloqueurParLeBas3    = 12;
 Bloc[5].BloqueurParLeBas4    = 12;
 Bloc[5].BloqueurParLaDroite1 = 1 ;
 Bloc[5].BloqueurParLaDroite2 = 12;
 Bloc[5].BloqueurParLaDroite3 = 12;
 Bloc[5].BloqueurParLaDroite4 = 12;
 Bloc[5].BloqueurParLaGauche1 = 0 ;
 Bloc[5].BloqueurParLaGauche2 = 11;
 Bloc[5].BloqueurParLaGauche3 = 11;
 Bloc[5].BloqueurParLaGauche4 = 11;
 Bloc[5].Largeur1 = 0;
 Bloc[5].Largeur2 = 1;
 Bloc[5].Largeur3 = 2;
 Bloc[5].Largeur4 = 2;
 Bloc[5].BlocDuBloc1 = 0 ;
 Bloc[5].BlocDuBloc2 = 1 ;
 Bloc[5].BlocDuBloc3 = 11;
 Bloc[5].BlocDuBloc4 = 12;

 Bloc[6].BloqueurParLeBas1    = 0 ;
 Bloc[6].BloqueurParLeBas2    = 21;
 Bloc[6].BloqueurParLeBas3    = 21;
 Bloc[6].BloqueurParLeBas4    = 21;
 Bloc[6].BloqueurParLaDroite1 = 1 ;
 Bloc[6].BloqueurParLaDroite2 = 11;
 Bloc[6].BloqueurParLaDroite3 = 21;
 Bloc[6].BloqueurParLaDroite4 = 21;
 Bloc[6].BloqueurParLaGauche1 = 0 ;
 Bloc[6].BloqueurParLaGauche2 = 11;
 Bloc[6].BloqueurParLaGauche3 = 21;
 Bloc[6].BloqueurParLaGauche4 = 21;
 Bloc[6].Largeur1 = 0;
 Bloc[6].Largeur2 = 1;
 Bloc[6].Largeur3 = 1;
 Bloc[6].Largeur4 = 1;
 Bloc[6].BlocDuBloc1 = 0 ;
 Bloc[6].BlocDuBloc2 = 1 ;
 Bloc[6].BlocDuBloc3 = 11;
 Bloc[6].BlocDuBloc4 = 21;

 Bloc[7].BloqueurParLeBas1    = 1 ;
 Bloc[7].BloqueurParLeBas2    = 20;
 Bloc[7].BloqueurParLeBas3    = 20;
 Bloc[7].BloqueurParLeBas4    = 20;
 Bloc[7].BloqueurParLaDroite1 = 1 ;
 Bloc[7].BloqueurParLaDroite2 = 10;
 Bloc[7].BloqueurParLaDroite3 = 20;
 Bloc[7].BloqueurParLaDroite4 = 20;
 Bloc[7].BloqueurParLaGauche1 = 0 ;
 Bloc[7].BloqueurParLaGauche2 = 10;
 Bloc[7].BloqueurParLaGauche3 = 20;
 Bloc[7].BloqueurParLaGauche4 = 20;
 Bloc[7].Largeur1 = 0;
 Bloc[7].Largeur2 = 1;
 Bloc[7].Largeur3 = 1;
 Bloc[7].Largeur4 = 1;
 Bloc[7].BlocDuBloc1 = 0 ;
 Bloc[7].BlocDuBloc2 = 1 ;
 Bloc[7].BlocDuBloc3 = 10;
 Bloc[7].BlocDuBloc4 = 20;

 Bloc[11].BloqueurParLeBas1    = 11;
 Bloc[11].BloqueurParLeBas2    = 20;
 Bloc[11].BloqueurParLeBas3    = 20;
 Bloc[11].BloqueurParLeBas4    = 20;
 Bloc[11].BloqueurParLaDroite1 = 0 ;
 Bloc[11].BloqueurParLaDroite2 = 11;
 Bloc[11].BloqueurParLaDroite3 = 20;
 Bloc[11].BloqueurParLaDroite4 = 20;
 Bloc[11].BloqueurParLaGauche1 = 0 ;
 Bloc[11].BloqueurParLaGauche2 = 10;
 Bloc[11].BloqueurParLaGauche3 = 20;
 Bloc[11].BloqueurParLaGauche4 = 20;
 Bloc[11].Largeur1 = 0;
 Bloc[11].Largeur2 = 1;
 Bloc[11].Largeur3 = 1;
 Bloc[11].Largeur4 = 1;
 Bloc[11].BlocDuBloc1 = 0 ;
 Bloc[11].BlocDuBloc2 = 10;
 Bloc[11].BlocDuBloc3 = 11;
 Bloc[11].BlocDuBloc4 = 20;

 Bloc[12].BloqueurParLeBas1    = 0 ;
 Bloc[12].BloqueurParLeBas2    = 2 ;
 Bloc[12].BloqueurParLeBas3    = 11;
 Bloc[12].BloqueurParLeBas4    = 11;
 Bloc[12].BloqueurParLaDroite1 = 2 ;
 Bloc[12].BloqueurParLaDroite2 = 11;
 Bloc[12].BloqueurParLaDroite3 = 11;
 Bloc[12].BloqueurParLaDroite4 = 11;
 Bloc[12].BloqueurParLaGauche1 = 0 ;
 Bloc[12].BloqueurParLaGauche2 = 11;
 Bloc[12].BloqueurParLaGauche3 = 11;
 Bloc[12].BloqueurParLaGauche4 = 11;
 Bloc[12].Largeur1 = 0;
 Bloc[12].Largeur2 = 1;
 Bloc[12].Largeur3 = 2;
 Bloc[12].Largeur4 = 2;
 Bloc[12].BlocDuBloc1 = 0 ;
 Bloc[12].BlocDuBloc2 = 1 ;
 Bloc[12].BlocDuBloc3 = 2 ;
 Bloc[12].BlocDuBloc4 = 11;

 Bloc[13].BloqueurParLeBas1    = 10;
 Bloc[13].BloqueurParLeBas2    = 21;
 Bloc[13].BloqueurParLeBas3    = 21;
 Bloc[13].BloqueurParLeBas4    = 21;
 Bloc[13].BloqueurParLaDroite1 = 1 ;
 Bloc[13].BloqueurParLaDroite2 = 11;
 Bloc[13].BloqueurParLaDroite3 = 21;
 Bloc[13].BloqueurParLaDroite4 = 21;
 Bloc[13].BloqueurParLaGauche1 = 1 ;
 Bloc[13].BloqueurParLaGauche2 = 10;
 Bloc[13].BloqueurParLaGauche3 = 21;
 Bloc[13].BloqueurParLaGauche4 = 21;
 Bloc[13].Largeur1 = 0;
 Bloc[13].Largeur2 = 1;
 Bloc[13].Largeur3 = 1;
 Bloc[13].Largeur4 = 1;
 Bloc[13].BlocDuBloc1 = 1 ;
 Bloc[13].BlocDuBloc2 = 10;
 Bloc[13].BlocDuBloc3 = 11;
 Bloc[13].BlocDuBloc4 = 21;

 Bloc[14].BloqueurParLeBas1    = 0 ;
 Bloc[14].BloqueurParLeBas2    = 1 ;
 Bloc[14].BloqueurParLeBas3    = 2 ;
 Bloc[14].BloqueurParLeBas4    = 3 ;
 Bloc[14].BloqueurParLaDroite1 = 3 ;
 Bloc[14].BloqueurParLaDroite2 = 3 ;
 Bloc[14].BloqueurParLaDroite3 = 3 ;
 Bloc[14].BloqueurParLaDroite4 = 3 ;
 Bloc[14].BloqueurParLaGauche1 = 0 ;
 Bloc[14].BloqueurParLaGauche2 = 0 ;
 Bloc[14].BloqueurParLaGauche3 = 0 ;
 Bloc[14].BloqueurParLaGauche4 = 0 ;
 Bloc[14].Largeur1 = 0;
 Bloc[14].Largeur2 = 1;
 Bloc[14].Largeur3 = 2;
 Bloc[14].Largeur4 = 3;
 Bloc[14].BlocDuBloc1 = 0;
 Bloc[14].BlocDuBloc2 = 1;
 Bloc[14].BlocDuBloc3 = 2;
 Bloc[14].BlocDuBloc4 = 3;

 Bloc[15].BloqueurParLeBas1    = 10;
 Bloc[15].BloqueurParLeBas2    = 21;
 Bloc[15].BloqueurParLeBas3    = 21;
 Bloc[15].BloqueurParLeBas4    = 21;
 Bloc[15].BloqueurParLaDroite1 = 0 ;
 Bloc[15].BloqueurParLaDroite2 = 11;
 Bloc[15].BloqueurParLaDroite3 = 21;
 Bloc[15].BloqueurParLaDroite4 = 21;
 Bloc[15].BloqueurParLaGauche1 = 0 ;
 Bloc[15].BloqueurParLaGauche2 = 10;
 Bloc[15].BloqueurParLaGauche3 = 21;
 Bloc[15].BloqueurParLaGauche4 = 21;
 Bloc[15].Largeur1 = 0;
 Bloc[15].Largeur2 = 1;
 Bloc[15].Largeur3 = 1;
 Bloc[15].Largeur4 = 1;
 Bloc[15].BlocDuBloc1 = 0 ;
 Bloc[15].BlocDuBloc2 = 10;
 Bloc[15].BlocDuBloc3 = 11;
 Bloc[15].BlocDuBloc4 = 21;

 Bloc[16].BloqueurParLeBas1    = 11;
 Bloc[16].BloqueurParLeBas2    = 20;
 Bloc[16].BloqueurParLeBas3    = 20;
 Bloc[16].BloqueurParLeBas4    = 20;
 Bloc[16].BloqueurParLaDroite1 = 1 ;
 Bloc[16].BloqueurParLaDroite2 = 11;
 Bloc[16].BloqueurParLaDroite3 = 20;
 Bloc[16].BloqueurParLaDroite4 = 20;
 Bloc[16].BloqueurParLaGauche1 = 2 ;
 Bloc[16].BloqueurParLaGauche2 = 10;
 Bloc[16].BloqueurParLaGauche3 = 20;
 Bloc[16].BloqueurParLaGauche4 = 20;
 Bloc[16].Largeur1 = 0;
 Bloc[16].Largeur2 = 1;
 Bloc[16].Largeur3 = 1;
 Bloc[16].Largeur4 = 1;
 Bloc[16].BlocDuBloc1 = 1 ;
 Bloc[16].BlocDuBloc2 = 10;
 Bloc[16].BlocDuBloc3 = 11;
 Bloc[16].BlocDuBloc4 = 20;

 Bloc[17].BloqueurParLeBas1    = 10;
 Bloc[17].BloqueurParLeBas2    = 11;
 Bloc[17].BloqueurParLeBas3    = 12;
 Bloc[17].BloqueurParLeBas4    = 12;
 Bloc[17].BloqueurParLaDroite1 = 2 ;
 Bloc[17].BloqueurParLaDroite2 = 12;
 Bloc[17].BloqueurParLaDroite3 = 12;
 Bloc[17].BloqueurParLaDroite4 = 12;
 Bloc[17].BloqueurParLaGauche1 = 2 ;
 Bloc[17].BloqueurParLaGauche2 = 10;
 Bloc[17].BloqueurParLaGauche3 = 10;
 Bloc[17].BloqueurParLaGauche4 = 10;
 Bloc[17].Largeur1 = 0;
 Bloc[17].Largeur2 = 1;
 Bloc[17].Largeur3 = 2;
 Bloc[17].Largeur4 = 2;
 Bloc[17].BlocDuBloc1 = 2 ;
 Bloc[17].BlocDuBloc2 = 10;
 Bloc[17].BlocDuBloc3 = 11;
 Bloc[17].BlocDuBloc4 = 12;

 Bloc[18].BloqueurParLeBas1    = 20;
 Bloc[18].BloqueurParLeBas2    = 21;
 Bloc[18].BloqueurParLeBas3    = 21;
 Bloc[18].BloqueurParLeBas4    = 21;
 Bloc[18].BloqueurParLaDroite1 = 0 ;
 Bloc[18].BloqueurParLaDroite2 = 10;
 Bloc[18].BloqueurParLaDroite3 = 21;
 Bloc[18].BloqueurParLaDroite4 = 21;
 Bloc[18].BloqueurParLaGauche1 = 0 ;
 Bloc[18].BloqueurParLaGauche2 = 10;
 Bloc[18].BloqueurParLaGauche3 = 20;
 Bloc[18].BloqueurParLaGauche4 = 20;
 Bloc[18].Largeur1 = 0;
 Bloc[18].Largeur2 = 1;
 Bloc[18].Largeur3 = 1;
 Bloc[18].Largeur4 = 1;
 Bloc[18].BlocDuBloc1 = 0 ;
 Bloc[18].BlocDuBloc2 = 10;
 Bloc[18].BlocDuBloc3 = 20;
 Bloc[18].BlocDuBloc4 = 21;

 Bloc[19].BloqueurParLeBas1    = 1 ;
 Bloc[19].BloqueurParLeBas2    = 2 ;
 Bloc[19].BloqueurParLeBas3    = 10;
 Bloc[19].BloqueurParLeBas4    = 10;
 Bloc[19].BloqueurParLaDroite1 = 2 ;
 Bloc[19].BloqueurParLaDroite2 = 10;
 Bloc[19].BloqueurParLaDroite3 = 10 ;
 Bloc[19].BloqueurParLaDroite4 = 10 ;
 Bloc[19].BloqueurParLaGauche1 = 0 ;
 Bloc[19].BloqueurParLaGauche2 = 10;
 Bloc[19].BloqueurParLaGauche3 = 10;
 Bloc[19].BloqueurParLaGauche4 = 10;
 Bloc[19].Largeur1 = 0;
 Bloc[19].Largeur2 = 1;
 Bloc[19].Largeur3 = 2;
 Bloc[19].Largeur4 = 2;
 Bloc[19].BlocDuBloc1 = 0;
 Bloc[19].BlocDuBloc2 = 1;
 Bloc[19].BlocDuBloc3 = 2;
 Bloc[19].BlocDuBloc4 = 10;

 Bloc[20].BloqueurParLeBas1    = 0 ;
 Bloc[20].BloqueurParLeBas2    = 1 ;
 Bloc[20].BloqueurParLeBas3    = 12;
 Bloc[20].BloqueurParLeBas4    = 12;
 Bloc[20].BloqueurParLaDroite1 = 2 ;
 Bloc[20].BloqueurParLaDroite2 = 12;
 Bloc[20].BloqueurParLaDroite3 = 12;
 Bloc[20].BloqueurParLaDroite4 = 12;
 Bloc[20].BloqueurParLaGauche1 = 0 ;
 Bloc[20].BloqueurParLaGauche2 = 12;
 Bloc[20].BloqueurParLaGauche3 = 12;
 Bloc[20].BloqueurParLaGauche4 = 12;
 Bloc[20].Largeur1 = 0;
 Bloc[20].Largeur2 = 1;
 Bloc[20].Largeur3 = 2;
 Bloc[20].Largeur4 = 2;
 Bloc[20].BlocDuBloc1 = 0;
 Bloc[20].BlocDuBloc2 = 1;
 Bloc[20].BlocDuBloc3 = 2;
 Bloc[20].BlocDuBloc4 = 12;

 Bloc[21].BloqueurParLeBas1    = 20;
 Bloc[21].BloqueurParLeBas2    = 21;
 Bloc[21].BloqueurParLeBas3    = 21;
 Bloc[21].BloqueurParLeBas4    = 21;
 Bloc[21].BloqueurParLaDroite1 = 1 ;
 Bloc[21].BloqueurParLaDroite2 = 11;
 Bloc[21].BloqueurParLaDroite3 = 21;
 Bloc[21].BloqueurParLaDroite4 = 21;
 Bloc[21].BloqueurParLaGauche1 = 1 ;
 Bloc[21].BloqueurParLaGauche2 = 11;
 Bloc[21].BloqueurParLaGauche3 = 20 ;
 Bloc[21].BloqueurParLaGauche4 = 20;
 Bloc[21].Largeur1 = 0;
 Bloc[21].Largeur2 = 1;
 Bloc[21].Largeur3 = 1;
 Bloc[21].Largeur4 = 1;
 Bloc[21].BlocDuBloc1 = 1 ;
 Bloc[21].BlocDuBloc2 = 11;
 Bloc[21].BlocDuBloc3 = 20;
 Bloc[21].BlocDuBloc4 = 21;

 Bloc[22].BloqueurParLeBas1    = 10;
 Bloc[22].BloqueurParLeBas2    = 11;
 Bloc[22].BloqueurParLeBas3    = 12;
 Bloc[22].BloqueurParLeBas4    = 12;
 Bloc[22].BloqueurParLaDroite1 = 0 ;
 Bloc[22].BloqueurParLaDroite2 = 12;
 Bloc[22].BloqueurParLaDroite3 = 12;
 Bloc[22].BloqueurParLaDroite4 = 12;
 Bloc[22].BloqueurParLaGauche1 = 0 ;
 Bloc[22].BloqueurParLaGauche2 = 10;
 Bloc[22].BloqueurParLaGauche3 = 10;
 Bloc[22].BloqueurParLaGauche4 = 10;
 Bloc[22].Largeur1 = 0;
 Bloc[22].Largeur2 = 1;
 Bloc[22].Largeur3 = 2;
 Bloc[22].Largeur4 = 2;
 Bloc[22].BlocDuBloc1 = 0 ;
 Bloc[22].BlocDuBloc2 = 10;
 Bloc[22].BlocDuBloc3 = 11;
 Bloc[22].BlocDuBloc4 = 12;}
