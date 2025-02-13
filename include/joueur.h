#ifndef _JOUEUR_H
#define _JOUEUR_H
#include "meeple.h"
#include "tuile.h"
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
joueur *creerJoueur(int,couleurs);
void creerJoueurs(tabJoueurs*,int);
void poserMeeple(grille,tabJoueurs*,int,positions,int,int);
//-------------------------
#endif 