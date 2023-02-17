/*
 * BufferSPI.h
 *
 *  Created on: 15 dic. 2022
 *      Author: nahuu
 */

#ifndef SPI_BUFFERSPI_H_
#define SPI_BUFFERSPI_H_
#include "LPC845.h"
#include "array"
#include "vector"
#define TipoDefault	uint32_t
#define MaxValores		10
using namespace std;

class BufferSPI {
public:
	enum Tamanios{
		Bits_1=0,
		Bits_2,
		Bits_3,
		Bits_4,
		Bits_5,
		Bits_6,
		Bits_7,
		Bits_8,
		Bits_9,
		Bits_10,
		Bits_11,
		Bits_12,
		Bits_13,
		Bits_14,
		Bits_15,
		Bits_16
	};
	BufferSPI(uint8_t Tam=Bits_8);
	uint8_t TamanioDatos;
	uint32_t GetValorRx();
	void SetValorRx(uint32_t v);
	uint32_t GetValorTx();
	void SetValorTx(uint32_t v);
	bool VacioRx(){
		return BufferRx.empty();
	}
	bool VacioTx(){
			return BufferTx.empty();
		}


	virtual ~BufferSPI();

private:
	std::vector<uint32_t> BufferRx;
	std::vector<uint32_t> BufferTx;
};

#endif /* SPI_BUFFERSPI_H_ */
