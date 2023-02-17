/*
 * RTC.h
 *
 *  Created on: 11 nov. 2022
 *      Author: nahuu
 */

#ifndef RTC_H_
#define RTC_H_
#include "LPC845.h"
#include "uart.h"

#define E_PedirHora			0
#define E_PedirMinutos		1
#define E_EsperandoHora		2
#define E_EsperandoMinutos	3
#define E_MinutosListos		4
#define E_SegundosListos	5
#define E_PedirSegundos		6
#define E_HoraLista			7
#define E_Nada 				8
#define Code_ERR_UART		'4'


#define ASCII_DEC(x)		(x-48);
#define Obtener_Hora(x,y)	((x*10)+(y))


class RTC {
public:
	RTC();
	//typedef void (RTC::*C)char*;
	//C punte;
	const uint8_t In_Hora=0;
	const uint8_t In_Minu=1;
	const uint8_t In_Sege=2;
	const uint8_t In_Anio=3;
	const uint8_t In_Todo=4;
	volatile uint8_t Estado=E_PedirMinutos;
	uint8_t bs[4];
	const char* Comandos[5]={"h","m","s","y","t"};	//-->	Comandos Para RTC	<--
	virtual ~RTC();
	uint32_t getAnio() const;
	//void (*EstadosRTC[])(void)={this->Nada()};
	void setAnio(uint32_t anio);
	uint8_t getDia() const;
	void setDia(uint8_t dia);
	uint8_t getHora() const;
	void setHora(uint8_t hora);
	uint8_t getMes() const;
	void setMes(uint8_t mes);
	uint8_t getMinutos() const;
	void setMinutos(uint8_t minutos);
	uint8_t getSegundos() const;
	void setSegundos(uint8_t segundos);
	void SetHora(uint8_t Hora,uint8_t Seg);
	void PedirHora();
	void PedirMinutos();
	void EsperandoHora();
	void EsperandoMinutos();
	void MinutosListos();
	void SegundosListos();
	void HoraLista();
	void PedirSegundos();
	void Nada();
	uart* uart1;

private:
	uint32_t Anio;
	uint8_t Mes;
	uint8_t Dia;

	uint8_t Hora;
	uint8_t Minutos;
	uint8_t Segundos;
	bool PM=false;
};

#endif /* RTC_H_ */
