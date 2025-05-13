#ifndef _TUILE_H
#define _TUILE_H
#define MAX 148
#define NB_TUILES 72
#include "meeple.h"
//----------------------------
typedef enum tuileTypes{
    ROUTE,
    VILLE,
    ABBAYE,
    PRE,
    BLASON,
    VILLAGE
}tuileTypes;
//----------------------------
typedef struct tuile{
    tuileTypes nord;
    tuileTypes sud;
    tuileTypes est;
    tuileTypes ouest;
    tuileTypes centre;
    meeple *meeples;
}tuile;
//----------------------------
typedef struct pileTuiles{
    tuile* pile[NB_TUILES];
    int indiceCourant;
}pileTuiles;
//----------------------------
typedef struct grille{
    tuile* tabTuiles[MAX][MAX];
    int ligneDebut,colonneDebut;
}grille;
//----------------------------
tuile* creerTuile(tuileTypes,tuileTypes,tuileTypes,tuileTypes,tuileTypes);
void libererTuile(tuile *);
tuileTypes convertirChaine(char*);
void initialiserPile(char*,pileTuiles*);
tuile *depilerTuile(pileTuiles*);
int pileVide(pileTuiles);
tuile* rotationTuile(tuile*,int);
void poserTuile(grille*,int,int,tuile*);
void melangerTuile(pileTuiles*);
//-----------------------------
#endif 
