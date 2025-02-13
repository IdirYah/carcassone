#include "../include/controlleur.h"
#include "../include/tuile.h"
#include <stdlib.h>
//-------------------------
int comparerTuiles(tuileTypes p1,tuileTypes p2){
    if(p1 != VILLE && p1 != BLASON){
        return p1 == p2;
    }
    return p2 == VILLE || p2 == BLASON;
}
//-------------------------
int isPositionTuileValide(grille* g,tuile *t,int dx,int dy){
    if(g->tabTuiles[dx][dy] != NULL){
        return 0;
    }
    if(g->tabTuiles[dx-1][dy] == NULL && g->tabTuiles[dx+1][dy] == NULL && g->tabTuiles[dx][dy-1] == NULL && g->tabTuiles[dx][dy+1] == NULL){
        return 0;
    }
    if(g->tabTuiles[dx-1][dy] != NULL && comparerTuiles(t->nord,g->tabTuiles[dx-1][dy]->sud) == 1){
        return 1;
    }
    if(g->tabTuiles[dx+1][dy] != NULL && comparerTuiles(t->sud,g->tabTuiles[dx+1][dy]->nord) == 1){
        return 1;
    }
    if(g->tabTuiles[dx][dy-1] != NULL && comparerTuiles(t->ouest,g->tabTuiles[dx][dy-1]->est) == 1){
        return 1;
    }
    if(g->tabTuiles[dx][dy+1] != NULL && comparerTuiles(t->est,g->tabTuiles[dx][dy+1]->ouest) == 1){
        return 1;
    }
    return 0;
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
posValid* positionsValid(grille *g,tuile* t){
    posValid* tete = NULL;
    for(int i=1;i<MAX-1;i++){
        for(int j=1;j<MAX-1;j++){
            if(isPositionTuileValide(g,t,i,j) == 1){
                tete = empilerPosValid(tete,i,j);
            }
        }
    }
    return tete;
}