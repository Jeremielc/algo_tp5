all : L_ADJ queue main
	gcc L_ADJ.o queue.o main.o -std=c99 -Wall -o output
	rm -rf *.o
	./output graphe_alea.txt > trace.txt
	nano trace.txt

L_ADJ : sources/L_ADJ.c
	gcc -c sources/L_ADJ.c -std=c99 -Wall

queue : sources/queue.c
	gcc -c sources/queue.c -std=c99 -Wall

main : sources/main.c
	gcc -c sources/main.c -std=c99 -Wall

genere_graph : sources/genere_graphe_0.c
	gcc sources/genere_graphe_0.c -std=c99 -Wall -o genere_graph

