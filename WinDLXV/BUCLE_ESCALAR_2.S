;
; a) BUCLE_ESCALAR_2.S
;	1088 ciclos perdidos por dependencias RAW (17 en cada iteración del bucle)
; 	582 instrucciones (4 de 'inicio' + 64*9 de 'bucle' + 2 de 'fin')
;	1289 ciclos (CPI 2.215)
;
           .data
x:         .double 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9  ;Vector X
		   .double 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9
		   .double 3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9
		   .double 4.0, 4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9
		   .double 5.0, 5.1, 5.2, 5.3, 5.4, 5.5, 5.6, 5.7, 5.8, 5.9
		   .double 6.0, 6.1, 6.2, 6.3, 6.4, 6.5, 6.6, 6.7, 6.8, 6.9
		   .double 7.0, 7.1, 7.2, 7.3
y:         .double 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9	  ;Vector Y
		   .double 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9
		   .double 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9
		   .double 3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9
		   .double 4.0, 4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9
		   .double 5.0, 5.1, 5.2, 5.3, 5.4, 5.5, 5.6, 5.7, 5.8, 5.9
		   .double 6.0, 6.1, 6.2, 6.3
a:         .double 3.14    											  ;Escalar a

           .text
inicio:    ADDI R1,R0,x     ; R1 = X
           ADDI R2,R0,y     ; R2 = Y
           LD F0,a(R0)	    ; F0 = a
           ADDI R4,R1,496   ; R4 = Posición último elemento de X
bucle:     LD F2,0(R1)		; Carga en F2 el valor de M(0+R1) = X[i]
		   LD F4,8(R1)		; F4 = X[i+1]
		   MULTD F2,F0,F2	; Carga en F2 el producto a·X[i]
		   MULTD F4,F0,F4	; F4 = a·X[i+1]
		   LD F6,16(R1)		; F6 = X[i+2] 
		   ADDI R1,R1,24	; R1 += 24 Próximo elemento del vector X
		   MULTD F6,F0,F6	; F6 = a·X[i+2]
           LD F8,0(R2)		; Carga en F8 la posición en memoria de Y[i]
		   LD F10,8(R2)		; F10 = Y[i+1]
		   LD F12,16(R2)	; F12 = Y[i+2]
           ADDD F8,F2,F8	; F8 = a·X[i] + Y[i]
		   ADDD F10,F4,F10	; F10 = a·X[i+1] + Y[i+1]
		   ADDD F12,F6,F12	; F12 = a·X[i+2] + Y[i+2]
		   SGE R6,R1,R4		; Si R1 >= R4 el bucle puede haber finalizado -> R6 = 1. Si no, R6 = 0.
           SD 0(R2),F8		; Almacena en M(0+R2) el valor de Y[i] desde F8
		   SD 8(R2),F10		; M(8+R2) = Y[i+1]
		   SD 16(R2),F12	; M(16+R2) = Y[i+2]
           ADDI R2,R2,24	; R2 += 24 Próximo elemento del vector Y
           BEQZ R6,bucle	; Si R6 = 0 repetimos el bucle
		   NOP              ;
salida:	   SUB R6,R1,R4		; R6 = R1-R4
		   SGEI R8,R6,16	; Si R6 = 16 no quedan elementos por tratar, R8 = 1
		   BNEZ R8,fin		; Si R8 = 1 fin del bucle. 
		   NOP				;
		   LD F2,0(R1)		;
		   LD F8,0(R2)		;
		   MULTD F2,F0,F2	;
		   ADDD F8,F2,F8	;
		   SD 0(R2),F8		;
		   SGEI R8,R6,8		; Si R6 = 8, ya no quedan elementos por tratar. R8 = 1
		   BNEZ R8, fin		; Si R8 = 1, finaliza. Si R8 = 0 trata el último elemento y finaliza
		   NOP				;
		   LD F4,8(R1)		;
		   LD F10,8(R2)		;
		   MULTD F4,F0,F4	;
		   ADDD F10,F4,F10	;
		   SD 8(R2),F10		;
fin:       TRAP 6           ;
	   