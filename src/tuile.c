#include "../include/tuile.h"
#include <stdlib.h>
#include <stdio.h>
//---------------------------------
tuile *creerTuile(tuileTypes north,tuileTypes south,tuileTypes east,tuileTypes west,tuileTypes center){
    tuile *t = (tuile*)malloc(sizeof(tuile));
    t->centre = center;
    t->est = east;
    t->ouest = west;
    t->nord = north;
    t->sud = south;
    t->x = -1;
    t->y = -1;
    t->meeples = NULL;
    return t;
}
//------------------------------------
void initialiserPile(char *fname,pileTuiles *p){
    p->indiceCourant = 0;
    FILE *f = fopen(fname,"rb");
    fclose(f);
}