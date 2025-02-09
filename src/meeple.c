#include "../include/meeple.h"
#include "../include/joueur.h"
#include <stdlib.h>
#include <stdio.h>
//--------------------------
meeple *creerMeeple(couleurs c){
    meeple *m = (meeple*)malloc(sizeof(meeple));
    m->couleur = c;
    m->tuilePosition = RIEN;
    return m;
}
//-------------------------
void empilerMeeple(meeple *mp,joueur *p){
    listMeeples *tmp = (listMeeples*)malloc(sizeof(listMeeples));
    tmp->m = mp;
    tmp->suivant = NULL;
    if(p->teteListe == NULL){
        p->teteListe = tmp;
        return;
    }
    tmp->suivant = p->teteListe;
    p->teteListe = tmp;
}
//-------------------------
meeple* depilerMeeple(joueur* p){
    if(p->teteListe == NULL){
        printf("Pile vide.\n");
        return NULL;
    }
    listMeeples *tmp = p->teteListe;
    meeple *l = tmp->m;
    free(tmp);
    p->teteListe = p->teteListe->suivant;
    return l;
}
//-------------------------