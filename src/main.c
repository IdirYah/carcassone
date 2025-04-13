#include <stdio.h>
#include <stdlib.h>
#include "../include/tuile.h"
#include "../include/meeple.h"
#include "../include/affichage.h"
#include "../include/joueur.h"

int main(){
    tabJoueurs j;
    creerJoueurs(&j,3);
    afficherScore(&j);
    return 0;
}