CC  =gcc
main.out: Node.o BTree.o Experiment.o
	$(CC) Experiment.o BTree.o Node.o -o 06satish.out

Experiment.o: BTree.h Experiment.c
	$(CC) -c -w -ggdb Experiment.c	
	
BTree.o: Node.h BTree.h BTree.c
	$(CC) -c -w -ggdb BTree.c

Node.o: Node.h Node.c
	$(CC) -c -w -ggdb Node.c

clean:
	rm *.o *.out *~
