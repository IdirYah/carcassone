#ifndef _CONTROLLEUR_H
#define _CONTROLLEUR_H
#include "../include/tuile.h"
//---------------------
typedef struct posValid{
    int ligne,colonne;
    struct posValid *suivant;
}posValid;
//---------------------
int isPositionTuileValide(grille*,tuile*,int,int);
posValid* empilerPosValid(posValid*,int,int);
void libererPosValid(posValid*);
posValid* positionsValid(grille*);
//---------------------
#endif 
