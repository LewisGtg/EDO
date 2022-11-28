OBJETOS = edo.o sist.o utils.o
DEPENDENCIAS = -lm

all: main

main: $(OBJETOS) main.c
	gcc -Wall main.c $(OBJETOS) $(DEPENDENCIAS) -o main

# Arquivos objeto
edo.o: edo.c edo.h
	gcc -c -Wall edo.c

sist.o: sist.c sist.h
	gcc -c -Wall sist.c

utils.o: utils.c utils.h
	gcc -c -Wall utils.c

clean:
	rm -f *.o

purge: clean
	rm -f main