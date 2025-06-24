.import   _main
.export   __STARTUP__ : absolute = 1        ; Mark as startup
.export   _hello
.import   __RAM_START__, __RAM_SIZE__       ; Linker generated

.segment "STARTUP"
JSR _main

.segment "CODE"
_hello:
  ldy #0                  ;y=0
  beq in                  ;jump to in
  loop:
    sta $100,y    ;at $100 begins the screenbuffer
    iny                   ;y++
  in:
    lda hello,y   ;a=hello+y
    bne loop              ;if(hello+y!=0) {goto loop}
    rts                   ;return/quit
  hello: .byte "Hello World!"
         .byte 13,10,0
