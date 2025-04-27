#ifndef _AFFICHAGE_H
#define _AFFICHAGE_H
#include "../include/tuile.h"
#include "../include/affichage.h"
#include "../include/joueur.h"
//--------------------
int colorToInt(couleurs);
char tuilePosToChar(tuileTypes);
void symbolDesignation();
void afficherTuile(tuile*);
void afficherScore(tabJoueurs*);
//--------------------
#endif 