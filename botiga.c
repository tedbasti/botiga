#include <stdlib.h>
#include "botiga.h"

unsigned int getAddress(unsigned char addressing,
	const struct state* state) {
	unsigned char ll = state->MEMORY[state->PC];
	unsigned char hh = state->MEMORY[state->PC+1];
	switch(addressing) {
		case ADDRESSING_IMMEDIATE:
			return state->PC;
		case ADDRESSING_ABSOLUTE:
			return ll | hh<<8;
		case ADDRESSING_ABSOLUTE_Y:
			return getAddress(ADDRESSING_ABSOLUTE,state) + state->Y;
		case ADDRESSING_ABSOLUTE_X:
			return getAddress(ADDRESSING_ABSOLUTE,state) + state->X;
		case ADDRESSING_RELATIVE:
			unsigned int address = ll;
			if (address <= 0x7f) {
				return state->PC + address;
			} else {
				return state->PC - (0xff - address + 1);
			}
		default:
			//Should not happen;
			return 0;
	}
}

void load(unsigned char reg,
	unsigned char addressing, struct state* state) {
	state->address = getAddress(addressing, state);
	unsigned char value = state->MEMORY[getAddress(addressing,state)];
	if(addressing == ADDRESSING_IMMEDIATE) { state->PC = state->PC + 1; }
	else { state->PC = state->PC + 2; }
	state->ZERO = (value == 0);
	switch (reg) {
		case TARGET_REGISTER_A:
			state->A = value;
			break;
		case TARGET_REGISTER_Y:
			state->Y = value;
			break;
		case TARGET_REGISTER_X:
			state->X = value;
			break;
	}
}

void store(unsigned char reg,
	unsigned char addressing, struct state* state) {
	unsigned char value = 0;
	switch (reg) {
		case TARGET_REGISTER_A:
			value = state->A;
			break;
		case TARGET_REGISTER_Y:
			value =	state->Y;
			break;
		case TARGET_REGISTER_X:
			value = state->X;
			break;
	}
	state->ZERO = (value == 0);
	state->address = getAddress(addressing, state);
	state->MEMORY[state->address] = value;
	state->PC = state->PC + 2;
}

void inc(unsigned char reg, struct state* state) {
	switch(reg) {
		case TARGET_REGISTER_A:
			state->A++;
			state->ZERO = (state->A == 0);
			break;
		case TARGET_REGISTER_X:
			state->X++;
			state->ZERO = (state->X == 0);
			break;
		case TARGET_REGISTER_Y:
			state->Y++;
			state->ZERO = (state->Y == 0);
			break;
	}
}

int main(int argc, char** argv) {
	//Initialize the state of the "computer"
	struct state state = {{0},0,0,0,0,0,0};
	//Read the rom to memory
	size_t rom_size = getromfromfile(argc,argv,state.MEMORY);
	//initialize ncurses with initScreen
	initScreen();
	//Go over the whole ROM read from the file
	while(state.PC <= rom_size) {
		printScreen(&state, 0);
		state.address=0;
		unsigned char command = state.MEMORY[state.PC];
		state.PC++;
		//Check the program counter binary code
		switch (command) {
			case 0xa0:  //ldy #0 (immediate)
				load(TARGET_REGISTER_Y,ADDRESSING_IMMEDIATE,&state);
				break;
			case 0xb9:	//lda addr,y
				load(TARGET_REGISTER_A,ADDRESSING_ABSOLUTE_Y,&state);
				break;
			case 0x60: //rts currently just aborts the program!
				state.PC = rom_size+1;
				break;
			case 0x99: //sta addr,y
				store(TARGET_REGISTER_A,ADDRESSING_ABSOLUTE_Y,&state);
				break;
			case 0xF0: //beq
				if (state.ZERO) {
					state.address = getAddress(ADDRESSING_RELATIVE,&state);
					state.PC = state.address;
				}
				state.PC+=1;
				break;
			case 0xd0: //bne
				if (!state.ZERO) {
					state.address = getAddress(ADDRESSING_RELATIVE,&state);
					state.PC = state.address;
				}
				state.PC+=1;
				break;
			case 0xC8: //iny
				inc(TARGET_REGISTER_Y,&state);
				break;
			case 0x20: //jsr (TODO:return address to stack)
				state.address = getAddress(ADDRESSING_ABSOLUTE,&state);
				state.PC = state.address;
				break;
			default:
				exit(5);
		}
	}
	printScreen(&state, 1);
	closeScreen();
	return 0;
}
