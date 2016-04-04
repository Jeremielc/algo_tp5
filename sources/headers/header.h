/* header.h */
//Jérémie Leclerc & Pierrick Hue

#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define WHITE           1
#define GREY            0
#define BLACK           -1
#define MAXSOMMET       250
#define MAXVALUATION    20.0
#define MAXSUCC         10

typedef int ELEMENT;

typedef struct CELL {
    int extremity;
    int value;
    struct CELL* next;
} CELL;

/*typedef struct CELL_INT {
    int value;
    struct CELL_INT* next;
} CELL_INT;*/

typedef struct LADJ /* listes d'adjacence */ {
    int nbSom;
    int nbArc;
    CELL** tab;
    int* predNumber;
} LADJ;

typedef struct QUEUE {
    int size;
    CELL/*_INT*/* head;
    CELL/*_INT*/* tail;
} QUEUE;

typedef struct REALATED_COMPONENTS {
    int* relatedComponents;
    int nbComponents;
} REALATED_COMPONENTS;

typedef struct GRAPH {
    int nbSummit;
    int nbArc;
    float** matrix; /* matrice d'adjacence */
    char* nodeStatus;
    REALATED_COMPONENTS componentInfo;
} GRAPH;

typedef struct t_ens {
    int* parent;
    int nbElem;
    int nbClass;
} t_ens;

//L_ADJ.c
void    affiche_graphe(LADJ);
void    affiche_liste(CELL*);
LADJ    charge_graphe(char*);
CELL*   creer_cellule(int, int, CELL*);
LADJ    init_ladj(int, int);
LADJ    inverse(LADJ);

//main.c
bool topologicalMarking(LADJ*);
LADJ load_graph(char*);
void displayList(QUEUE*);
bool hasPredecessor(int*, int);

//queue.c
QUEUE   add(ELEMENT, QUEUE);
ELEMENT add_2(QUEUE*);
void    concat(QUEUE*, QUEUE*);
void    displayQueue(char*, QUEUE);
QUEUE   get(QUEUE);
ELEMENT getHeadValue(QUEUE);
int     isEmpty(QUEUE);
QUEUE   newEmptyQueue();

#endif	// HEADER_H

