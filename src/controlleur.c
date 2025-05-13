#include "../include/controlleur.h"
#include "../include/tuile.h"
#include "../include/meeple.h"
#include <stdlib.h>
#include <stdio.h>
//-------------------------
int comparerTuiles(tuileTypes p1,tuileTypes p2){
    if(p1 != VILLE && p1 != BLASON){
        return p1 == p2;
    }
    return p2 == VILLE || p2 == BLASON;
}
//-------------------------
int isPositionTuileValide(grille* g, tuile *t, int dx, int dy){
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
    if(p == NULL){
        printf("Erreur d'allocation de memoire.\n");
        return NULL;
    }
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
int isRouteOccupeeRec(grille* g,int x,int y,positions pos,posValid** visites){
    if(isVisited(x,y,*visites)) return 1;
    *visites = empilerPosValid(*visites,x,y);
    tuile* t = g->tabTuiles[x][y];
    if(!t) return 1;
    if(t->meeples != NULL && t->meeples->tuilePosition == pos) return 0;
    int found = 1;
    if(comparerTuiles(ROUTE,t->centre)){
        if(t->meeples != NULL && t->meeples->tuilePosition == CENTRE) return 0;
        if(comparerTuiles(ROUTE, t->nord) && t->meeples != NULL && t->meeples->tuilePosition == NORD) return 0;
        tuile* voisine = g->tabTuiles[x-1][y];
        if(voisine && comparerTuiles(ROUTE,voisine->sud)) found &= isRouteOccupeeRec(g,x-1,y,SUD,visites);
        if(comparerTuiles(ROUTE, t->sud) && t->meeples != NULL && t->meeples->tuilePosition == SUD) return 0;
        voisine = g->tabTuiles[x+1][y];
        if(voisine && comparerTuiles(ROUTE,voisine->nord)) found &= isRouteOccupeeRec(g,x+1,y,NORD,visites);
        if(comparerTuiles(ROUTE, t->ouest) && t->meeples != NULL && t->meeples->tuilePosition == OUEST) return 0;
        voisine = g->tabTuiles[x][y-1];
        if(voisine && comparerTuiles(ROUTE,voisine->est)) found &= isRouteOccupeeRec(g,x,y-1,EST,visites);
        if(comparerTuiles(ROUTE, t->est) && t->meeples != NULL && t->meeples->tuilePosition == EST) return 0;
        voisine = g->tabTuiles[x][y+1];
        if(voisine && comparerTuiles(ROUTE,voisine->ouest)) found &= isRouteOccupeeRec(g,x,y+1,OUEST,visites);
    }else{
        if(pos == NORD){
            tuile* voisine = g->tabTuiles[x-1][y];
            if(voisine && comparerTuiles(ROUTE,voisine->sud)) found &= isRouteOccupeeRec(g,x-1,y,SUD,visites);
        }
        else if(pos == SUD){
            tuile* voisine = g->tabTuiles[x+1][y];
            if(voisine && comparerTuiles(ROUTE,voisine->nord)) found &= isRouteOccupeeRec(g,x+1,y,NORD,visites);
        }
        else if(pos == EST){
            tuile* voisine = g->tabTuiles[x][y+1];
            if(voisine && comparerTuiles(ROUTE,voisine->ouest)) found &= isRouteOccupeeRec(g,x,y+1,OUEST,visites);
        }
        else if(pos == OUEST){
            tuile* voisine = g->tabTuiles[x][y-1];
            if(voisine && comparerTuiles(ROUTE,voisine->est)) found &= isRouteOccupeeRec(g,x,y-1,EST,visites);
        }
    }
    return found;
}
//---------------------------
int isVilleOccupeeRec(grille* g,int x,int y,positions pos,posValid** visites){
    if(isVisited(x,y,*visites)) return 1;
    *visites = empilerPosValid(*visites,x,y);
    tuile* t = g->tabTuiles[x][y];
    if(!t) return 1;
    if(t->meeples != NULL && t->meeples->tuilePosition == pos) return 0;
    int found = 1;
    if(comparerTuiles(BLASON,t->centre)){
        if(t->meeples != NULL && t->meeples->tuilePosition == CENTRE) return 0;
        if(comparerTuiles(BLASON,t->nord) && t->meeples != NULL && t->meeples->tuilePosition == NORD) return 0;
        tuile* voisine = g->tabTuiles[x-1][y];
        if(voisine && comparerTuiles(BLASON,voisine->sud)) found &= isVilleOccupeeRec(g,x-1,y,SUD,visites);
        if(comparerTuiles(BLASON,t->sud) && t->meeples != NULL && t->meeples->tuilePosition == SUD) return 0;
        voisine = g->tabTuiles[x+1][y];
        if(voisine && comparerTuiles(BLASON,voisine->nord)) found &= isVilleOccupeeRec(g,x+1,y,NORD,visites);
        if(comparerTuiles(BLASON,t->ouest) && t->meeples != NULL && t->meeples->tuilePosition == OUEST) return 0;
        voisine = g->tabTuiles[x][y-1];
        if(voisine && comparerTuiles(BLASON,voisine->est)) found &= isVilleOccupeeRec(g,x,y-1,EST,visites);
        if(comparerTuiles(BLASON,t->est) && t->meeples != NULL && t->meeples->tuilePosition == EST) return 0;
        voisine = g->tabTuiles[x][y+1];
        if(voisine && comparerTuiles(BLASON,voisine->ouest)) found &= isVilleOccupeeRec(g,x,y+1,OUEST,visites);
    }else{
        if(pos == NORD){
            tuile* voisine = g->tabTuiles[x-1][y];
            if(voisine && comparerTuiles(BLASON,voisine->sud)) found &= isVilleOccupeeRec(g,x-1,y,SUD,visites);
        }
        if(pos == SUD){
            tuile* voisine = g->tabTuiles[x+1][y];
            if(voisine && comparerTuiles(BLASON,voisine->nord)) found &= isVilleOccupeeRec(g,x+1,y,NORD,visites);
        }
        if(pos == EST){
            tuile* voisine = g->tabTuiles[x][y+1];
            if(voisine && comparerTuiles(BLASON,voisine->ouest)) found &= isVilleOccupeeRec(g,x,y+1,OUEST,visites);
        }
        if(pos == OUEST){
            tuile* voisine = g->tabTuiles[x][y-1];
            if(voisine && comparerTuiles(BLASON,voisine->est)) found &= isVilleOccupeeRec(g,x,y-1,EST,visites);
        }
    }
    return found;
}
//---------------------------
int meepleController(grille* g,int x,int y,positions direction){
    tuile *t = g->tabTuiles[x][y];
    posValid* tete = NULL;
    int valid = 0;
    if(direction == NORD){
        if(t->nord == ABBAYE){valid = 1;}
        else if(t->nord == ROUTE){valid = isRouteOccupeeRec(g,x,y,direction,&tete);}
        else if(t->nord == VILLE || t->nord == BLASON){valid = isVilleOccupeeRec(g,x,y,direction,&tete);}
    }else if(direction == SUD){
        if(t->sud == ABBAYE){valid = 1;}
        else if(t->sud == ROUTE){valid = isRouteOccupeeRec(g,x,y,direction,&tete);}
        else if(t->sud == VILLE ||t->sud == BLASON){valid = isVilleOccupeeRec(g,x,y,direction,&tete);}
    }else if(direction == EST){
        if(t->est == ABBAYE){valid = 1;}
        else if(t->est == ROUTE){valid = isRouteOccupeeRec(g,x,y,direction,&tete);}
        else if(t->est == VILLE ||t->est == BLASON){valid = isVilleOccupeeRec(g,x,y,direction,&tete);}
    }else if(direction == OUEST){
        if(t->ouest == ABBAYE){valid = 1;}
        else if(t->ouest == ROUTE){valid = isRouteOccupeeRec(g,x,y,direction,&tete);}
        else if(t->ouest == VILLE ||t->ouest == BLASON){valid = isVilleOccupeeRec(g,x,y,direction,&tete);}
    }else{
        if(t->centre == ABBAYE){valid = 1;}
        else if(t->centre == ROUTE){valid = isRouteOccupeeRec(g,x,y,direction,&tete);}
        else if(t->centre == VILLE ||t->centre == BLASON){valid = isVilleOccupeeRec(g,x,y,direction,&tete);}
    }
    return valid;
}
//-----------------------
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
    if(!t) return 0;
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
//-------------------
int abbayeFinished(grille* g,int x,int y){
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            if(g->tabTuiles[i+x][j+y] == NULL) return 0;
        }
    }
    return 1;
}
//--------------------
int routeFinished(grille* g,int x,int y,positions pos,posValid** visites){
    if(isVisited(x,y,*visites)) return 1;
    *visites = empilerPosValid(*visites,x,y);
    tuile* t = g->tabTuiles[x][y];
    if(!t) return 0;
    int isClosed = 1;
    if(pos == NORD){
        if(comparerTuiles(ROUTE,t->nord) && comparerTuiles(ROUTE,t->centre)){
            if(!comparerTuiles(ROUTE,t->sud) && !comparerTuiles(ROUTE,t->est) && !comparerTuiles(ROUTE,t->ouest)) return 1;
            else{
                if(comparerTuiles(ROUTE,t->est)){
                    tuile* voisine = g->tabTuiles[x][y+1];
                    if(!voisine) return 0;
                    isClosed &= routeFinished(g,x,y+1,OUEST,visites);
                }
                if(comparerTuiles(ROUTE,t->ouest)){
                    tuile* voisine = g->tabTuiles[x][y-1];
                    if(!voisine) return 0;
                    isClosed &= routeFinished(g,x,y-1,EST,visites);
                }
                if(comparerTuiles(ROUTE,t->sud)){
                    tuile* voisine = g->tabTuiles[x+1][y];
                    if(!voisine) return 0;
                    isClosed &= routeFinished(g,x+1,y,NORD,visites);
                }
            }
        }else if(comparerTuiles(ROUTE,t->nord) && !comparerTuiles(ROUTE,t->centre) && g->tabTuiles[x-1][y] != NULL) isClosed &= routeFinished(g,x-1,y,SUD,visites);
        else if(comparerTuiles(ROUTE,t->nord) && !comparerTuiles(ROUTE,t->centre) && g->tabTuiles[x-1][y] == NULL) return 0;
    }
    else if(pos == SUD){
        if(comparerTuiles(ROUTE,t->sud) && comparerTuiles(ROUTE,t->centre)){
            if(!comparerTuiles(ROUTE,t->nord) && !comparerTuiles(ROUTE,t->est) && !comparerTuiles(ROUTE,t->ouest)) return 1;
            else{
                if(comparerTuiles(ROUTE,t->est)){
                    tuile* voisine = g->tabTuiles[x][y+1];
                    if(!voisine) return 0;
                    isClosed &= routeFinished(g,x,y+1,OUEST,visites);
                }
                if(comparerTuiles(ROUTE,t->ouest)){
                    tuile* voisine = g->tabTuiles[x][y-1];
                    if(!voisine) return 0;
                    isClosed &= routeFinished(g,x,y-1,EST,visites);
                }
                if(comparerTuiles(ROUTE,t->nord)){
                    tuile* voisine = g->tabTuiles[x-1][y];
                    if(!voisine) return 0;
                    isClosed &= routeFinished(g,x-1,y,SUD,visites);
                }
            }
        }else if(comparerTuiles(ROUTE,t->sud) && !comparerTuiles(ROUTE,t->centre) && g->tabTuiles[x+1][y] != NULL) isClosed &= routeFinished(g,x+1,y,NORD,visites);
        else if(comparerTuiles(ROUTE,t->sud) && !comparerTuiles(ROUTE,t->centre) && g->tabTuiles[x+1][y] == NULL) return 0;
    }
    else if(pos == EST){
        if(comparerTuiles(ROUTE,t->est) && comparerTuiles(ROUTE,t->centre)){
            if(!comparerTuiles(ROUTE,t->nord) && !comparerTuiles(ROUTE,t->sud) && !comparerTuiles(ROUTE,t->ouest)) return 1;
            else{
                if(comparerTuiles(ROUTE,t->nord)){
                    tuile* voisine = g->tabTuiles[x-1][y];
                    if(!voisine) return 0;
                    isClosed &= routeFinished(g,x-1,y,SUD,visites);
                }
                if(comparerTuiles(ROUTE,t->sud)){
                    tuile* voisine = g->tabTuiles[x+1][y];
                    if(!voisine) return 0;
                    isClosed &= routeFinished(g,x+1,y,NORD,visites);
                }
                if(comparerTuiles(ROUTE,t->ouest)){
                    tuile* voisine = g->tabTuiles[x][y-1];
                    if(!voisine) return 0;
                    isClosed &= routeFinished(g,x,y-1,EST,visites);
                }
            }
        }else if(comparerTuiles(ROUTE,t->est) && !comparerTuiles(ROUTE,t->centre) && g->tabTuiles[x][y+1] != NULL) isClosed &= routeFinished(g,x,y+1,OUEST,visites);
        else if(comparerTuiles(ROUTE,t->est) && !comparerTuiles(ROUTE,t->centre) && g->tabTuiles[x][y+1] == NULL) return 0;
    }
    else if(pos == OUEST){
        if(comparerTuiles(ROUTE,t->ouest) && comparerTuiles(ROUTE,t->centre)){
            if(!comparerTuiles(ROUTE,t->nord) && !comparerTuiles(ROUTE,t->sud) && ! comparerTuiles(ROUTE,t->est)) return 1;
            else{
                if(comparerTuiles(ROUTE,t->nord)){
                    tuile* voisine = g->tabTuiles[x-1][y];
                    if(!voisine) return 0;
                    isClosed &= routeFinished(g,x-1,y,SUD,visites);
                }
                if(comparerTuiles(ROUTE,t->sud)){
                    tuile* voisine = g->tabTuiles[x+1][y];
                    if(!voisine) return 0;
                    isClosed &= routeFinished(g,x+1,y,NORD,visites);
                }
                if(comparerTuiles(ROUTE,t->est)){
                    tuile* voisine = g->tabTuiles[x][y+1];
                    if(!voisine) return 0;
                    isClosed &= routeFinished(g,x,y+1,OUEST,visites);
                }
            }
        }else if(comparerTuiles(ROUTE,t->ouest) && !comparerTuiles(ROUTE,t->centre) && g->tabTuiles[x][y-1] != NULL) isClosed &= routeFinished(g,x,y-1,EST,visites);
        else if(comparerTuiles(ROUTE,t->ouest) && !comparerTuiles(ROUTE,t->centre) && g->tabTuiles[x][y-1] == NULL) return 0;
    }
    else if(pos == CENTRE){
        if(comparerTuiles(ROUTE,t->centre)){
            if(comparerTuiles(ROUTE,t->nord)){
                tuile* voisine = g->tabTuiles[x-1][y];
                if(!voisine) return 0;
                isClosed &= routeFinished(g,x-1,y,SUD,visites);
            }
            if(comparerTuiles(ROUTE,t->sud)){
                tuile* voisine = g->tabTuiles[x+1][y];
                if(!voisine) return 0;
                isClosed &= routeFinished(g,x+1,y,NORD,visites);
            }
            if(comparerTuiles(ROUTE,t->est)){
                tuile* voisine = g->tabTuiles[x][y+1];
                if(!voisine) return 0;
                isClosed &= routeFinished(g,x,y+1,OUEST,visites);
            }
            if(comparerTuiles(ROUTE,t->ouest)){
                tuile* voisine = g->tabTuiles[x][y-1];
                if(!voisine) return 0;
                isClosed &= routeFinished(g,x,y-1,EST,visites);
            }
        }
    }
    return isClosed;
}
//-------------------
int villeFinished(grille* g,int x,int y,positions pos,posValid** visites){
    if(isVisited(x,y,*visites)) return 1;
    *visites = empilerPosValid(*visites,x,y);
    tuile* t = g->tabTuiles[x][y];
    if(!t) return 0;
    int isClosed = 1;
    if(pos == NORD){
        if(comparerTuiles(VILLE,t->nord) && comparerTuiles(VILLE,t->centre)){
            if(!comparerTuiles(VILLE,t->sud) && !comparerTuiles(VILLE,t->est) && !comparerTuiles(VILLE,t->ouest)) return 1;
            else{
                if(comparerTuiles(VILLE,t->est)){
                    tuile* voisine = g->tabTuiles[x][y+1];
                    if(!voisine) return 0;
                    isClosed &= villeFinished(g,x,y+1,OUEST,visites);
                }
                if(comparerTuiles(VILLE,t->ouest)){
                    tuile* voisine = g->tabTuiles[x][y-1];
                    if(!voisine) return 0;
                    isClosed &= villeFinished(g,x,y-1,EST,visites);
                }
                if(comparerTuiles(VILLE,t->sud)){
                    tuile* voisine = g->tabTuiles[x+1][y];
                    if(!voisine) return 0;
                    isClosed &= villeFinished(g,x+1,y,NORD,visites);
                }
            }
        }else if(comparerTuiles(VILLE,t->nord) && !comparerTuiles(VILLE,t->centre) && g->tabTuiles[x-1][y] != NULL) isClosed &= villeFinished(g,x-1,y,SUD,visites);
        else if(comparerTuiles(VILLE,t->nord) && !comparerTuiles(VILLE,t->centre) && g->tabTuiles[x-1][y] == NULL) return 0;
    }
    else if(pos == SUD){
        if(comparerTuiles(VILLE,t->sud) && comparerTuiles(VILLE,t->centre)){
            if(!comparerTuiles(VILLE,t->nord) && !comparerTuiles(VILLE,t->est) && !comparerTuiles(VILLE,t->ouest)) return 1;
            else{
                if(comparerTuiles(VILLE,t->est)){
                    tuile* voisine = g->tabTuiles[x][y+1];
                    if(!voisine) return 0;
                    isClosed &= villeFinished(g,x,y+1,OUEST,visites);
                }
                if(comparerTuiles(VILLE,t->ouest)){
                    tuile* voisine = g->tabTuiles[x][y-1];
                    if(!voisine) return 0;
                    isClosed &= villeFinished(g,x,y-1,EST,visites);
                }
                if(comparerTuiles(VILLE,t->nord)){
                    tuile* voisine = g->tabTuiles[x-1][y];
                    if(!voisine) return 0;
                    isClosed &= villeFinished(g,x-1,y,SUD,visites);
                }
            }
        }else if(comparerTuiles(VILLE,t->sud) && !comparerTuiles(VILLE,t->centre) && g->tabTuiles[x+1][y] != NULL) isClosed &= villeFinished(g,x+1,y,NORD,visites);
        else if(comparerTuiles(VILLE,t->sud) && !comparerTuiles(VILLE,t->centre) && g->tabTuiles[x+1][y] == NULL) return 0;
    }
    else if(pos == EST){
        if(comparerTuiles(VILLE,t->est) && comparerTuiles(VILLE,t->centre)){
            if(!comparerTuiles(VILLE,t->nord) && !comparerTuiles(VILLE,t->sud) && !comparerTuiles(VILLE,t->ouest)) return 1;
            else{
                if(comparerTuiles(VILLE,t->nord)){
                    tuile* voisine = g->tabTuiles[x-1][y];
                    if(!voisine) return 0;
                    isClosed &= villeFinished(g,x-1,y,SUD,visites);
                }
                if(comparerTuiles(VILLE,t->sud)){
                    tuile* voisine = g->tabTuiles[x+1][y];
                    if(!voisine) return 0;
                    isClosed &= villeFinished(g,x+1,y,NORD,visites);
                }
                if(comparerTuiles(VILLE,t->ouest)){
                    tuile* voisine = g->tabTuiles[x][y-1];
                    if(!voisine) return 0;
                    isClosed &= villeFinished(g,x,y-1,EST,visites);
                }
            }
        }else if(comparerTuiles(VILLE,t->est) && !comparerTuiles(VILLE,t->centre) && g->tabTuiles[x][y+1] != NULL) isClosed &= villeFinished(g,x,y+1,OUEST,visites);
        else if(comparerTuiles(VILLE,t->est) && !comparerTuiles(VILLE,t->centre) && g->tabTuiles[x][y+1] == NULL) return 0;
    }
    else if(pos == OUEST){
        if(comparerTuiles(VILLE,t->ouest) && comparerTuiles(VILLE,t->centre)){
            if(!comparerTuiles(VILLE,t->nord) && !comparerTuiles(VILLE,t->sud) && !comparerTuiles(VILLE,t->est)) return 1;
            else{
                if(comparerTuiles(VILLE,t->nord)){
                    tuile* voisine = g->tabTuiles[x-1][y];
                    if(!voisine) return 0;
                    isClosed &= villeFinished(g,x-1,y,SUD,visites);
                }
                if(comparerTuiles(VILLE,t->sud)){
                    tuile* voisine = g->tabTuiles[x+1][y];
                    if(!voisine) return 0;
                    isClosed &= villeFinished(g,x+1,y,NORD,visites);
                }
                if(comparerTuiles(VILLE,t->est)){
                    tuile* voisine = g->tabTuiles[x][y+1];
                    if(!voisine) return 0;
                    isClosed &= villeFinished(g,x,y+1,OUEST,visites);
                }
            }
        }else if(comparerTuiles(VILLE,t->ouest) && !comparerTuiles(VILLE,t->centre) && g->tabTuiles[x][y-1] != NULL) isClosed &= villeFinished(g,x,y-1,EST,visites);
        else if(comparerTuiles(VILLE,t->ouest) && !comparerTuiles(VILLE,t->centre) && g->tabTuiles[x][y-1] == NULL) return 0;
    }
    else if(pos == CENTRE){
        if(comparerTuiles(VILLE,t->centre)){
            if(comparerTuiles(VILLE,t->nord)){
                tuile* voisine = g->tabTuiles[x-1][y];
                if(!voisine) return 0;
                isClosed &= villeFinished(g,x-1,y,SUD,visites);
            }
            if(comparerTuiles(VILLE,t->sud)){
                tuile* voisine = g->tabTuiles[x+1][y];
                if(!voisine) return 0;
                isClosed &= villeFinished(g,x+1,y,NORD,visites);
            }
            if(comparerTuiles(VILLE,t->est)){
                tuile* voisine = g->tabTuiles[x][y+1];
                if(!voisine) return 0;
                isClosed &= villeFinished(g,x,y+1,OUEST,visites);
            }
            if(comparerTuiles(VILLE,t->ouest)){
                tuile* voisine = g->tabTuiles[x][y-1];
                if(!voisine) return 0;
                isClosed &= villeFinished(g,x,y-1,EST,visites);
            }
        }
    }
    return isClosed;
}
//-------------------
int calculScore(grille* g,int finished,meeple* m,int *fin){
    *fin = 0;
    if(m == NULL) return 0;
    if(m->x < 0 || m->x >= MAX || m->y < 0 || m->y >= MAX) return 0;
    if(g->tabTuiles[m->x][m->y] == NULL) return 0;
    if(g->tabTuiles[m->x][m->y]->meeples == NULL) return 0;
    if(g->tabTuiles[m->x][m->y]->meeples != m) return 0;
    tuile* current = g->tabTuiles[m->x][m->y];
    tuileTypes t;
    switch(m->tuilePosition){
        case CENTRE: t = current->centre; break;
        case NORD: t = current->nord; break;
        case SUD: t = current->sud; break;
        case EST: t = current->est; break;
        case OUEST: t = current->ouest; break;
        default: return 0;
    }
    posValid* visites = NULL;
    int score = 0;
    int isComplete = 0;
    if(t == ABBAYE){
        isComplete = abbayeFinished(g,m->x,m->y);
        if(isComplete || finished){
            score = compterAbbaye(g,m->x,m->y);
        }
    }
    else if(t == ROUTE){
        isComplete = routeFinished(g,m->x,m->y,m->tuilePosition,&visites);
        visites = NULL;
        if(isComplete || finished){
            score = compterRoute(g,m->x,m->y,m->tuilePosition,&visites);
        }
    }
    else if(comparerTuiles(VILLE, t)){
        isComplete = villeFinished(g,m->x,m->y,m->tuilePosition,&visites);
        visites = NULL;
        if(isComplete || finished){
            score = compterVille(g,m->x,m->y,m->tuilePosition,&visites);
            if(isComplete && !finished) score *= 2;
        }
    }
    *fin = isComplete;
    return score;
}