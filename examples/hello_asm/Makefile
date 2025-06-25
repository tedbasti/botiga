all: hello

hello: hello.s
	ca65 hello.s -o hello.o --cpu 6502
	ld65 hello.o -o hello -C ../botiga.cfg

clean:
	rm -f hello.o hello
.PHONY: clean
