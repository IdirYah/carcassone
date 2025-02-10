#ifndef _MEEPLE_H
#define _MEEPLE_H
//---------------------
struct joueur;
typedef struct joueur joueur;
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
    int x,y;
}meeple;
//----------------------
typedef struct listMeeples{
    meeple *m;
    struct listMeeples *suivant;
}listMeeples;
//-----------------------
meeple* creerMeeple(couleurs);
void empilerMeeple(meeple*,joueur*);
//-----------------------
#endif 