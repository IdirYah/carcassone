#include "../include/jeu.h"
#include "../include/joueur.h"
#include "../include/tuile.h"   
#include "../include/meeple.h"
#include "../include/controlleur.h"
#include "../include/affichage.h"
#include <stdio.h>  
#include <stdlib.h>
#include <unistd.h>
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
    melangerTuile(p);
    while(!finished){
        t = depilerTuile(p);
        if(pileVide(*p) == 1) finished = 1;
        int stop = 0;
        while(!stop){
            printf("C'est au tour du joueur numéro %d.\n",(i%n)+1);
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
            printf("Grille:\n");
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
                    int x,y;
                    printf("Veuillez entrer la position (x,y) pour placer la tuile: ");
                    scanf("%d %d",&x,&y);
                    if(isPositionTuileValide(g,t,x,y)){
                        poserTuile(g,x,y,t);
                        if(meepleController(g,x,y,NORD) == 1 || meepleController(g,x,y,SUD) == 1 || meepleController(g,x,y,EST) == 1 || meepleController(g,x,y,OUEST) == 1 || meepleController(g,x,y,CENTRE) == 1){  
                            printf("Voulez-vous placer un meeple sur la tuile? (1: Oui, 0: Non): ");
                            int choixMeeple;
                            scanf("%d",&choixMeeple);
                            if(choixMeeple == 1){
                                int posMeeple;
                                printf("Veuillez choisir la position du meeple (0: NORD, 1: SUD, 2: EST, 3: OUEST, 4: CENTRE): ");
                                scanf("%d",&posMeeple);
                                if(posMeeple == 0){
                                    if(meepleController(g,x,y,NORD) == 1){
                                        poserMeeple(g,j,(i%n)+1,NORD,x,y);
                                    }else{
                                        printf("Impossible de poser le meeple dans cette position.\n");
                                    }
                                }else if(posMeeple == 1){
                                    if(meepleController(g,x,y,SUD) == 1){
                                        poserMeeple(g,j,(i%n)+1,SUD,x,y);
                                    }else{
                                        printf("Impossible de poser le meeple dans cette position.\n");
                                    }
                                }else if(posMeeple == 2){
                                    if(meepleController(g,x,y,EST) == 1){
                                        poserMeeple(g,j,(i%n)+1,EST,x,y);
                                    }else{
                                        printf("Impossible de poser le meeple dans cette position.\n");
                                    }
                                }else if(posMeeple == 3){
                                    if(meepleController(g,x,y,OUEST) == 1){
                                        poserMeeple(g,j,(i%n)+1,OUEST,x,y);
                                    }else{
                                        printf("Impossible de poser le meeple dans cette position.\n");
                                    }
                                }else if(posMeeple == 4){
                                    if(meepleController(g,x,y,CENTRE) == 1){
                                        poserMeeple(g,j,(i%n)+1,CENTRE,x,y);
                                    }else{
                                        printf("Impossible de poser le meeple dans cette position.\n");
                                    }
                                }else{
                                    printf("Position invalide.\n");  
                                }
                            }
                        }
                        for(int k=0;k<=i%n;k++){
                            int score = 0;
                            listMeeples* tete = j->player[k]->teteListe;
                            listMeeples* tmp = NULL;
                            while(tete != NULL){
                                int fin = 0;
                                score += calculScore(g,0,g->tabTuiles[tete->m->x][tete->m->y]->meeples,&fin);
                                if(fin == 1){
                                    rendreMeeple(g,j,k,tete->m);
                                    if(tmp == NULL){tete = j->player[k]->teteListe;}
                                    else{tete = tmp->suivant;}
                                }else{
                                    tmp = tete;
                                    tete = tete->suivant;
                                }
                            }
                            j->player[k]->score += score;
                        }
                        stop = 1;
                        i++;
                    }else{
                        printf("Positions invalide. Veuillez reessayer.\n");
                    }
                    sleep(1);
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
                case 4:
                    finished = 1;
                    stop = 1;
                    printf("Vous avez choisi de quitter le jeu.\n");
                    printf("Merci d'avoir joué!\n");
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
//--------------------
void finJeu(grille* g,tabJoueurs* j,int n){
    printf("Fin du jeu!\n");
    for(int k=0;k<n;k++){
        int score = 0;
        listMeeples* tete = j->player[k]->teteListe;
        listMeeples* tmp = NULL;
        while(tete != NULL){
            int fin = 0;
            score += calculScore(g,1,g->tabTuiles[tete->m->x][tete->m->y]->meeples,&fin);
            rendreMeeple(g,j,k,tete->m);
            if(tmp == NULL){tete = j->player[k]->teteListe;}
            else{tete = tmp->suivant;}                    
        }
        j->player[k]->score += score;
    }
    printf("Scores finaux:\n");
    afficherScore(j);
    printf("Merci d'avoir joué!\n");
}