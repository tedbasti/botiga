# Botiga

## What is Botiga
Botiga is the worst emulator that you will ever see and it is only for learning purposes.
It uses the 6502 processor - currently only 9 commands implemented - and there are only 20 bytes of vram (starting from #$100).
When you compile it as is, you will get debug output within line number 5 and it will stop after every command.

## Examples
Within the examples folder you got a hello world within assembler (hello_asm), which is the main driver for the development and uses most of the commands implemented.
Furthermore you got a hello world within c (hello_c), where I just wanted to test, how to call the hello world assembler program from within c.

## Compile
### Compile botiga
Install gcc, make and ncurses via `apt install build-essential libncurses-dev` on debian based systems.
Afterwards you are able to execute  `make` to build botiga.

### Compile examples
If you want to build an example, switch to the folder and execute `make`, but you need to have cc65 (`apt install cc65` on debian based systems) installed.

## Execute botiga
When you want to execute botiga, just type `.\botiga <ROMFILE>`.
