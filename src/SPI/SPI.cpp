/*
 * SPI.cpp
 *
 *  Created on: 17 nov. 2022
 *      Author: nahuu
 */
#include "SPI/SPI.h"
static void* Inte[2];
//-->	Fallos - Requiero tener todos los Pines como parametros <--
SPI::SPI(uint32_t N_SPI,PinDescrip *Clock,PinDescrip *MOSI,PinDescrip *MISO,PinDescrip *SELECT0,uint8_t Mod,bool TestMode,uint8_t TamanioTrama) {
	SYSCON->PRESETCTRL0&=~(0x1<<(11+N_SPI));
		SYSCON->PRESETCTRL0|=(0x1<<(11+N_SPI));
	SYSCON->SYSAHBCLKCTRL0|=(0x1<<7);	//-->	SWM	<--

	SYSCON->SYSAHBCLKCTRL0|=(0x1<<(11+N_SPI));

	//-->	Linea Reset	<--
	//-->	Seteo del divisor	<--
	uint32_t tmp;
	uint32_t baudrate_Bps=500000;
	uint32_t srcClock_Hz=FREQ_PRINCIPAL;
	tmp = (srcClock_Hz / baudrate_Bps) - 1U;
	switch(N_SPI){
	case NSPI0:
		SYSCON->FCLKSEL[SPI0CLKSEL]=SPI_MainClock;
	//	SWM0->PINENABLE0|=(0x1<<21)|(0x1<<20)|(0x1<<);
		SWM0->PINASSIGN.PINASSIGN3&=~((0xFF)<<24);	//-->	Limpio los bits que me interesan	<--
		SWM0->PINASSIGN.PINASSIGN3|=(Clock->PinRegist()<<24);
		//-->	CORREGIR	<--
		//-->	NO ESTOY HACIENDO LA ASIGNACION DE LOS DEMAS SELECT	<--
		SWM0->PINASSIGN.PINASSIGN4=(MOSI->PinRegist()|MISO->PinRegist()<<8|SELECT0->PinRegist()<<16|SELECT0->PinRegist()<<24);
		//SPI0->DIV&= ~(0xFFFFU);	//-->	Limpio el valor del divisor	<--
		//SPI0->DIV|=(tmp & 0xFFFFU);	//-->	Aplico la and para evitar tocar los bits reservados Por eso mismo aplico una Or	<--
		//-->	Configuracion de funcionamiento del modulo	<--
	//	SPI0->CFG|=(Mod<<2)|IDL_Alto|(TestMode<<7);
		SPI0->CFG=(0x1)|(Mod<<2)|(TestMode<<7);
		SPI0->TXCTL=(0x1<<16)|(Len8Bits<<24);
		//SPI0->TXDATCTL|=(TamanioTrama<<24);	//--> Establesco Tamaño de datos por trama	<--
		//SPI0->CFG|=(0x1);	//-->	En el codigo ejemplo lo setean y luego activan asi que probare eso	<--
		//NVIC->ISER[0] = ( 1 << 0 );	//-->	Habilita Interrupcion	<---
//		SPI0->INTENSET=(0x1|(0x1<<1));	//-->	Habilito interrupciones en Tx y Rx	<---
		//SPI0->INTENSET=(0x1|(0x1<<1)|(0x1<<4));	//-->	Habilito interrupciones en Tx y Rx	<---
		Inte[0]=(void*)this;
		Base=SPI0;
		break;
	case NSPI1:
		SWM0->PINASSIGN.PINASSIGN5&=~((0xFFFF)<<16);	//-->	Limpio los bits que me interesan	<--
		SWM0->PINASSIGN.PINASSIGN5|=((Clock->Pin+31*Clock->Puerto)<<16)|((MOSI->Pin+31*MOSI->Puerto)<<24);		//-->	Hoja 137	<--
		SWM0->PINASSIGN.PINASSIGN6&=~(0xFFFFFF);
		SWM0->PINASSIGN.PINASSIGN6|=(MISO->Pin+31*MISO->Puerto)|((SELECT0->Pin+31*SELECT0->Puerto)<<8);
		SPI1->DIV&= ~(0xFFFFU);	//-->	Limpio el valor del divisor	<--
		SPI1->DIV|=(tmp & 0xFFFFU);	//-->	Aplico la and para evitar tocar los bits reservados Por eso mismo aplico una Or	<--
				//-->	Configuracion de funcionamiento del modulo	<--
		SPI1->CFG|=(Mod<<2)|IDL_Alto|(TestMode<<7);
		SPI1->TXDATCTL|=(SPI_8Bits<<24);	//--> Establesco Tamaño de datos por trama	<--
		SPI1->CFG|=(0x1);	//-->	En el codigo ejemplo lo setean y luego activan asi que probare eso	<--
		NVIC->ISER[0] = ( 1 <<1);	//-->	Habilita Interrupcion	<---
		SPI1->INTENSET=(0x1|(0x1<<1));	//-->	Habilito interrupciones en Tx y Rx	<---
		Inte[1]=(void*)this;
		Base=SPI1;
		break;
	default:
		Err=true;
		break;
	}
	//-->	Ahora configuro las variables de clase que interesan para la transferencia	<--
//	for(uint8_t i=0;i<MaxEsclavos;i++){
	//	InRxIn[i]=InRxOut[i]=0;
		//InTxIn[i]=InTxOut[i]=0;
	//}
	SYSCON->SYSAHBCLKCTRL0&=~(0x1<<7);	//-->	SWM	Desconecta	<--
	EsclavoActivo=SinEsclavo;	//-->	Indico que no tenemos esclavos activos	<--
//-->	Funciones para luego implementar	<--
	//(void)memset(BufferRx, 0, sizeof(BufferRx));
	//(void)memset(BufferTx, 0, sizeof(BufferTx));


}
void SPI::EnviaDato(uint8_t Dato,uint8_t Sel,bool EnviaCorta){
//	BufferTx[0][InTxIn[0]]=Dato;
	//InTxIn[0]++;
	//InTxIn[0]%=T_MaxTx;
	ForzarFinTransmision(Base->STAT);	//-->	Para limpieza	<--
	Base->TXDATCTL|=(Dato)|(0x1<<(Sel+16))|(EnviaCorta<<20);
	//-->	Por ahora Voy a poner codigo bloqueante para esperar a que se envie los datos	<--

	//while(!(Base->STAT&(0x1<<8)));	//-->	Espero de forma bloqueante el modo reset del buffer SPI	<--

}

SPI::~SPI() {
	// TODO Auto-generated destructor stub
}
void SPI::CargaBufferRx(uint8_t Da,uint8_t Esclav){
		Buffer[Esclav].SetValorRx(Da);

		BufferTx[Esclav][InTxIn[Esclav]]=Da;
		InTxIn[Esclav]++;
		InTxIn[Esclav]%=T_MaxTx;
		EsclavoActivo=Esclav;
}
SPI& SPI::operator<<(uint32_t dat){
	CargaBufferRx(dat, EsclavoActivo);
	return *this;
}


void SPI::SPI_IRQHandler(){
	uint32_t Temp=Base->STAT;
	//-->	La interrupcion vino por Datos Listos para leer	<--
	if(DatosLeer(Temp)){
		uint32_t Datos=(Base->RXDAT&MascaraDatos);			//-->	Saco los datos que me interesan	<--
		uint8_t Esclavo=(Base->RXDAT&MascaraEsclavoRx);		//-->	Que esclavo es?	<--
		Base->STAT|=LimpiaRecepcion;						//-->	Limpio los datos recividos	<--
		NBufRX[0][InRxIn[0]]=Datos;	//-->	CORREGIR	<--
		InRxIn[0]++;
		InRxIn[0]%=T_MaxRx;}
	//-->	Podemos escribir en el buffer para envios	<--
	else if(DatosEscr(Temp)){
		//-->	Podemos escribir datos para enviar	<--
		Base->TXDAT=NBufTx[0][InTxOut[0]];	//-->	CORREGIR	<--
		InTxOut[0]++;
		InTxOut[0]&=T_MaxTx;
}
else if(EsclavoSEL(Base->STAT) || (Base->STAT&(0x1<<5))){
	//-->	Interrupcion por esclavo seleccionado	<--
	//-->	Requiere Limpieza por sofware	<--
			Base->STAT|=(0x3<<4);	//-->	Limpio esto	<--
}
}

void SPI0_IRQHandler(){
	if(Inte[0]!=nullptr){
	((SPI*)Inte[0])->SPI_IRQHandler();
	}
}
void SPI1_IRQHandler(){
	if(Inte[1]!=nullptr){
	((SPI*)Inte[1])->SPI_IRQHandler();
	}
}
