#ifndef _JOUEUR_H
#define _JOUEUR_H
#include "meeple.h"
//------------------------
typedef struct joueur{
    unsigned int id;
    unsigned int score;
    listMeeples *teteListe;
}joueur;
//-------------------------
typedef struct tabJoueurs{
    joueur **player;
    unsigned int nbJoueurs;
}tabJoueurs;
//-------------------------
joueur *creerJoueur(int);
void creerJoueurs(tabJoueurs*,int);
//-------------------------
#endif 