hello: hello.o crt0.o
	ld65 -C ../../botiga.cfg -o hello hello.o crt0.o

crt0.o: crt0.s
	ca65 --cpu 6502 crt0.s

hello.s: hello.c
	cc65 hello.c -t none --cpu 6502

hello.o: hello.s
	ca65 hello.s --cpu 6502


.PHONY: clean
clean:
	rm -f hello.o hello.s hello crt0.o

