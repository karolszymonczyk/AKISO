    opt f-g-h+l+o+

    ;f - wypelnia miejsce w pamieci pomiędzy $FF /255
    ;g - Atari 5200 mode
    ;h - generuje pliki wykonawcze Atari
    ;l - zapisuje 
    ;0 - nadpisuje do plikow

  	;org - zmienia wartosc oryginalnego countera
    org $1000

start   equ *

    	lda <text
    	;przetrzymuje wartosc rejestru w lokacji 80
    	sta $80
    	lda >text
    	sta $81
    	ldy #1
    	;laduje wartosc a5 = 165, 10100101 binarnie
    	lda #$a5
    	jsr phex

    	lda <text
    	ldx >text
    	jsr $ff80
    	brk

;kod z wykladu do konwersji do postaci szesnastkowej
PHEX 	PHA
     	JSR PXDIG
     	PLA
     	LSR @
     	LSR @
     	LSR @
     	LSR @
PXDIG   AND #%00001111
    	ORA #'0'
    	CMP #'9'+1
    	BCC PR
    	ADC #'A'-'9'-2
PR      STA ($80),Y
    	DEY
    	RTS

byte    dta b(0)

    	org $2000
text    equ *
    	dta b(0),b(0)
    	; 10 - znak nowej linii
    	dta b(10)
    	dta a(0)


    	org $2E0
    	dta a(start)


    	end of file