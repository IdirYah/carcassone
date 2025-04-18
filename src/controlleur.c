
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
//--------------------------
int compterRoute(grille* g,int x,int y,positions pos,posValid** visites){
    if(isVisited(x,y,*visites)) return 0;
    tuile* t = g->tabTuiles[x][y];
    if(!t)return 0;
    *visites = empilerPosValid(*visites,x,y);
    int score = 1;
    if(t->nord == ROUTE){
        tuile* voisine = g->tabTuiles[x-1][y];
        if(voisine && voisine->sud == ROUTE) score = score + compterRoute(g,x-1,y,SUD,visites);
    }
    if(t->sud == ROUTE){
        tuile* voisine = g->tabTuiles[x+1][y];
        if(voisine && voisine->nord == ROUTE) score = score + compterRoute(g,x+1,y,NORD,visites);
    }
    if(t->est == ROUTE){
        tuile* voisine = g->tabTuiles[x][y+1];
        if(voisine && voisine->ouest == ROUTE) score = score + compterRoute(g,x,y+1,OUEST,visites);
    }
    if(t->ouest == ROUTE){
        tuile* voisine = g->tabTuiles[x][y-1];
        if(voisine && voisine->est == ROUTE) score = score + compterRoute(g,x,y-1,EST,visites);
    }
    return score;
}
//-----------------------------
int contientBlason(tuile* t){
    return (t->centre == BLASON || t->est == BLASON || t->nord == BLASON || t->ouest == BLASON || t->sud == BLASON);
}
//-----------------------------
int compterVille(grille* g,int x,int y,positions pos,posValid** visites){
    if(isVisited(x,y,*visites)) return 0;
    tuile* t = g->tabTuiles[x][y];
    if(!t)return 0;
    *visites = empilerPosValid(*visites,x,y);
    int score = 1;
    if(contientBlason(t)) score = 2;
    if(comparerTuiles(VILLE,t->nord)){
        tuile* voisine = g->tabTuiles[x-1][y];
        if(voisine && comparerTuiles(VILLE,voisine->sud)) score = score + compterVille(g,x-1,y,SUD,visites);
    }
    if(comparerTuiles(VILLE,t->sud)){
        tuile* voisine = g->tabTuiles[x+1][y];
        if(voisine && comparerTuiles(VILLE,voisine->nord)) score = score + compterVille(g,x+1,y,NORD,visites);
    }
    if(comparerTuiles(VILLE,t->est)){
        tuile* voisine = g->tabTuiles[x][y+1];
        if(voisine && comparerTuiles(VILLE,voisine->ouest)) score = score + compterVille(g,x,y+1,OUEST,visites);
    }
    if(comparerTuiles(VILLE,t->ouest)){
        tuile* voisine = g->tabTuiles[x][y-1];
        if(voisine && comparerTuiles(VILLE,voisine->est)) score = score + compterVille(g,x,y-1,EST,visites);
    }
    return score;
}
//-------------------
int compterAbbaye(grille* g,int x,int y){
    int score = 0;
    if(g->tabTuiles[x][y] == NULL) return score;
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            if(g->tabTuiles[x+i][y+j] != NULL) score++;
        }
    }
    return score;
}