/*
 * PinDescrip.h
 *
 *  Created on: 17 nov. 2022
 *      Author: nahuu
 */

#ifndef PINDESCRIP_H_
#define PINDESCRIP_H_
#include <LPC845.h>
#define PinDefault  0
#define PortDefault 0
class PinDescrip {
public:
	PinDescrip(uint8_t Pi=PinDefault,uint8_t Port=PortDefault);
	uint8_t Pin;
	uint8_t Puerto;
	uint8_t PinRegist(){
		//-->	Me retorna directamente el valor para poner en los registros	<--
		return(Pin+31*Puerto);
	}
	virtual ~PinDescrip();
};

#endif /* PINDESCRIP_H_ */
