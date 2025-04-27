#include "../include/jeu.h"
#include "../include/joueur.h"
#include "../include/tuile.h"  
#include "../include/meeple.h"
#include <stdio.h>  
#include <stdlib.h>
//--------------------
int intialiserJeu(grille* g,tabJoueurs* j,char *fname,pileTuiles *p){
    printf("Initialisation du jeu...\n");
    int n;
    printf("Veuillez choisir le nombre de joueurs (2-5): ");
    do{
        scanf("%d",&n);
        if(n<2 || n>5){
            printf("Nombre de joueurs invalide. Veuillez reessayer: ");
        }
    }while(n<2 || n>5);
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++){
            g->tabTuiles[i][j] = NULL;
        }
    }
    creerJoueurs(j,n);
    initialiserPile(fname,p);
    return n;
}