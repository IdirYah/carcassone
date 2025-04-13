#include <stdio.h>
#include <stdlib.h>
#include "../include/controlleur.h"
#include "../include/tuile.h"
#include "../include/meeple.h"

int main(){
    grille g;
    g.tabTuiles[72][71] = creerTuile(VILLAGE,VILLAGE,VILLE,VILLE,BLASON);
    g.tabTuiles[72][72] = creerTuile(VILLAGE,BLASON,VILLE,VILLE,BLASON);
    g.tabTuiles[72][73] = creerTuile(VILLAGE,VILLAGE,VILLAGE,BLASON,VILLE);
    g.tabTuiles[73][72] = creerTuile(VILLE,VILLE,VILLAGE,VILLAGE,VILLAGE);
    g.tabTuiles[73][73] = creerTuile(BLASON,VILLAGE,VILLE,VILLAGE,BLASON);
    meeple *m = creerMeeple(BLEU);
    m->tuilePosition = NORD;
    m->x = 73;
    m->y = 72;
    g.tabTuiles[m->x][m->y]->meeples = m;
    int i = meepleController(&g,72,72,CENTRE);
    printf("%d\n",i);
    return 0;
}