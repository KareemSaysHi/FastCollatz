all: main subcollatz

clobber: clean
	rm -f *~ \#*\# 

clean: 
	rm -f file*
	rm -f finalfile
	rm -f *.o

# Dependency rules for file targets
main: main.o
	gcc main.o -o main

subcollatz: subcollatz.o
	gcc subcollatz.o -o subcollatz

main.o: main.c
	gcc -c main.c 

subcollatz.o: subcollatz.c
	gcc -c subcollatz.c
