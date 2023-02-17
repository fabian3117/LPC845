/*
 * MRT.h
 *
 *  Created on: 14 dic. 2022
 *      Author: nahuu
 */

#ifndef MRT_MRT_H_
#define MRT_MRT_H_
#include "LPC845.h"
//-->	Prove interrupciones cada intervalos regulares	<--
#define ISER_MRT	(0x1<<10)
#define DefaultV		0xFFFFFF
#define MaxChanels		4
#if defined (__cplusplus)
	extern "C" {
	void MRT_IRQHandler ( void );
	}
#endif
class MRT {
public:
	enum Modo{
		Repeat=0x0,
		InterrupcionUnica=0x1,
		InterrupcionUnicaBloqueante=0x2
	};
	enum Canal{
		Chanel0=0,
		Chanel1,
		Chanel2,
		Chanel3
	};
	enum FlagInterrup{
		FChanel0=1,
		FChanel1=2,
		FChanel2=4,
		FChanel3=8
	};
	enum ERR{
		SinError=0
	};
	uint8_t Erro;
	void (*InterrAsociada)();	//-->	Vector a funcion asociada a la interrupcion	<---
	MRT(uint8_t Cana=Chanel0,uint8_t Modo=Repeat, void (*F)()=nullptr,bool Interrumpe=true,uint32_t Va=DefaultV);
	MRT(MRT&);
	void MRT_IRQHandler();
	virtual ~MRT();
	void SetValor(uint32_t Val){Valor=Val;};
	uint32_t GetValor(void){return Valor;};
	MRT& operator<<(void (*)());
	uint32_t GetValorActual(void){
		return 0;
	}

private:
	uint32_t Valor;
	uint8_t Canal;
};

#endif /* MRT_MRT_H_ */
