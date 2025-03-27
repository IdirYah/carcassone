#include <stdio.h>
#include <stdlib.h>
#include "../include/tuile.h"
#include "../include/meeple.h"
#include "../include/controlleur.h"

int main(){
    tuile* t = creerTuile(ROUTE, VILLE, ABBAYE, BLASON, VILLAGE);
    meeple* m = creerMeeple(BLEU);
    m->tuilePosition = SUD;
    t->meeples = m;
    printf("%d \n", isMeepleInRoute(m, t));
    
    return 0;
}