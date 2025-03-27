#include <stdio.h>
#include <stdlib.h>
#include "../include/affichage.h"
#include "../include/tuile.h"

int main(){
    /*grille g;
    g.tabTuiles[72][71] = creerTuile(VILLAGE,VILLAGE,ROUTE,ROUTE,ROUTE);
    g.tabTuiles[72][72] = creerTuile(VILLAGE,ROUTE,ROUTE,ROUTE,ROUTE);
    g.tabTuiles[72][73] = creerTuile(VILLAGE,VILLAGE,VILLAGE,ROUTE,ROUTE);
    g.tabTuiles[73][72] = creerTuile(ROUTE,ROUTE,VILLAGE,VILLAGE,ROUTE);
    g.tabTuiles[73][73] = creerTuile(ROUTE,VILLAGE,VILLAGE,ROUTE,ROUTE);
    posValid* tete = NULL;
    int i = meepleRouteController(&g,72,72,tete);
    printf("%d\n",i);*/
    tuile *t = creerTuile(VILLAGE,VILLE,ROUTE,ROUTE,PRE);
    afficherTuile(t);
    return 0;
}