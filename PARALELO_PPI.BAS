OUT &H303, &H90         ' Configurar PPI8255 asi: &H90 portA entrada, B, C salidas
ENTRADAS = INP(&H300)   ' Leyendo el puerto A
PRINT "Lectura PortA dec:", ENTRADAS, "...hex:", HEX$(ENTRADAS)

DIM n AS INTEGER
n = 0
DO
	PRINT "---", n, "---"
	FOR i = 0 TO 7
		OUT &H378, 2 ^ i       ' Salida por puerto paralelo DB25
		'OUT &H300, 2 ^ i	' Salida por  PortA del PPI8255
		OUT &H301, 2 ^ i	' Salida por  PortB del PPI8255
		OUT &H302, 2 ^ i	' Salida por  PortC del PPI8255
		PRINT "led ... ", i
		SLEEP 1
	NEXT
	n = n + 1
LOOP UNTIL n = 2
END