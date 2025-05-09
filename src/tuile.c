#include "../include/tuile.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//---------------------------------
tuile *creerTuile(tuileTypes north,tuileTypes south,tuileTypes east,tuileTypes west,tuileTypes center){
    tuile *t = (tuile*)malloc(sizeof(tuile));
    t->centre = center;
    t->est = east;
    t->ouest = west;
    t->nord = north;
    t->sud = south;
    t->meeples = NULL;
    return t;
}
//------------------------------------
void libererTuile(tuile *t){
    free(t);
}
//------------------------------------
tuileTypes convertirChaine(char *chaine){
    if(!strcmp(chaine,"pre")){
        return PRE;
    }
    if(!strcmp(chaine,"village")){
        return VILLAGE;
    }
    if(!strcmp(chaine,"ville")){
        return VILLE;
    }
    if(!strcmp(chaine,"blason")){
        return BLASON;
    }
    if(!strcmp(chaine,"route")){
        return ROUTE;
    }
    return ABBAYE;
}
//------------------------------------
void initialiserPile(char *fname,pileTuiles *p){
    p->indiceCourant = 0;
    FILE *f = fopen(fname,"rb");
    if(f == NULL){
        perror("Error\n");
        return;
    }
    char chaine[15];
    tuileTypes north,south,east,west,center;
    char c;
    int i = 0;
    int j = 0;
    int k = 1;
    while(fread(&c,sizeof(char),1,f) == 1){
        if(c != '\n' && c != ','){
            chaine[j] = c;
            j++;
        }else{
            chaine[j] = '\0';
            j = 0;
            if(k%5 == 1){
                north = convertirChaine(chaine);
            }else if(k%5 == 2){
                east = convertirChaine(chaine);
            }else if(k%5 == 3){
                south = convertirChaine(chaine);
            }else if(k%5 == 4){
                west = convertirChaine(chaine);
            }else{
                center = convertirChaine(chaine);
                p->pile[i] = creerTuile(north,south,east,west,center);
                i++;
            }
            k++;
        }
    }
    fclose(f);
}
//------------------------------------
tuile* depilerTuile(pileTuiles *t){
    tuile *tmp = t->pile[t->indiceCourant];
    t->indiceCourant++;
    return tmp;
}
//------------------------------------
int pileVide(pileTuiles t){
    return t.indiceCourant == NB_TUILES;
}
//------------------------------------
tuile *rotationTuile(tuile *t,int angle){
    tuile *tmp = (tuile*)malloc(sizeof(tuile));
    if(tmp == NULL){;
        printf("Erreur d'allocation de mémoire\n");
        return NULL;
    }
    tmp->centre = t->centre;
    tmp->meeples = t->meeples;
    int ancienNord = t->nord;
    int ancienSud = t->sud;
    int ancienEst = t->est;
    int ancienOuest = t->ouest;
    if(angle == -90){
        tmp->nord = ancienOuest;
        tmp->est = ancienNord;
        tmp->sud = ancienEst;
        tmp->ouest = ancienSud;
    }else{
        tmp->nord = ancienEst;
        tmp->est = ancienSud;
        tmp->sud = ancienOuest;
        tmp->ouest = ancienNord;
    }
    return tmp;
}
//------------------------------
void poserTuile(grille *g,int ligne,int colonne,tuile *t){
    g->tabTuiles[ligne][colonne] = t;
}