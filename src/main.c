#include <stdio.h>
#include <stdlib.h>
#include "../include/controlleur.h"
#include "../include/tuile.h"
#include "../include/meeple.h"

int main(){
    grille g;
    g.tabTuiles[72][71] = creerTuile(VILLAGE,VILLAGE,ROUTE,ROUTE,ROUTE);
    g.tabTuiles[72][72] = creerTuile(VILLAGE,ROUTE,ROUTE,ROUTE,ROUTE);
    g.tabTuiles[72][73] = creerTuile(VILLAGE,VILLAGE,VILLAGE,ROUTE,ROUTE);
    g.tabTuiles[73][72] = creerTuile(ROUTE,ROUTE,VILLAGE,VILLAGE,VILLAGE);
    g.tabTuiles[73][73] = creerTuile(ROUTE,VILLAGE,ROUTE,VILLAGE,ROUTE);
    posValid* tete = NULL;
    meeple *m = creerMeeple(BLEU);
    m->tuilePosition = SUD;
    m->x = 73;
    m->y = 72;
    g.tabTuiles[73][72]->meeples = m;
    int i = meepleRouteController(&g,72,72,tete, CENTRE);
    printf("%d\n",i);
    return 0;
}