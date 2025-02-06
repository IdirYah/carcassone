#ifndef _MEEPLE_H
#define _MEEPLE_H
#include "tuile.h"
//----------------------
typedef enum couleurs{
    JAUNE,
    ROUGE,
    VERT,
    BLEU,
    NOIR
}couleurs;
//--------------------------
typedef enum positions{
    RIEN,
    NORD,
    SUD,
    EST,
    OUEST,
    CENTRE
}positions;
//----------------------
typedef struct meeple{
    positions tuilePosition;
    couleurs couleur; 
}meeple;
//----------------------
typedef struct listMeeples{
    meeple *m;
    struct listMeeples *suivant;
}listMeeples;
//-----------------------
#endif 