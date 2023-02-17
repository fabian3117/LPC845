#include <cr_section_macros.h>
#include "inicializar.h"
#include "ejemplo.h"
#include "RTC.h"
#include "string.h"
#include "SPI/SPI.h"
#include "LPC845.h"
#include "I2C/I2C.h"
#include "Letras/Letras.h"
#include "MRT/MRT.h"
#include "ADC.h"

#if defined (__cplusplus)
	extern "C" {
	void PININT0_IRQHandler ( void );
	}
#endif
void PININT0_IRQHandler(){
	while(1);

}
//-->	Funcion utilizada como ejemplo para MRT<..

//void CambioPin(void){}

/*
 * -->	Pines para utilizar de ejemplo luego	<--
PinDescrip* Clock=new PinDescrip(18,0);
PinDescrip* MOSI=new PinDescrip(19,0);
PinDescrip* MISO=new PinDescrip(20,0);
PinDescrip* SEL0=new PinDescrip(21,0);
 *
 */
int main(void)
{
	inicializar();
	//inicializarEjemplo();



	//-->	Ejemplo instanciacion controlador de ADC	<--

	//ADC* pruebaAD=new ADC();

	//-->	Ejemplo de instanciacion del controlador UART con una transmision de un string	<--

	//uart* uart_1 = new uart( 0 , 16 , 0 , 17 , USART1 , 9600 , uart::ocho_bits , uart::NoParidad , 64 , 64 );
	//uart_1->Transmit("HOLA");

	//-->	Ejemplo de instanciacion de controlador de I2C	<--

	//I2C* PruebaI2C0=new I2C(I2C::I2C_0,Clock,MOSI,false);

	//-->	Ejemplo de instanciacion del MRT con una asignacion de una funcion	<--

	//MRT *MRT_Test=new MRT(MRT::Chanel0,MRT::Repeat,nullptr,UnSegundo);
	//(*MRT_Test)<<CambioPin;

	//-->	Ejemplo de instanciacion del controlador SPI <--

	//SPI* Probando=new SPI(0,Clock,MOSI,MISO,SEL0,SPI::Maestro,false);


	while (1){

}

    return 0 ;
}

