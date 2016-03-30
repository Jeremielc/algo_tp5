/* L_ADJ.c */
//C.Porquet

#include "headers/header.h"

int main(int argc, char* *argv) {
    LADJ graph, graph_inverse;

    if (argc != 2) {
        exit(-1);
    }

    graph = charge_graphe(argv[1]);
    affiche_graphe(graph);

    graph_inverse = inverse(graph);
    affiche_graphe(graph_inverse);

    return 0;
}

CELL* creer_cellule(int extr, int val, CELL* suiv) {
    CELL* p;

    p = (CELL*) malloc(sizeof (CELL));
    if (p == NULL) {
        exit(-1);
    }

    p->extremite = extr;
    p->valuation = val;
    p->suivant = suiv;

    return p;
}

void affiche_liste(CELL* p) {
    while (p) {
        printf("<%d-%d>\t", p->extremite, p->valuation);
        p = p->suivant;
    };
    
    printf("\n");
}

LADJ init_ladj(int nsom, int nar) /* allocation dynamique et initialisation */ {
    LADJ graph;

    graph.nbsom = nsom;
    graph.nbar = nar;
    graph.tab = (CELL* *) calloc(nsom, sizeof (CELL*));

    if (graph.tab == NULL) {
        exit(-1);
    }

    return graph;
}

void affiche_graphe(LADJ graph) {
    int i;

    for (i = 0; i < graph.nbsom; i++) {
        if (graph.tab[i]) {
            printf("Successeurs de %d : ", i);
            affiche_liste(graph.tab[i]);
        }
    }
    printf("\n");
}

LADJ charge_graphe(char* nom_fichier) {
    LADJ graph;
    int nsom, nar;
    FILE* fp;
    int i, ori, ext, val;
    CELL* p;

    fp = fopen(nom_fichier, "rt");
    
    if (fp == NULL) {
        exit(-1);
    }
    
    fscanf(fp, "%d %d", &nsom, &nar);
    graph = init_ladj(nsom, nar);
    
    for (i = 0; i < nar; i++) {
        fscanf(fp, "%d %d %d", &ori, &ext, &val);
        p = creer_cellule(ext, val, graph.tab[ori]);
        graph.tab[ori] = p; /* on empile */
    }
    
    fclose(fp);
    
    return graph;
}

LADJ inverse(LADJ graph) {
    LADJ graph_inverse;
    int i;
    CELL* p, *q;

    graph_inverse = init_ladj(graph.nbsom, graph.nbar);
    
    for (i = 0; i < graph.nbsom; i++) {
        p = graph.tab[i];
        
        while (p) {
            q = creer_cellule(i, p->valuation, graph_inverse.tab[p->extremite]);
            graph_inverse.tab[p->extremite] = q; /* on empile */
            p = p->suivant;
        }
    }
    
    return graph_inverse;
}


/*******************************************************************************
Trace d'execution sur le fichier :
6
8
0 1 3
1 1 6
1 3 2
1 4 1
3 0 2
3 4 2
4 3 7
5 2 1

Successeurs de 0 : <1-3>
Successeurs de 1 : <4-1>        <3-2>   <1-6>
Successeurs de 3 : <4-2>        <0-2>
Successeurs de 4 : <3-7>
Successeurs de 5 : <2-1>

Successeurs de 0 : <3-2>
Successeurs de 1 : <1-6>        <0-3>
Successeurs de 2 : <5-1>
Successeurs de 3 : <4-7>        <1-2>
Successeurs de 4 : <3-2>        <1-1>
	
 *******************************************************************************/
