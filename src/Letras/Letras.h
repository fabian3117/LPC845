#ifndef LETRAS_H_
#define LETRAS_H_

//-->

#include "Gpio/gpio.h"
#include "timers.h"
#include "timer.h"

#define MAX_Leds 			8
#define Max_Estados			3
#define Apaga(x)		(x)->ClrPin();
#define Prende(x)		(x)->SetPin();
//uint8_t CAracter[]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA};
//-->	Tengo que adaptar esto como una maquina de estado	<--

class Letras {
public:
	enum Estados{
		MOSTRANDO,
		ACTUALIZANDO,
		APAGADO
	};
	Estados I_Estado;
	void (Letras::*M_Estad[Max_Estados])(void);
	void Mostrando();
	void Actualizando(){};
	void Maquina(){
		controler->TimerEvent();
		(this->*M_Estad[I_Estado])();
	};
	//-->	El truco esta en cambiar cada Ts el valor que tiene que mostrar	<--
	//void Apagar();
	timer* controler;
	timers* M_Timer;
	gpio* Leds[MAX_Leds];
	uint8_t Indice;
	Letras(uint8_t =0);
	void Prender();
	void Cambio0();
	timer *secuenciaLeds,*secuenciaIncremento;
	void Apagar();
	uint8_t ValorMostrar;
	bool Muestra;
	void Prender(uint8_t Valor);
	const uint8_t Character[16]={0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xA,0xB,0xC,0xD,0xE,0xF};
	void IncrementaValor();
	};

#endif /* LETRAS_H_ */
