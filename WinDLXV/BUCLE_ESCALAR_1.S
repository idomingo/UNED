;
; a) BUCLE_ESCALAR_1.S
;	1088 ciclos perdidos por dependencias RAW (17 en cada iteración del bucle)
; 	582 instrucciones (4 del main + 64*9 del bucle + 2 tras salida del bucle)
;	Total: 1289 ciclos (CPI 2.215)
;
           .data
x:         .double 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9   ;Vector X
		   .double 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9
		   .double 3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9
		   .double 4.0, 4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9
		   .double 5.0, 5.1, 5.2, 5.3, 5.4, 5.5, 5.6, 5.7, 5.8, 5.9
		   .double 6.0, 6.1, 6.2, 6.3, 6.4, 6.5, 6.6, 6.7, 6.8, 6.9
		   .double 7.0, 7.1, 7.2, 7.3
y:         .double 0.01, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9	  ;Vector Y
		   .double 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9
		   .double 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9
		   .double 3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9
		   .double 4.0, 4.1, 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9
		   .double 5.0, 5.1, 5.2, 5.3, 5.4, 5.5, 5.6, 5.7, 5.8, 5.9
		   .double 6.0, 6.1, 6.2, 6.3
a:         .double 3.14    											  ;Escalar a

           .text
main:      ADDI R1,R0,x     ; R1 = X[0]
           ADDI R2,R0,y     ; R2 = Y[0]
           LD F0,a(R0)	    ; F0 = a
           ADDI R4,R1,504   ; R4 = Posición último elemento de X
loop:      LD F2,0(R1)		; Carga en F2 la dirección en Memoria de X[i]
		   LD F4,0(R2)		; Carga en F4 la dirección en Memoria de Y[i]
           MULTD F2,F0,F2	; Guarda en F2 el producto a·X[i]
           SUB R5,R4,R1		; R5 = R4(#504) - R1(Posición elemento actual de X)
		   ADDI R1,R1,8		; R1 += 8 Próximo elemento del vector X
           ADDD F4,F2,F4	; F4 = a·X[i] + Y[i]
           SD 0(R2),F4		; Almacena en M(0+R2) el valor de Y[i] desde F4
		   ADDI R2,R2,8		; R2 += 8 Próximo elemento del vector Y
           BNEZ R5,loop		; Si R5 != 0 repetimos el bucle
           NOP              ;
salida:    TRAP 6           ;
	    
