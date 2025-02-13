#include "../include/joueur.h"
#include "../include/tuile.h"
#include <stdlib.h>
//----------------------------
joueur* creerJoueur(int idf,couleurs c){
    joueur *j = (joueur*)malloc(sizeof(joueur));
    j->id = idf;
    j->score = 0;
    j->teteListe = NULL;
    for(int i=0;i<7;i++){
        meeple *m = creerMeeple(c);
        empilerMeeple(m,j);
    }
    return j;
}
//----------------------------
void creerJoueurs(tabJoueurs *js,int n){
    js->nbJoueurs = n;
    js->player = (joueur**)malloc(sizeof(joueur*));
    for(int i=0;i<n;i++){
        js->player[i] = creerJoueur(i,i);
    }
}
//----------------------------
void poserMeeple(grille g,tabJoueurs *tab,int idf,positions p,int dx,int dy){
    int i = 0;
    while(i<tab->nbJoueurs && tab->player[i]->id != idf){
        i++;
    }
    if(i>=tab->nbJoueurs){
        return;
    }
    listMeeples *tmp = tab->player[i]->teteListe;
    while(tmp != NULL && tmp->m->tuilePosition != RIEN){
        tmp = tmp->suivant;
    }
    if(tmp == NULL){
        return;
    }
    tmp->m->tuilePosition = p;
    tmp->m->x = dx;
    tmp->m->y = dy;
    g.tabTuiles[dx][dy]->meeples = tmp->m;
}
//----------------------------