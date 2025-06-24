all: botiga

botiga: botiga.c
	gcc -o botiga botiga.c -lncurses

clean:
	rm -f botiga
.PHONY: clean
