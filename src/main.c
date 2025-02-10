#include <stdio.h>
#include <stdlib.h>
#include "../include/controlleur.h"
#include "../include/tuile.h"
int main(){
    grille g;
    pileTuiles p;
    initialiserPile("C:/carcassonne/lib/tuiles.csv",&p);
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++){
            g.tabTuiles[i][j] = NULL;
        }
    }
    tuile *t = creerTuile(1,1,1,1,1);
    g.tabTuiles[72][72] = t;
    tuile *tmp = depilerTuile(&p);
    printf("ON EST LA \n");
    posValid *tete = NULL;
    tete = positionsValid(&g);
    while(tete != NULL){
        printf("%d %d",tete->ligne,tete->colonne);
        tete = tete->suivant;
    }
    return 0;
}