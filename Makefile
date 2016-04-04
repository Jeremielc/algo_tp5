all : L_ADJ perso_queue queue main 
	gcc L_ADJ.o perso_queue.o queue.o main.o -std=c99 -Wall -o output
	rm -rf *.o
	
L_ADJ : sources/L_ADJ.c
	gcc -c sources/L_ADJ.c -std=c99 -Wall

queue : sources/queue.c
	gcc -c sources/queue.c -std=c99 -Wall

perso_queue : sources/perso_queue.c
	gcc -c sources/perso_queue.c -std=c99 -Wall

main : sources/main.c
	gcc -c  sources/main.c -std=c99 -Wall

genere_graph : sources/genere_graphe_0.c
	gcc sources/genere_graphe_0.c -std=c99 -Wall -o genere_graph

zip : 
	zip -r TP5_Marquage_Topographique_Jeremie_Leclerc_Pierrick_Hue.zip sources/ genere_graph output graph_*.txt trace.txt Makefile
	
