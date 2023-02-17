/*
 * SPI.h
 *
 *  Created on: 17 nov. 2022
 *      Author: nahuu
 */

#ifndef SPI_H_
#define SPI_H_
#include <LPC845.h>
#define FuenteClockSPI0	9
#define FuenteClockSPI1	10
//#define ClockS
#include "PinDescrip.h"
#include "BufferSPI.h"
#define IDL_Alto	(0x1<<5)
//-->	Fuente de clock de SPI	<--
//#define SPI0CLKSEL	((uint32_t *)(uint32_t)0x400480B4)
//#define SPI1CLKSEL	((uint32_t *)0x400480B8)
#define SPI0CLKSEL		9
#define SPI1CLKSEL		10
#define SPI_FRO			0x0
#define SPI_MainClock	0x1	//-->	Segun el ejemeplo le dan este	<--
#define SPI_FRG0		0x2
#define SPI_FRG1		0x3
#define FRO_2			0x4
#define SPI_None		0x7	//-->	Este es el default	<--	

#define SPI_8Bits		0x8
#define MaxSelect 				3
#define LimpiaRecepcion		(0x1<<2)
#define MascaraDatos		(0xFFFF)
#define MascaraEsclavoRx	(0xF<<16)
#define LimpiaBufferListo	(0x1<<3)
#if defined (__cplusplus)
	extern "C" {
	void SPI0_IRQHandler ( void );
	}
#endif
#if defined (__cplusplus)
	extern "C" {
	void SPI1_IRQHandler ( void );
	}
#endif
#define MascaraDatosExtrae	(0xFFFF)
#define MaxEsclavos				3
#define SinEsclavo			   -1
#define ForzarFinTransmision(x) (x)|=(0x1<<7);
#define DatosLeer(x)		(x)&(0x1)
#define DatosEscr(x)		(x)&(0x1<<1)
#define EsclavoSEL(x)		(x)&(0x1<<4)
#define LimpEscSEL(x)		(x)&=~(0x1<<4);
#define F_Esclavo			(x)
#define SelectEsclavo(x,y)	(x)|=(y);
#define MascaraFinTransmicion	(0x1<<7)
#define FinTransmicion(x)	(x)|=(MascaraFinTransmicion);
#define LimpiaEsclavos(x)	(x)&=~(0xF);
class SPI {
public:
	enum {
		NSPI0=0,
		NSPI1=1
	}NSPI;
	enum{
		TxS0=0x1,
		TxS1=0x2,
		TxS2=0x4,
		TxS3=0x8,
	}TXSelect;
	enum{
		SS0=0x0,
		SS1=0x1,
		SS2=0x2,
		SS3=0x3
	}Selecter;
	enum{
		Len1Bits=0x1,
		Len2Bits,
		Len3Bits,
		Len4Bits,
		Len5Bits,
		Len6Bits,
		Len7Bits,
		Len8Bits,
		Len9Bits,
		Len10Bits,
		Len11Bits,
		Len12Bits,
		Len13Bits,
		Len14Bits,
		Len15Bits,
	}LenData;
	enum {
		Esclavo=0x0,
		Maestro=0x1
	}Modo;
	SPI(uint32_t N_SPI,PinDescrip *Cloc,PinDescrip *MOS,PinDescrip *MIS,PinDescrip *SELECT0,uint8_t Mod=Maestro,bool TestMode=false,uint8_t TamanioTrama=SPI_8Bits);
	virtual ~SPI();
	BufferSPI Buffer[MaxSelect];
	PinDescrip *SELECT[MaxSelect];
	PinDescrip *Clock,*MOSI,*MISO;
	uint8_t EsclavosActivos;	//-->	Para saber cuantos esclavos tengo activos	<--
	uint8_t EsclavoActivo;		//-->	Para saber a que esclavo Tengo que enviarle los datos	<--

	void EnviaDato(uint8_t Dato,uint8_t Sel=SS0,bool EnviaCorta=false);
	bool Err=false;
	void CargaBufferRx(uint8_t Dato,uint8_t N_Esclavo=SS0);
	//-->	Deberia tener asignado con una matriz a cada Esclavo el buffer a enviar	<--
	//-->	En una segunda implementacion lo hago	<--
	uint8_t *BufferRx[MaxEsclavos];
	uint32_t *NBufRX[MaxEsclavos];
	uint32_t *NBufTx[MaxEsclavos];
	SPI_Type * Base;
	uint8_t *BufferTx[MaxEsclavos];
	uint8_t InRxIn[MaxEsclavos];
	static uint8_t Miram;
	const uint8_t T_MaxRx=15;
	const uint8_t T_MaxTx=15;
	uint8_t InRxOut[MaxEsclavos];
	uint8_t InTxIn[MaxEsclavos];
	uint8_t InTxOut[MaxEsclavos];
	uint8_t TamDat=SPI_8Bits;
	uint8_t DatosEnvio(){
		for(uint8_t i=0;i<MaxSelect;i++){
			if(!Buffer[i].VacioTx()){
				return i;
			}
		}
	};
	SPI& operator<<(uint32_t);
	void SPI_IRQHandler();
};

#endif /* SPI_H_ */
