/* main.c */
//Jérémie Leclerc & Pierrick Hue

#include "headers/header.h"

int main(int argc, char** argv) {
    LADJ graph;

    if (argc != 2) {
        printf("%s\n", "Veuillez specifier un fichier de graphe.");
        exit(-1);
    }

    //graph = charge_graphe(argv[1]);
    graph = load_graph(argv[1]);

    for (int i = 0; i < graph.nbsom; i++) {
        printf("Noeud %d : %d\n", i, graph.predNumber[i]);
    }
    printf("\n");
    
    topologicalMarking(&graph);
    free(graph.predNumber);

    return 0;
}

bool topologicalMarking(LADJ* graph) {
    if (graph == NULL) {
        return false;
    }

    QUEUE topographicQueue, summitQueue;
    bool topographyIsPossible = true;

    topographicQueue = newEmptyQueue();
    summitQueue = newEmptyQueue();

    // 1 - Recherche des sommets sans prédecesseurs
    for (int i = 0; i < graph->nbsom; i++) {
        if (graph->predNumber[i] == 0) {
            summitQueue = add(i, summitQueue);
        }
    }

    if (isEmpty(summitQueue)) {
        topographyIsPossible = false;
    } else {
        displayList(&summitQueue);
    }

    // 2 - Reconstruction du graphe

    return topographyIsPossible;
}

LADJ load_graph(char* fileName) {
    LADJ graph;
    int nbsom, nbar, ori, ext, val;
    FILE* canal;
    CELL* cell;

    canal = fopen(fileName, "rt");

    if (canal == NULL) {
        exit(-1);
    }

    fscanf(canal, "%d %d", &nbsom, &nbar);
    graph = init_ladj(nbsom, nbar);

    //Initialisation du tableau du nom des predecesseurs
    graph.predNumber = (int*) malloc(graph.nbsom * sizeof (int));
    for (int i = 0; i < graph.nbsom; i++) {
        graph.predNumber[i] = 0;
    }

    for (int i = 0; i < nbar; i++) {
        fscanf(canal, "%d %d %d", &ori, &ext, &val);
        cell = creer_cellule(ext, val, graph.tab[ori]);
        graph.tab[ori] = cell; /* on empile */

        graph.predNumber[ext] += 1;
    }

    fclose(canal);

    return graph;
}

void displayList(QUEUE* queue) {
    CELL* cell = queue->head;

    while (cell != NULL) {
        printf("Numero de sommet sans predecesseur : %d\n", cell->value);
        cell = cell->next;
    }
}