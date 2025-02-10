#include "../include/controlleur.h"
#include "../include/tuile.h"
#include <stdlib.h>
//-------------------------
int isPositionTuileValide(grille* g,tuile *t,int dx,int dy){
    
}
//--------------------------
posValid* empilerPosValid(posValid* tete,int l,int c){
    posValid* tmp = tete;
    posValid *p = (posValid*)malloc(sizeof(posValid));
    p->ligne = l;
    p->colonne = c;
    p->suivant = NULL;
    if(tmp == NULL){
        return p;
    }
    p->suivant = tmp;
    return p;
}
//---------------------------
void libererPosValid(posValid* tete){
    posValid* tmp = tete;
    while(tmp != NULL){
        posValid* t = tmp;
        free(t);
        tmp = tmp->suivant;
    }
}
//--------------------------
posValid* positionsValid(grille *g){
    posValid* tete = NULL;
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++){
            if(isPositionTuileValide(g,g->tabTuiles[i][j],i,j) == 1){
                tete = empilerPosValid(tete,i,j);
            }
        }
    }
    return tete;
}