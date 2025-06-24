#include <curses.h>
#include <stdio.h>

#define DEBUG

struct state {
	unsigned char MEMORY[0x1000];
	int PC;
	int A;
	int X;
	int Y;
	int ZERO;
	int address; //it's not state, but helps debugging
};

#define ADDRESSING_ABSOLUTE 1
#define ADDRESSING_ABSOLUTE_Y 2
#define ADDRESSING_ABSOLUTE_X 3
#define ADDRESSING_RELATIVE 4
#define ADDRESSING_IMMEDIATE 5

#define TARGET_REGISTER_A 1
#define TARGET_REGISTER_X 2
#define TARGET_REGISTER_Y 3

size_t getromfromfile(int argc, char** argv, unsigned char* mem) {
	FILE* rom_file;
	if (argc < 2) {
		printf("You have to give a filename\n");
		exit(1);
	}
	printf("Opening file %s\n", argv[1]);
	rom_file = fopen(argv[1], "rb");
	if (!rom_file) {
		printf("Could not open file %s\n", argv[1]);
		exit(2);
	}
	size_t rom_size = fread(mem,1,100,rom_file);
	if (rom_size <= 0) {
		printf("Could not read from file or file is empty\n");
		fclose(rom_file);
		exit(3);
	}
	fclose(rom_file);
  #ifdef DEBUG
  printf("MEMORY got %i bytes\n", (int)rom_size);
  for(int i=0; i<rom_size; i++) {
    printf("MEMORY[%i]: %02x\n", i, mem[i]);
  }
  #endif
	return rom_size;
}

void initScreen() {
	initscr();
	noecho();
}

void closeScreen() {
	endwin();
}

void printScreen(struct state *state, int isTheEnd) {
		erase();
		for(int i=0; i<20; i++) {
			if (state->MEMORY[0x100+i]) {
				mvaddch(0, i, state->MEMORY[0x100+i]);
			}
		}
		move(5,0);
		#ifdef DEBUG
		printw("A=%i,X=%i,Y=%i,PC=%i,addr=%04x,ZERO=%i,Memory=%02x %02x %02x"
			,state->A,state->X,state->Y,state->PC,state->address,state->ZERO
			,state->MEMORY[state->PC], state->MEMORY[state->PC+1]
			,state->MEMORY[state->PC+2]);
		if (isTheEnd) {
			printw(" --> End");
		}
		#endif
		refresh();
		getch();
}
