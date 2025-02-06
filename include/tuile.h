#ifndef _TUILE_H
#define _TUILE_H
#define MAX 144
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
    int x,y;
    meeple *meeples;
}tuile;
//----------------------------
typedef struct pileTuiles{
    tuile pile[NB_TUILES];
    int indiceCourant;
}pileTuiles;
//----------------------------
typedef struct grille{
    tuile tabTuiles[MAX][MAX];
    int ligneDebut,colonneDebut;
}grille;
//----------------------------
#endif 
