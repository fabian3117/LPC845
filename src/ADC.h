/*
 * ADC.h
 *
 *  Created on: 7 feb. 2023
 *      Author: nahuu
 */

#ifndef ADC_H_
#define ADC_H_
#include "LPC845.h"


class ADC {
public:
	ADC();
	enum {
		Modo_Sincronico=0,
		Modo_Asyncronico=1,
	}AsyncMode;
//static void	ADC_SEQA_IRQHandler();
	virtual ~ADC();
};

#endif /* ADC_H_ */
