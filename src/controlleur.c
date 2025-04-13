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
int isRouteOccupeeRec(grille* g,int x,int y,positions pos,posValid** visites) {
    if(isVisited(x,y,*visites)) return 0;
    *visites = empilerPosValid(*visites,x,y);
    tuile* t = g->tabTuiles[x][y];
    if(!t) return 0;
    if(t->meeples && t->meeples->tuilePosition == pos) return 1;
    if(pos == NORD && t->nord == ROUTE){
        if(isRouteOccupeeRec(g,x-1,y,SUD,visites)) return 1;
    }
    if(pos == SUD && t->sud == ROUTE){
        if(isRouteOccupeeRec(g,x+1,y,NORD,visites)) return 1;
    }
    if(pos == EST && t->est == ROUTE){
        if(isRouteOccupeeRec(g,x,y+1,OUEST,visites)) return 1;
    }
    if(pos == OUEST && t->ouest == ROUTE){
        if(isRouteOccupeeRec(g,x,y-1,EST,visites)) return 1;
    }
    if(pos == CENTRE && t->centre == ROUTE){
        if(t->meeples && t->meeples->tuilePosition == CENTRE) return 1;
        if(t->nord == ROUTE && isRouteOccupeeRec(g,x-1,y,SUD,visites)) return 1;
        if(t->sud == ROUTE && isRouteOccupeeRec(g,x+1,y,NORD,visites)) return 1;
        if(t->est == ROUTE && isRouteOccupeeRec(g,x,y+1,OUEST,visites)) return 1;
        if(t->ouest == ROUTE && isRouteOccupeeRec(g,x,y-1,EST,visites)) return 1;
    }
    return 0;
}
//---------------------------
int isVilleOccupeeRec(grille* g,int x,int y,positions pos,posValid** visites) {
    if(isVisited(x,y,*visites)) return 0;
    *visites = empilerPosValid(*visites,x,y);
    tuile* t = g->tabTuiles[x][y];
    if(!t) return 0;
    if(t->meeples && t->meeples->tuilePosition == pos) return 1;
    if(pos == NORD && comparerTuiles(VILLE,t->nord) == 1){
        if(isVilleOccupeeRec(g,x-1,y,SUD,visites)) return 1;
    }
    if(pos == SUD && comparerTuiles(VILLE,t->sud) == 1){
        if(isVilleOccupeeRec(g,x+1,y,NORD,visites)) return 1;
    }
    if(pos == EST && comparerTuiles(VILLE,t->est) == 1){
        if(isVilleOccupeeRec(g,x,y+1,OUEST,visites)) return 1;
    }
    if(pos == OUEST && comparerTuiles(VILLE,t->ouest) == 1){
        if(isVilleOccupeeRec(g,x,y-1,EST,visites)) return 1;
    }
    if(pos == CENTRE && comparerTuiles(VILLE,t->centre) == 1){
        if(t->meeples && t->meeples->tuilePosition == CENTRE) return 1;
        if(comparerTuiles(VILLE,t->nord) == 1 && isVilleOccupeeRec(g,x-1,y,SUD,visites)) return 1;
        if(comparerTuiles(VILLE,t->sud) == 1 && isVilleOccupeeRec(g,x+1,y,NORD,visites)) return 1;
        if(comparerTuiles(VILLE,t->est) == 1 && isVilleOccupeeRec(g,x,y+1,OUEST,visites)) return 1;
        if(comparerTuiles(VILLE,t->ouest) == 1 && isVilleOccupeeRec(g,x,y-1,EST,visites)) return 1;
    }
    return 0;
}
//---------------------------
int meepleController(grille* g,int x,int y,positions direction){
    tuile *t = g->tabTuiles[x][y];
    posValid* tete = NULL;
    int valid = 1;
    switch(direction){
    case NORD:
        if(t->nord == ABBAYE){valid = 0;}
        else if(t->nord == ROUTE){valid = isRouteOccupeeRec(g,x,y,direction,&tete);}
        else if(t->nord == VILLE || t->nord == BLASON){valid = isVilleOccupeeRec(g,x,y,direction,&tete);}
        break;
    case SUD:
        if(t->sud == ABBAYE){valid = 0;}
        else if(t->sud == ROUTE){valid = isRouteOccupeeRec(g,x,y,direction,&tete);}
        else if(t->sud == VILLE ||t->sud == BLASON){valid = isVilleOccupeeRec(g,x,y,direction,&tete);}
        break;
    case EST:
        if(t->est == ABBAYE){valid = 0;}
        else if(t->est == ROUTE){valid = isRouteOccupeeRec(g,x,y,direction,&tete);}
        else if(t->est == VILLE ||t->est == BLASON){valid = isVilleOccupeeRec(g,x,y,direction,&tete);}
        break;
    case OUEST:
        if(t->ouest == ABBAYE){valid = 0;}
        else if(t->ouest == ROUTE){valid = isRouteOccupeeRec(g,x,y,direction,&tete);}
        else if(t->ouest == VILLE ||t->ouest == BLASON){valid = isVilleOccupeeRec(g,x,y,direction,&tete);}
        break;
    case CENTRE:
        if(t->centre == ABBAYE){valid = 0;}
        else if(t->centre == ROUTE){valid = isRouteOccupeeRec(g,x,y,direction,&tete);}
        else if(t->centre == VILLE ||t->centre == BLASON){valid = isVilleOccupeeRec(g,x,y,direction,&tete);}
        break;
    default:
        break;
    }
    if(valid == 1) return 0;
    return 1;
}