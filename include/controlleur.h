#ifndef _CONTROLLEUR_H
#define _CONTROLLEUR_H
#include "../include/tuile.h"
#include "../include/meeple.h"
//---------------------
typedef struct posValid{
    int ligne,colonne;
    struct posValid *suivant;
}posValid;
//---------------------
int comparerTuiles(tuileTypes,tuileTypes);
int isPositionTuileValide(grille*,tuile*,int,int);
posValid* empilerPosValid(posValid*,int,int);
posValid* depilerPosValid(posValid*);
void libererPosValid(posValid*);
posValid* positionsValid(grille*,tuile*);
int isPositionMeepleValid(grille*,meeple*);
int isVisited(int,int,posValid*);
int isRouteOccupeeRec(grille*,int,int,positions,posValid**);
int isVilleOccupeeRec(grille*,int,int,positions,posValid**);
int meepleController(grille*,int,int,positions);
//---------------------
#endif 