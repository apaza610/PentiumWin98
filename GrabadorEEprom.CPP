/****************************************************
Program: Read/Write to EEPROM using .HEX file using
			a PPI8255 and the parallel port
Conections: PPIportA used as DATAbus
			PPIportB used as ADDRESSbusHigh
			PPIportC used as ADDRESSbusLow
			ParallelPort used as CONTROLbus
Author:	Homar Orozco Apaza
	LaPaz - Bolivia
****************************************************/
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <dos.h>
#include <fstream.h>
#include <stdlib.h>

unsigned int portRdWr = 0x378;	// puertoParalelo pin1=/WE, pin0=/OE
unsigned int portAdrH = 0x301;	// puertoB es OUTPUT addressBusHIGH bits 0 a 7
unsigned int portAdrL = 0x302;	// puertoC es OUTPUT addressBusLOW bits 8 a 15
unsigned int portData = 0x300;	// puertoA es INPUT/OUTPUT data bus
unsigned int portCtrl = 0x303;	// control word que SETEA el PPI
						// 2^16 = 65536 = 16 * 4096 total de memoria del Z80
unsigned char registro[43];		// :10005000C36C00C3C507C3C807C3CB07C3CE07C360
						// :XXbyteCount cuantos DataBytes tiene
						//    XXXXmemAddr 16bit
						//        XXrecordType 00=data o 01=endOfFile
						//			XYXYXY..........datos.........XY
						//                                          XXchecksum
unsigned int memAddr, byteCount;	// 16bits
unsigned char celda[16];			// 8bits celda0,celda1,celda2......celdaD,celdaE,celdaF

void writeEEPROM(){		
	sscanf(registro,":%2X%4X%*2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X%2X",
							&byteCount,&memAddr,&celda[0],&celda[1],&celda[2],&celda[3],&celda[4],&celda[5],&celda[6],&celda[7],&celda[8],&celda[9],&celda[10],&celda[11],&celda[12],&celda[13],&celda[14],&celda[15]);
	printf("nroCells %02X startAddress %04X | %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n",
						byteCount,memAddr,celda[0],celda[1],celda[2],celda[3],celda[4],celda[5],celda[6],celda[7],celda[8],celda[9],celda[10],celda[11],celda[12],celda[13],celda[14],celda[15]);
		
	outportb(portCtrl, 0x80);	// PPI puertoA,B,C salidas
	for(int i=0; i<byteCount; i++){
		unsigned int tempAddr = memAddr + i;
		unsigned char addrH, addrL;
		
		addrH = (tempAddr >> 8) & 0x00FF;
		addrL = tempAddr & 0xFF;
		
		printf("%02X: %04X sera %02X\n", i,tempAddr,celda[i]);
		outportb(portAdrH, addrH);
		outportb(portAdrL, addrL);
		outportb(portData, celda[i]);
		
		outportb(portRdWr, 0x01);	// 0000 0010 pin1=/WE, pin0=/OE
		delay(10);
		outportb(portRdWr, 0x02);   // 0000 0001
		delay(5);
		outportb(portRdWr, 0x01);	// 0000 0010
		delay(10);
		//getch();
	}
}

void readEEPROM(){
	unsigned int addressInicio;		// 16bit value
	unsigned int cantidadCeldas;
	
	printf("addressInicio(Hexadecimal) y cantidadCeldas(Decimal) a leer? ");
	scanf("%X %d",&addressInicio, &cantidadCeldas);	
	
	outportb(portCtrl, 0x90);	// Setear PPI puertoA entrada, puertoB,C salidas
	outportb(portRdWr, 0x02);   // 0000 0010 pin1=/WE, pin0=/OE
	
	for(int i=addressInicio; i<(addressInicio+cantidadCeldas); i++){
		unsigned char addrH, addrL, valor;
		
		addrH = (i >> 8) & 0x00FF;
		addrL = i & 0xFF;
		
		outportb(portAdrH, addrH);
		outportb(portAdrL, addrL);
		valor = inportb(portData);
		
		printf("%02X%02X  contiene: %02X\n", addrH, addrL, valor);
		//getch();
		//delay(500);
	}
}

int main(){
	FILE *HEXfile;
	char opcion;
	
	clrscr();
	printf("Want to Write(y) o Read(n) the EPROM? ");
	scanf("%c", &opcion);
	
	if(opcion == 'y'){
		HEXfile = fopen("Programa.hex","r");	//C:\\apaza\\cpp\\
		if(HEXfile==NULL){
			printf("no encuentro el .HEX");
			return 1;
		}
		else{
			while(fscanf(HEXfile, "%s", registro) != EOF){
				writeEEPROM();
				//getch();
			}
			fclose(HEXfile);
		}
		printf("operacion finalizada...");
	}
	else{
		readEEPROM();
	}
	//getch();
	return 0;
}