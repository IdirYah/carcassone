
#include "../include/controlleur.h"
#include "../include/tuile.h"
#include "../include/meeple.h"
#include <stdlib.h>
//-------------------------
int comparerTuiles(tuileTypes p1,tuileTypes p2){
    if(p1 != VILLE && p1 != BLASON){
        return p1 == p2;
    }
    return p2 == VILLE || p2 == BLASON;
}
//-------------------------
int isPositionTuileValide(grille* g, tuile *t, int dx, int dy) {
    if (g->tabTuiles[dx][dy] != NULL) {
        return 0;
    }
    int aVoisin = 0;
    if (g->tabTuiles[dx-1][dy] != NULL) { 
        aVoisin = 1;
        if(!comparerTuiles(t->nord, g->tabTuiles[dx-1][dy]->sud)){
            return 0;
        }
    }
    if(g->tabTuiles[dx+1][dy] != NULL) { 
        aVoisin = 1;
        if (!comparerTuiles(t->sud, g->tabTuiles[dx+1][dy]->nord)){
            return 0;
        }
    }
    if(g->tabTuiles[dx][dy-1] != NULL) { 
        aVoisin = 1;
        if(!comparerTuiles(t->ouest, g->tabTuiles[dx][dy-1]->est)){
            return 0;
        }
    }
    if(g->tabTuiles[dx][dy+1] != NULL) { 
        aVoisin = 1;
        if(!comparerTuiles(t->est, g->tabTuiles[dx][dy+1]->ouest)){
            return 0;
        }
    }
    return aVoisin;
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
//---------------------------
int isVisited(int x,int y,posValid* tete){
    posValid* p = tete;
    while(p != NULL){
        if(p->colonne == y && p->ligne == x){
            return 1;
        }
        p = p->suivant;
    }
    return 0;
}
//---------------------------
int isMeepleInRoute(meeple* m, tuile* t)
{
    switch(m->tuilePosition){
        case NORD: 
            return t->nord != ROUTE;
        case SUD:
            return t->sud != ROUTE;
        case EST:
            return t->est != ROUTE;
        case OUEST:
            return t->ouest != ROUTE;
        case CENTRE:
            return t->centre != ROUTE;
    }
}
//---------------------------
//Controller si on peut poser un meeple sur une route (parcours de route)
int meepleRouteController(grille* g,int x,int y,posValid* tete){
    if(isVisited(x,y,tete)){
        return 1;
    }
    tuile *t = g->tabTuiles[x][y];
    if (t == NULL){
        return 1;  
    }
    if(t->meeples != NULL){
        return 0;
    }
    tete = empilerPosValid(tete, x, y);
    if (t->centre == ROUTE) {
        if (t->nord == ROUTE && meepleRouteController(g, x - 1, y, tete) == 0) {
            return 0;
        }
        if (t->sud == ROUTE && meepleRouteController(g, x + 1, y, tete) == 0) {
            return 0;
        }
        if (t->est == ROUTE && meepleRouteController(g, x, y + 1, tete) == 0) {
            return 0;
        }
        if (t->ouest == ROUTE && meepleRouteController(g, x, y - 1, tete) == 0) {
            return 0;
        }
    }else{
        if (t->nord == ROUTE) {
            tuile *tNord = g->tabTuiles[x - 1][y];
            if (tNord != NULL && tNord->sud == ROUTE && meepleRouteController(g, x - 1, y, tete) == 0) {
                return 0;
            }
        }
        if (t->sud == ROUTE) {
            tuile *tSud = g->tabTuiles[x + 1][y];
            if (tSud != NULL && tSud->nord == ROUTE && meepleRouteController(g, x + 1, y, tete) == 0) {
                return 0;
            }
        }
        if (t->est == ROUTE) {
            tuile *tEst = g->tabTuiles[x][y + 1];
            if (tEst != NULL && tEst->ouest == ROUTE && meepleRouteController(g, x, y + 1, tete) == 0) {
                return 0;
            }
        }
        if (t->ouest == ROUTE) {
            tuile *tOuest = g->tabTuiles[x][y - 1];
            if (tOuest != NULL && tOuest->est == ROUTE && meepleRouteController(g, x, y - 1, tete) == 0) {
                return 0;
            }
        }
    }
    return 1;  
}
