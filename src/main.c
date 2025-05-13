#include <stdio.h>
#include <stdlib.h>
#include "../include/tuile.h"
#include "../include/meeple.h"
#include "../include/controlleur.h"
#include "../include/affichage.h"
#include "../include/jeu.h"

int main(){
    grille g;
    tabJoueurs j;
    pileTuiles p;
    int n = initialiserJeu(&g, &j,"data/tuiles.csv",&p);
    deroulementJeu(&g,&j,&p,n);
    finJeu(&g,&j,n);
    return 0;
}