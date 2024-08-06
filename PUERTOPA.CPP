#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <dos.h>

int main(){
	int puerto = 0x378;

	unsigned char dato;
	dato = inportb(0x3F8);	//leer puerto serial

	printf("leido: %d\n", dato);
	outportb(puerto, 0x66);	//write puerto paralelo
	getch();
	return 0;
}