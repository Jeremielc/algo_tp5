all : L_ADJ queue
	gcc L_ADJ.o queue.o -std=c99 -Wall -o output
	rm -rf *.o
	./output graphe_alea.txt > trace.txt
	nano trace.txt

L_ADJ : sources/L_ADJ.c
	gcc -c sources/L_ADJ.c -std=c99 -Wall

queue : sources/queue.c
	gcc -c sources/queue.c -std=c99 -Wall
