/* header.h */
//Jérémie Leclerc & Pierrick Hue

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>

typedef struct CELL {
    int extremite;
    int valuation;
    struct CELL* suivant;
} CELL;

typedef struct LADJ /* listes d'adjacence */ {
    int nbsom, nbar;
    CELL** tab;
} LADJ;

//L_ADJ.c
void affiche_graphe(LADJ);
void affiche_liste(CELL*);
LADJ charge_graphe(char*);
CELL* creer_cellule(int, int, CELL*);
LADJ init_ladj(int, int);
LADJ inverse(LADJ);

//main.c


#endif	// HEADER_H
