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
void libererTuile(tuile *t){
    free(t);
}
//------------------------------------
/*void initialiserPile(char *fname,pileTuiles *p){
    p->indiceCourant = 0;
    FILE *f = fopen(fname,"r");
    if(f == NULL){
        perror("Error\n");
        return;
    }
    char chaine1[10],chaine2[10],chaine3[10],chaine4[10],chaine5[10];
    while(fscanf(f,"%99[^,]%99[^,]%99[^,]%99[^,]%99[^\n]",chaine1,chaine2,chaine3,chaine4,chaine5) == 5){
        printf("%s,%s,%s,%s,%s\n",chaine1,chaine2,chaine3,chaine4,chaine5);
    }
    fclose(f);
}*/
//------------------------------------
tuile* depilerTuile(pileTuiles *t){
    tuile *tmp = t->pile[t->indiceCourant];
    t->indiceCourant++;
    return tmp;
}
//------------------------------------
int pileVide(pileTuiles t){
    return t.indiceCourant == NB_TUILES;
}
//------------------------------------
tuile *rotationTuile(tuile *t,int angle){
    tuile *tmp = (tuile*)malloc(sizeof(tuile));
    tmp->x = t->x;
    tmp->y = t->y;
    tmp->centre = t->centre;
    tmp->meeples = t->meeples;
    if(angle == 90){
        tmp->nord = t->est;
        tmp->ouest = t->nord;
        tmp->sud = t->ouest;
        tmp->est = t->sud;
        return tmp;
    }
    if(angle == 180){
        tmp->nord = t->sud;
        tmp->sud = t->nord;
        tmp->est = t->ouest;
        tmp->ouest = t->est;
        return tmp;
    }
    if(angle == 270){
        tmp->nord = t->ouest;
        tmp->sud = t->est;
        tmp->est = t->sud;
        tmp->ouest = t->nord;
        return tmp;
    }
}
//------------------------------
void poserTuile(grille *g,int ligne,int colonne,tuile *t){
    g->tabTuiles[ligne][colonne] = t;
}