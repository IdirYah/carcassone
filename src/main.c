#include <stdio.h>
#include <stdlib.h>
#include "../include/controlleur.h"
#include "../include/tuile.h"
#include "../include/meeple.h"

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
    posValid* tete = NULL;
    meeple *m = creerMeeple(BLEU);
    m->tuilePosition = CENTRE;
    m->x = 72;
    m->y = 72;
    g.tabTuiles[m->x][m->y]->meeples = m;
    int i = calculScore(&g,1,m);
    printf("%d\n",i);
    return 0;
}