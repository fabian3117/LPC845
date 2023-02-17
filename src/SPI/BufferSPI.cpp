/*
 * BufferSPI.cpp
 *
 *  Created on: 15 dic. 2022
 *      Author: nahuu
 */

#include <SPI/BufferSPI.h>

BufferSPI::BufferSPI(uint8_t Tam) {
	TamanioDatos=Tam;
	//BufferRx.fill(-1);
	//BufferTx.fill(-1);
}

BufferSPI::~BufferSPI() {}
uint32_t BufferSPI::GetValorRx(){
	//-->	Retorna el ultimo valor del buffer y lo elimina	<--

uint32_t Last= BufferRx.back();
BufferRx.pop_back();

return Last;
}
void BufferSPI::SetValorRx(uint32_t Val){
		BufferRx[BufferRx.size()]=Val;
}
uint32_t BufferSPI::GetValorTx(){

	//-->	Retorna el ultimo valor del buffer y lo elimina	<--

uint32_t Last= BufferTx.back();
BufferTx.pop_back();

return Last;

}


void BufferSPI::SetValorTx(uint32_t Val){
		BufferTx[BufferTx.size()]=Val;
}
