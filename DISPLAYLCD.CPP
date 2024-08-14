/****************************************************
Program: Example of controlling LCD 1602 using PPI8255
Conections: PPIportA --- data of LCD
			PPIportC pin7 --- RS of LCD
			PPIportC pin6 --- E of LCD
Author:	Homar Orozco Apaza
	LaPaz - Bolivia
****************************************************/
#include <stdio.h>
#include <dos.h>
#include <conio.h>

int puertoA = 0x300;	// DATAbus
int puertoC = 0x302;	// CTRLbus
int puertoS	= 0x303;	// puerto de configuracion PPI
//char modoDato[]  = "10000000";

unsigned int bin2dec(char cadena[8]){		// binario to decimal conversor
	unsigned int valor = 0;
	int pesos[] = {128,64,32,16,8,4,2,1};
	for(int i=0; i<8; i++){
   	if(cadena[i] == '1')
      	valor += pesos[i];
   }
   return valor;
}

void pulsoE(unsigned int modo){
	outportb(puertoC, modo);
	outportb(puertoC, bin2dec("01000000")|modo);
	delay(10);
	outportb(puertoC, modo);
}
void LCDcomando(char cadena[8]){
	outportb(puertoA, bin2dec(cadena));	// Comando configurar a 8 bits
	pulsoE(0x00);
}
void LCDcaractr(char cadena[8]){
	outportb(puertoA, bin2dec(cadena));	// Comando configurar a 8 bits
	pulsoE(0x80);
}

void main(){
	clrscr();
 	outportb(puertoS, 0x80);	// Configurar PPI puertosA,B,C salidas

	//configurar el LCD
	LCDcomando("00110000");			// Comando configurar a 8 bits
	LCDcomando("00111000");			// Comando activar las 2 filas
	LCDcomando("00001110");			// Comando mostrar cursor
	LCDcomando("00001111");			// Comando mostrar cursor parpadeante
	
	//escribir al LCD
	outportb(puertoA, 0x4E);	// Escribir N en hexa
	pulsoE(0x80);
	LCDcaractr("01101111");		// Escribir o binario
  	outportb(puertoA, 'm');		// Escribir m en ASCII
	pulsoE(0x80);
	outportb(puertoA, bin2dec("01100010"));	// b
	pulsoE(0x80);
	LCDcaractr("01110010");		// Escribir r binario
	LCDcaractr("01100101");		// Escribir e binario
	
	LCDcomando("11000000");			// Comando moverCursorAbajo
	
	char tecla;
	printf("Press keys to send to LCD (ESC to exit)\n");
	while(1){
		tecla = getch();
		if(tecla == 27)			// ASCII for ESC key
			break;
		outportb(puertoA, tecla);	// Escribir tecla recibida
		pulsoE(0x80);
	}
}