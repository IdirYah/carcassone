#include <stdio.h>
#include <stdlib.h>
#include "../include/joueur.h"
int main(){
    tabJoueurs tab;
    creerJoueurs(&tab,5);
    poserMeeple(&tab,1,CENTRE);
    poserMeeple(&tab,1,NORD);
    printf("%d\n",tab.player[1]->teteListe->suivant->m->tuilePosition);
    return 0;
}