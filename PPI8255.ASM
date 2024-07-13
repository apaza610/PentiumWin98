;**********************************************************************
; Using the ISA expanssion slot we can communicate with PPI-8255 mapped to Addresses
; 0300h portA,     0301h portB,     0302 portC,        and 0303 CtrlWord
;**********************************************************************
codigo     	segment
Programa	proc	far
			mov  	dx, 0303h		; Enviar palabra de control
			mov  	al, 10010000b	; PortA = entrada;  PortB = PortCH = PortCL = salidas
			out  	dx, al
			
			mov		dx, 0300h		; Leyendo el PuertoA
			in		al, dx

			mov		dx, 0301h		; Escribe al puertoB
			out		dx, al
			mov		dx, 0302h		; Escribe al puertoC
			out		dx, al
		
			mov		ax,4C00h		; Terminacion del programa
			int		21h				; Llamada al DOS
Programa	endp			
;------------------------------------------------------;    
codigo     	ends
			end		Programa