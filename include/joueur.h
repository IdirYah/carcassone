#ifndef _JOUEUR_H
#define _JOUEUR_H
//-------------------------
typedef enum couleur{
    JAUNE,
    ROUGE,
    VERT,
    BLEU,
    NOIR
}couleurs;
//------------------------
typedef struct joueur{
    unsigned int score;
    couleurs couleur;
    unsigned int nbMeeples;
}joueur;
//-------------------------
#endif 
