#ifndef _TUILE_H
#define _TUILE_H
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
#endif 
