ldy #0 			;y=0
beq in 			;jump to in 
loop:
  sta $100,y	;at $100 begins the screenbuffer
  iny			;y++
in:
  lda hello,y	;a=hello+y
  bne loop		;if(hello+y!=0) {goto loop}
  rts			;return/quit
hello: .byte "Hello World!",0
