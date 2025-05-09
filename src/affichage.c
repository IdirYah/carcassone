#include <stdio.h>
#include "../include/affichage.h"
#include "../include/meeple.h"
#include "../include/joueur.h"
//----------------
int colorToInt(couleurs c){
    if(c == BLEU) return 44;
    if(c == ROUGE) return 41;
    if(c == VERT) return 42;
    if(c == JAUNE) return 43;
    if(c == NOIR) return 40;
    return 0;
}
//----------------
char tuilePosToChar(tuileTypes t){
    if(t == VILLAGE) return 'O';
    if(t == ROUTE) return 'R';
    if(t == PRE) return 'P';
    if(t == VILLE) return 'V';
    if(t == BLASON) return 'B';
    return 'A';
}
//---------------------
void symbolDesignation(){
    printf("O : VILLAGE | R : ROUTE | P : PRE | V : VILLE | B : BLASON\n");
}
//---------------------
void afficherTuileNord(tuile* t){
    if(t->meeples != NULL &&t->meeples->tuilePosition == NORD){
        printf("|  \033[%dm%c\033[0m  |",colorToInt(t->meeples->couleur),tuilePosToChar(t->nord));
    }else{
        printf("|  %c  |",tuilePosToChar(t->nord));
    }
}
//---------------------
void afficherTuileSud(tuile* t){
    if(t->meeples != NULL &&t->meeples->tuilePosition == SUD){
        printf("|  \033[%dm%c\033[0m  |",colorToInt(t->meeples->couleur),tuilePosToChar(t->sud));
    }else{
        printf("|  %c  |",tuilePosToChar(t->sud));
    }
}
//---------------------
void afficherTuileReste(tuile* t){
    if(t->meeples != NULL && t->meeples->tuilePosition == OUEST){
        printf("|\033[%dm%c\033[0m",colorToInt(t->meeples->couleur),tuilePosToChar(t->ouest));
    }else{
        printf("|%c",tuilePosToChar(t->ouest));
    }
    if(t->meeples != NULL && t->meeples->tuilePosition == CENTRE){
        printf(" \033[%dm%c\033[0m",colorToInt(t->meeples->couleur),tuilePosToChar(t->centre));
    }else{
        printf(" %c",tuilePosToChar(t->centre));
    }
    if(t->meeples != NULL && t->meeples->tuilePosition == EST){
        printf(" \033[%dm%c\033[0m|",colorToInt(t->meeples->couleur),tuilePosToChar(t->est));
    }else{
        printf(" %c|",tuilePosToChar(t->est));
    }
}
//---------------------
void afficherScore(tabJoueurs* t){
    printf("ID\tScore\n");
    printf("-----------------\n");
    for(int i=0;i<t->nbJoueurs;i++){
        printf("%d\t%d\n",t->player[i]->id,t->player[i]->score);
    }
}
//---------------------
void afficherGrille(grille* g){
    int iMin = MAX, iMax = 0;
    int jMin = MAX, jMax = 0;
    for(int i=0; i<MAX;i++){
        for(int j=0;j<MAX;j++){
            if(g->tabTuiles[i][j] != NULL){
                if (i < iMin) iMin = i;
                if (i > iMax) iMax = i;
                if (j < jMin) jMin = j;
                if (j > jMax) jMax = j;
            }
        }
    }
    for (int i = iMin; i <= iMax; i++){
        for(int j=jMin;j<=jMax;j++) {
            if(g->tabTuiles[i][j] != NULL) printf("+-----+");
            else printf("       ");
        }
        printf("\n");
        for(int j=jMin;j<=jMax;j++){
            if(g->tabTuiles[i][j] != NULL) afficherTuileNord(g->tabTuiles[i][j]);
            else printf("       ");
        }
        printf("\n");
        for(int j=jMin;j<=jMax;j++){
            if(g->tabTuiles[i][j] != NULL) afficherTuileReste(g->tabTuiles[i][j]);
            else printf("       ");
        }
        printf("\n");
        for(int j=jMin;j<=jMax;j++){
            if(g->tabTuiles[i][j] != NULL) afficherTuileSud(g->tabTuiles[i][j]);
            else printf("       ");
        }
        printf("\n");
        for(int j=jMin;j<=jMax;j++){
            if(g->tabTuiles[i][j] != NULL) printf("+-----+");
            else printf("       ");
        }
        printf("\n");
    }
}
