#include <stdio.h>
#include <stdlib.h>
#include "../include/affichage.h"

int main(){
    grille g;
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++){
            g.tabTuiles[i][j] = NULL;
        }
    }
    g.tabTuiles[72][71] = creerTuile(VILLAGE,VILLAGE,ROUTE,ROUTE,ROUTE);
    g.tabTuiles[72][72] = creerTuile(VILLAGE,ROUTE,VILLAGE,ROUTE,ROUTE);
    g.tabTuiles[72][73] = creerTuile(VILLAGE,VILLAGE,VILLAGE,ROUTE,ROUTE);
    g.tabTuiles[73][72] = creerTuile(ROUTE,VILLAGE,VILLAGE,VILLAGE,ROUTE);
    g.tabTuiles[73][73] = creerTuile(VILLAGE,VILLAGE,VILLAGE,VILLAGE,VILLAGE);
    afficherGrille(&g);
    return 0;
}