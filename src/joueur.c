#include "../include/joueur.h"
#include <stdlib.h>
//----------------------------
joueur* creerJoueur(int idf){
    joueur *j = (joueur*)malloc(sizeof(joueur));
    j->id = idf;
    j->score = 0;
    j->teteListe = NULL;
    return j;
}
//----------------------------
void creerJoueurs(tabJoueurs *js,int n){
    js->nbJoueurs = n;
    js->player = (joueur**)malloc(sizeof(joueur*));
    for(int i=1;i<=n;i++){
        js->player[i-1] = creerJoueur(i);
    }
}