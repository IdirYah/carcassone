#include "../include/jeu.h"
#include "../include/joueur.h"
#include "../include/tuile.h"   
#include "../include/meeple.h"
#include "../include/controlleur.h"
#include "../include/affichage.h"
#include <stdio.h>  
#include <stdlib.h>
//--------------------
int initialiserJeu(grille* g,tabJoueurs* j,char *fname,pileTuiles *p){
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
//--------------------
void deroulementJeu(grille* g,tabJoueurs* j,pileTuiles* p,int n){
    int i=0;
    int finished = 0;
    int choix = 0;
    tuile* t = NULL;
    tuile* t1 = t;
    t = depilerTuile(p);
    g->tabTuiles[72][72] = t;
    while(!finished){
        t = depilerTuile(p);
        if(pileVide(*p) == 1) finished = 1;
        printf("C'est au tour du joueur numéro %d.\n",i%n+1);
        int stop = 0;
        while(!stop){
            afficherScore(j);
            printf("\n");
            symbolDesignation();
            printf("\n");
            printf("Tuile à jouer: \n");
            afficherTuileNord(t);
            printf("\n");
            afficherTuileReste(t);
            printf("\n");
            afficherTuileSud(t);
            printf("\n");
            printf("\n");
            afficherGrille(g);
            printf("\n");
            posValid* tete = positionsValid(g,t);
            posValid* tmp = tete;
            if(tete == NULL){
                printf("Aucune position valide pour placer la tuile.\n");
                stop = 1;
                continue;
            }
            printf("Voici les positions valides pour placer la tuile:\n");
            while(tmp != NULL){
                printf("(%d,%d) ",tmp->ligne,tmp->colonne);
                tmp = tmp->suivant;
            }
            printf("\n");
            printf("\n");
            printf("1. Placer la tuile.\n");
            printf("2. Faire une rotation 90°.\n");
            printf("3. Faire une rotation -90°.\n");
            printf("Faites votre choix : ");
            scanf("%d",&choix);
            switch(choix){
                case 1:
                    if(tete == NULL){
                        printf("Aucune position valide pour placer la tuile.\n");
                        stop = 1;
                    }else{
                        int x,y;
                        printf("Veuillez entrer la position (x,y) pour placer la tuile: ");
                        scanf("%d %d",&x,&y);
                        if(isPositionTuileValide(g,t,x,y) == 1){
                            g->tabTuiles[x][y] = t;
                            stop = 1;
                            i++;
                            afficherGrille(g);
                        }else{
                            printf("Position invalide. Veuillez reessayer.\n");
                        }
                    }
                    system("clear");
                    break;
                case 2:
                    t1 = rotationTuile(t,90);
                    t = t1;
                    system("clear");
                    break;
                case 3:
                    t1 = rotationTuile(t,-90);
                    t = t1;
                    system("clear");
                    break;
                default:
                    printf("Choix invalide. Veuillez reessayer.\n");
                    system("clear");
                    break;  
            }
        }
    }
}