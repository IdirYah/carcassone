#ifndef _MEEPLE_H
#define _MEEPLE_H
#include "tuile.h"
#include "joueur.h"
//----------------------
typedef enum positions{
    NORD,
    SUD,
    EST,
    OUEST,
    CENTRE
}positions;
//----------------------
typedef struct meeple{
    positions tuilePosition;
    tuile *tuiles;
    joueur *player;
}meeple;
//----------------------
#endif 