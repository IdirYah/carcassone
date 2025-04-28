#ifndef _JEU_H
#define _JEU_H
#include "joueur.h"
#include "tuile.h"
#include "meeple.h"
//-------------------
int initialiserJeu(grille*,tabJoueurs*,char*,pileTuiles*);
void deroulementJeu(grille*,tabJoueurs*,pileTuiles*,int);
//-------------------
#endif 