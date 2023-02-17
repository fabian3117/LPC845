/*
 * I2CBufferTrans.h
 *
 *  Created on: 8 dic. 2022
 *      Author: nahuu
 */

#ifndef I2C_I2CBUFFERTRANS_H_
#define I2C_I2CBUFFERTRANS_H_

//-->	Esta clase hace de buffer para las transmisiones del I2C	<--
#include "LPC845.h"
//-->	Puede Hacerse haciendo uso de Estructura pero como este lenguaje tiene objetos	<--
//-->	Podria hacer uso de vector pero al hacer de buffer esto mejor lo controlo de la forma clasica	<--
#define ModeRead	1
#define ModeWrite	0

using namespace std;
class I2C_BufferTrans {

public:

	I2C_BufferTrans();
	virtual ~I2C_BufferTrans();

	uint8_t Modo;       	  				//-->	READ = 1 - WRITE = 0
	uint8_t Direccion;    	  				//-->	DEVICE ADDRESS
	uint8_t regAddr;      	  				//-->	REGISTER ADDRESS
	uint8_t *Dato;      	  				//-->	POINTER TO DATA
	uint8_t Tamanio;       	  				//-->	SIZE OF DATA IN BYTES
	uint8_t IndexDato; 		  				//-->	DATA INDEX(INTERNAL)
	int8_t  EstadoTrans;      				//-->	TRANSMIT STATE(INTERNAL)
	void* (I2C_BufferTrans::*done)(void);	//-->	Funcion a ejecutar al finalizar
};

#endif /* I2C_I2CBUFFERTRANS_H_ */
