#include "../include/joueur.h"
#include "../include/tuile.h"
#include <stdlib.h>
//----------------------------
joueur* creerJoueur(int idf,couleurs c){
    joueur *j = (joueur*)malloc(sizeof(joueur));
    j->id = idf;
    j->score = 0;
    j->teteListe = NULL;
    return j;
}
//----------------------------
void creerJoueurs(tabJoueurs *js,int n){
    js->nbJoueurs = n;
    js->player = (joueur**)malloc(n*sizeof(joueur*));
    for(int i=0;i<n;i++){
        js->player[i] = creerJoueur(i+1,i);
    }
}
//----------------------------
int longuerList(joueur *j){
    int i = 0;
    listMeeples *tmp = j->teteListe;
    while(tmp != NULL){
        i++;
        tmp = tmp->suivant;
    }
    return i;
}
//----------------------------
int poserMeeple(grille* g,tabJoueurs *tab,int idf,positions p,int dx,int dy){
    if(longuerList(tab->player[idf-1])>=7){
        return 0;
    }
    meeple* mp = (meeple*)malloc(sizeof(meeple));
    mp->x = dx;
    mp->y = dy;
    mp->couleur = idf;
    mp->tuilePosition = p;
    empilerMeeple(mp,tab->player[idf-1]);
    g->tabTuiles[dx][dy]->meeples = mp;
    return 1;
}
//----------------------------
void rendreMeeple(grille* g,tabJoueurs *tab,int idf,meeple* mp){
    listMeeples* tmp = tab->player[idf]->teteListe;
    listMeeples* prev = NULL;
    if(mp == NULL) return;
    while(tmp != NULL){
        if(tmp->m->x == mp->x && tmp->m->y == mp->y){
            if(prev == NULL){
                tab->player[idf]->teteListe = tmp->suivant;
            }else{
                prev->suivant = tmp->suivant;
            }
            free(tmp);
            g->tabTuiles[mp->x][mp->y]->meeples = NULL;
            return;
        }
        prev = tmp;
        tmp = tmp->suivant;
    }
}