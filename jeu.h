#ifndef PROTOTYPE
#define PROTOTYPE

#define LONGUEURE 600
#define CARRE     30
#define MARGE     150

void Tetrix(SDL_Surface);
int Rotation( int );
void CaracteristiqueDesBloc();

typedef struct Caracteristiques Caracteristiques;
struct Caracteristiques
{int BloqueurParLeBas1;
 int BloqueurParLeBas2;
 int BloqueurParLeBas3;
 int BloqueurParLeBas4;
 int BloqueurParLaDroite1;
 int BloqueurParLaDroite2;
 int BloqueurParLaDroite3;
 int BloqueurParLaDroite4;
 int BloqueurParLaGauche1;
 int BloqueurParLaGauche2;
 int BloqueurParLaGauche3;
 int BloqueurParLaGauche4;
 int Largeur1;
 int Largeur2;
 int Largeur3;
 int Largeur4;
 int BlocDuBloc1;
 int BlocDuBloc2;
 int BlocDuBloc3;
 int BlocDuBloc4;
};

#endif
