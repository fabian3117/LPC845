/*
 * ADC.cpp
 *
 *  Created on: 7 feb. 2023
 *      Author: nahuu
 */

#include <ADC.h>
#if defined (__cplusplus)
	extern "C" {
	void ADC_SEQA_IRQHandler ( void );
	//((ADC*)InteADC)-
	//while(1){};
	//while(1){}
	}
#endif
	static void* InteADC;
ADC::ADC() {
	SYSCON->PDRUNCFG &= ~(1 << 4);				// Enciendo el modulo del ADC que esta apagado por default
	SYSCON->SYSAHBCLKCTRL0 |= (1 << 24);		// 24 = ADC

	//SWM0->PINENABLE0 &= ~(1 << 14);				// ADC_0 enabled on pin PIO0_7
	SWM0->PINENABLE0 &= ~(1 << 15);				// ADC_1 enabled on pin PIO0_6

	ADC0->CTRL 	= (1)							// CLKDIV se recomienda el minimo si no hay una necesidad de velocidad
				| (Modo_Sincronico << 8)						// ASYNCMODE
				| (0 << 10)						// LPWRMODE
				| (0 << 30);					// CALMODE

	// A/D Conversion Sequence A Control Register

	ADC0->SEQ_CTRL[0] 	= (0)					// CANAL, lo voy a seleccionar en el momento de disparar la conversion
						| (0 << 12)				// TRIGGER
						//	Input 	Source 					Description
						//	0 								- No hardware trigger.
						//	1 		PININT0_IRQ 			GPIO_INT interrupt 0.
						//	2 		PININT1_IRQ 			GPIO_INT interrupt 1.
						//	3 		SCT0_OUT3 				SCT output 3.
						//	4 		SCT0_OUT4 				SCT output 4.
						//	5 		T0_MAT3 				CTIMER match 3.
						//	6 		CMP0_OUT_ADC 			Analog comparator output.
						//	7 		GPIO_INT_BMAT 			GPIO_INT bmatch.
						//	8 		ARM_TXEV 				ARM core TXEV event.
						| (1 << 18)				// TRIGPOL					0=FLANCO NEGATIVO DE LOS TRIGGERS 1=FLANCO POSITIVO DE LOS TRIGGERS
						| (0 << 19)				// SYNCBYPASS
						| (0 << 26)				// START OF CONVERSION		1=SOC 0=STOP
						| (0 << 29)				// SINGLESTEP
						| (0 << 30)				// MODE						0
						| (1 << 31);			// SEQA_ENA					0=SECUENCIA A DESHABILITADA 1=HABILITADA

	ADC0->INTEN = (1 << 0);						// Sequence A interrupt enable

	NVIC->ISER[0] = (1 << 16); 					/* enable interrupt ISE_ADC_SEQA*/
InteADC=this;

}

ADC::~ADC() {
	// TODO Auto-generated destructor stub
}

