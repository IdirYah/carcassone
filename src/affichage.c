#include <stdio.h>
#include "../include/affichage.h"
//----------------
char tuilePosToChar(tuileTypes t){
    if(t == VILLAGE){
        return 'O';
    }
    if(t == ROUTE){
        return 'R';
    }
    if(t == PRE){
        return 'P';
    }
    if(t == VILLE){
        return 'V';
    }
    if(t == BLASON){
        return 'B';
    }
    return 'A';
}
//---------------------
void afficherTuile(tuile* t){
    printf("  %c\n",tuilePosToChar(t->nord));
    printf("%c %c %c\n",tuilePosToChar(t->ouest),tuilePosToChar(t->centre),tuilePosToChar(t->est));
    printf("  %c\n",tuilePosToChar(t->sud)); 
}