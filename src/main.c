#include <stdio.h>
#include <stdlib.h>
#include "../include/jeu.h"

int main(){
    grille g;
    tabJoueurs j;
    pileTuiles p;
    int n = initialiserJeu(&g, &j,"data/tuiles.csv",&p);
    deroulementJeu(&g,&j,&p,n);
    return 0;
}