# Botiga

## What is Botiga
Botiga is the worst emulator that you will ever see and it is only for learning purposes.
It uses the 6502 processor - currently only 9 commands implemented - and there are only 20 bytes of vram (starting from #$100).
When you compile it as is, you will get debug output within line number 5 and it will stop after every command.

## Examples
Within the examples folder you got a hello world within assembler (hello_asm), which is the main driver for the development and uses most of the commands implemented.
Furthermore you got a hello world within c (hello_c), where I just wanted to test, how to call the hello world assembler program from within c.

## Dependencies
Botiga only got ncurses as dependencies, because it got no sound at all and runs in terminal only.
