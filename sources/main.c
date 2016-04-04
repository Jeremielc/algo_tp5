/* main.c */
//Jérémie Leclerc & Pierrick Hue

#include "headers/header.h"

int main(int argc, char** argv) {
    LADJ graph;

    if (argc != 2) {
        printf("%s\n", "Veuillez specifier un fichier de graphe.");
        exit(-1);
    }

    graph = load_graph(argv[1]);

    for (int i = 0; i < graph.nbSom; i++) {
        printf("Noeud %d : %d\n", i, graph.predNumber[i]);
    }
    printf("\n");

    bool topographyIsPossible = topologicalMarking(&graph);

    for (int i = 0; i < graph.nbSom; i++) {
        printf("Noeud %d : %d\n", i, graph.predNumber[i]);
    }
    printf("\n");

    if (topographyIsPossible) {
        printf("%s\n", "Topographie possible");
    } else {
        printf("%s\n", "Topographie impossible");
    }

    free(graph.predNumber);

    return 0;
}

bool topologicalMarking(LADJ* graph) {
    if (graph == NULL) {
        return false;
    }

    QUEUE summitWithoutPredQueue;
    bool topographyIsPossible = true;


    summitWithoutPredQueue = newEmptyQueue();

    // 1 - Recherche des sommets sans prédecesseurs
    for (int i = 0; i < graph->nbSom; i++) {
        if (graph->predNumber[i] == 0) {
            summitWithoutPredQueue = add(i, summitWithoutPredQueue);
        }
    }

    if (isEmpty(summitWithoutPredQueue)) {
        topographyIsPossible = false;
    } else {
        displayList(&summitWithoutPredQueue);
    }

    // 2 - Reconstruction du graphe
    int value = 0;
    CELL* temp;

    while (!isEmpty(summitWithoutPredQueue)) {
        value = getHeadValue(summitWithoutPredQueue);
        temp = graph->tab[value];
        printf("%s %d\n", "temp->extremity :", temp->extremity);

        while (temp != NULL) {
            graph->predNumber[temp->extremity] = graph->predNumber[temp->extremity] - 1;
            
            if (graph->predNumber[temp->extremity] == 0) {
                summitWithoutPredQueue = add(temp->extremity, summitWithoutPredQueue);
            }
            
            temp = temp->next;
        }

        summitWithoutPredQueue = get(summitWithoutPredQueue); //Utiliser get pour retirer le noeud dans la file.
    }

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

bool hasPredecessor(int* predNumber, int nbSom) {
    for (int i = 0; i < nbSom; i++) {
        if (predNumber[i] != 0) {
            return true;
        }
    }

    return false;
}