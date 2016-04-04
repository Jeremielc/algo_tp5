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

    if (topographyIsPossible) {
        printf("%s\n", "Topologie possible");
    } else {
        printf("%s\n", "Topologie impossible");
    }

    free(graph.predNumber);

    return 0;
}

bool topologicalMarking(LADJ* graph) {
    if (graph == NULL) {
        return false;
    }

    QUEUE_INT summitWithoutPredQueue, topologicalQueue;
    bool topologyIsPossible = false;

    summitWithoutPredQueue = newEmptyQueue_int();
    topologicalQueue = newEmptyQueue_int();

    // 1 - Recherche des sommets sans prédecesseurs
    for (int i = 0; i < graph->nbSom; i++) {
        if (graph->predNumber[i] == 0) {
            summitWithoutPredQueue = add_int(i, summitWithoutPredQueue);
        }
    }

    // 2 - Reconstruction du graphe
    int value = 0;
    CELL* temp;

    while (!isEmpty_int(summitWithoutPredQueue)) {
        value = getHeadValue_int(summitWithoutPredQueue);
        temp = graph->tab[value];
        
        /*if (temp) {
            printf("%s %d\n", "temp->extremity :", temp->extremity);
        }*/

        while (temp != NULL) {
            graph->predNumber[temp->extremity] = graph->predNumber[temp->extremity] - 1;

            if (graph->predNumber[temp->extremity] == 0) {
                summitWithoutPredQueue = add_int(temp->extremity, summitWithoutPredQueue);
            }

            temp = temp->next;
        }
        
        topologicalQueue = add_int(value, topologicalQueue);
        summitWithoutPredQueue = get_int(summitWithoutPredQueue); //Utiliser get pour retirer le noeud dans la file.
    }
    
    displayList(&topologicalQueue);
    
    if (topologicalQueue.size == graph->nbSom) {
        topologyIsPossible = true;
    }

    return topologyIsPossible;
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