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
posValid* depilerPosValid(posValid* tete){
    if (tete == NULL){
        return NULL;
    }
    posValid *nouveauSommet = tete->suivant;
    free(tete);
    return nouveauSommet;
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
int isMeepleInRoute(meeple* m, tuile* t){
    if(m->tuilePosition == NORD) return t->nord != ROUTE;
    if(m->tuilePosition == SUD) return t->sud != ROUTE;
    if(m->tuilePosition == EST) return t->est != ROUTE;
    if(m->tuilePosition == OUEST) return t->ouest != ROUTE;
    return t->centre != ROUTE; 
}
//---------------------------
int isMeepleInVille(meeple* m, tuile* t){
    if(m->tuilePosition == NORD) return !comparerTuiles(t->nord,VILLE);
    if(m->tuilePosition == SUD) return !comparerTuiles(t->sud,VILLE);
    if(m->tuilePosition == EST) return !comparerTuiles(t->est,VILLE);
    if(m->tuilePosition == OUEST) return !comparerTuiles(t->ouest,VILLE);
    return !comparerTuiles(t->centre,VILLE); 
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
int meepleRouteController(grille* g,int x,int y,posValid* tete,positions direction){
    
}
//--------------------------
int meepleVilleController(grille* g,int x,int y,posValid* tete,positions direction){
    if(isVisited(x,y,tete)){
        return 1;
    }
    tuile *t = g->tabTuiles[x][y];
    if(t == NULL){
        return 1;  
    }
    if(t->meeples != NULL && isMeepleInVille(t->meeples,t) == 0){
        return 0;
    }
    tete = empilerPosValid(tete,x,y);
    if (direction != SUD && t->nord == ROUTE && meepleVilleController(g, x - 1, y, tete, NORD) == 0) {
        return 0;
    }
    if (direction != NORD && t->sud == ROUTE && meepleVilleController(g, x + 1, y, tete, SUD) == 0) {
        return 0;
    }
    if (direction != OUEST && t->est == ROUTE && meepleVilleController(g, x, y + 1, tete, EST) == 0) {
        return 0;
    }
    if (direction != EST && t->ouest == ROUTE && meepleVilleController(g, x, y - 1, tete, OUEST) == 0) {
        return 0;
    }
    return 1;  
}
//---------------------
int meepleController(grille* g,int x,int y,positions direction){
    tuile *t = g->tabTuiles[x][y];
    posValid* tete = NULL;
    int valid = 0;
    switch(direction){
    case NORD:
        if(t->nord == ABBAYE){valid = 1;}
        //else if(t->nord == ROUTE){valid = meepleRouteController(g,x,y,tete,direction);}
        else if(t->nord == VILLE || t->nord == BLASON){valid = meepleVilleController(g,x,y,tete,direction);}
        break;
    case SUD:
        if(t->sud == ABBAYE){valid = 1;}
        //else if(t->sud == ROUTE){valid = meepleRouteController(g,x,y,tete,direction);}
        else if(t->sud == VILLE ||t->sud == BLASON){valid = meepleVilleController(g,x,y,tete,direction);}
        break;
    case EST:
        if(t->est == ABBAYE){valid = 1;}
        //else if(t->est == ROUTE){valid = meepleRouteController(g,x,y,tete,direction);}
        else if(t->est == VILLE ||t->est == BLASON){valid = meepleVilleController(g,x,y,tete,direction);}
        break;
    case OUEST:
        if(t->ouest == ABBAYE){valid = 1;}
        //else if(t->ouest == ROUTE){valid = meepleRouteController(g,x,y,tete,direction);}
        else if(t->ouest == VILLE ||t->ouest == BLASON){valid = meepleVilleController(g,x,y,tete,direction);}
        break;
    case CENTRE:
        if(t->centre == ABBAYE){valid = 1;}
        //else if(t->centre == ROUTE){valid = meepleRouteController(g,x,y,tete,direction);}
        else if(t->centre == VILLE ||t->centre == BLASON){valid = meepleVilleController(g,x,y,tete,direction);}
        break;
    default:
        break;
    }
    return valid;
}