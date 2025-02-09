#include "../include/tuile.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    pileTuiles p;
    initialiserPile("C:/carcassonne/lib/tuiles.csv",&p);
    printf("%d %d %d %d %d\n",p.pile[0]->nord,p.pile[0]->est,p.pile[0]->sud,p.pile[0]->ouest,p.pile[0]->centre);
    return 0;
}