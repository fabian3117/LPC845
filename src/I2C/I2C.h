#ifndef I2C_I2C_H_
#define I2C_I2C_H_
#include "LPC845.h"
#include "PinDescrip.h"
#include "I2CBufferTrans.h"

#define I2C_CLKSEL					5	//-->	Base	<--
#define I2C_MainClock				0x1
#define ISER_I2C0				(0x1<<8)
#define ISER_I2C1				(0x1<<7)
#define ISER_I2C2				(0x1<<21)
#define ISER_I2C3				(0x1<<22)
#define I2C0_TRANSMIT_BUFFER_SIZE	1
#define I2C_Disponible_Listo(x)	((x) & (0x0F)) != 0x01)
#define I2C_MST_Start(x)		(x)=(0x1<<1);
#define I2C_MST_Continue(x)		(x)=(0x1<<0);
#define I2C_Pendiente(x)		(x)&(0x1<<0)
#define I2C_TransmisionOK(x)	((x)&(0x7<<1))==(0x02<<1)
#define I2C_Stop(x)				(x)=(0x1<<2);
#define I2C_CargaDir(x,y)		(x)=((y)<<1)|0;
#define I2C_DisponibleListo(x)	((x)&(0x0F))!=0x01
#define I2C_Interrupciones(x)	(x)=(0x1<<0)|(0x1<<24)|(0x1<<25);
#define I2C_InterrupcionesA(x)	(x) = (1<<0) | (1<<24) | (1<<25);
#define I2C_DatosRecibidos(x)	(((x) & (0x07<<1))==(0x01<<1))
#define BUSY						-3	//-->	Ocupado	<--
#define ERROR_NACK_ADDR 			-2
#define ERROR_NACK					-1
#define	ERROR						-4
#define OK							 0
//#define ResetI
//#define ResetII
#if defined (__cplusplus)
	extern "C" {
	void I2C0_IRQHandler ( void );
	}
#endif
#if defined (__cplusplus)
	extern "C" {
	void I2C1_IRQHandler ( void );
	}
#endif
#if defined (__cplusplus)
	extern "C" {
	void I2C2_IRQHandler ( void );
	}
#endif
#if defined (__cplusplus)
	extern "C" {
	void I2C3_IRQHandler( void );
	}
#endif

using namespace std;
//-->	Vector interrupciones	<--
//static void* Inter_I2C[4];
class I2C {
public:
	//-->	Tiene 2 Lineas	<--
	//-->	SDA - SCL		<--
	I2C(uint8_t NI2C=I2C_0,PinDescrip *SDA=new PinDescrip(),PinDescrip *SCL=new PinDescrip(),bool TestMode=false);
	virtual ~I2C();
	void I2C_IRQHandler(void);
	I2C_BufferTrans* I2C0_Transmit[I2C0_TRANSMIT_BUFFER_SIZE];
	uint32_t 	in_index;
	uint32_t 	out_index;
	void Buffer_Push(I2C_BufferTrans&);
	uint8_t Buffer_Pop(I2C_BufferTrans&);
	int8_t I2C0_MasterWriteBlocking(uint8_t address, uint8_t regAddr, uint8_t *data,uint8_t size);	//-->	Escribe de forma bloqueante	<--
	int8_t I2C0_MasterReadBlocking(uint8_t address, uint8_t regAddr, uint8_t *data, uint8_t size);	//-->	Leo de forma bloqueante		<--
	int8_t I2C0_MasterWrite(uint8_t address, uint8_t regAddr, uint8_t *data,uint8_t size,void (*done)(void)=nullptr);//-->	Maestro Escribe de forma no bloqueante	<--
	int8_t I2C0_MasterRead(uint8_t address, uint8_t regAddr, uint8_t *data, uint8_t size,void (*done)(void));

	I2C_Type* Base;
	enum I2C_N{
		I2C_0=0x0,
		I2C_1=0x1,
		I2C_2=0x2,
		I2C_3=0x3,
		I2C_4=0x4
	};
	enum ModoDir{
		Escritura=0,
		Lectura=1
	};
	enum EstadoTransfer{
		Completa=0,
		Pendiente=1
	};
	enum Modo{
		Maestro=0x1,
		Esclavo=0x2
	};


};

#endif /* I2C_I2C_H_ */
