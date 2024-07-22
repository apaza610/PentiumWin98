'Enciende 1 led cada segundo usando el puerto paralelo (DB25)
'Setea los puertos A,B,C del PPI8255 como salidas
' por donde enciende 1 led cada segundo

DIM n AS INTEGER
n = 1
OUT &H303, &H80         'portA, B, C como salidas

DO
	PRINT "---", n, "---"
	FOR i = 0 TO 7
		OUT &H378, 2 ^ i		' port paralelo DB25
		OUT &H300, 2 ^ i		' portA
		OUT &H301, 2 ^ i
		OUT &H302, 2 ^ i
		PRINT "led ... ", i
		SLEEP 1
	NEXT
	n = n + 1
LOOP UNTIL n = 10
END

