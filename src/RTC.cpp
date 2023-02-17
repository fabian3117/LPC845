/*
 * RTC.cpp
 *
 *  Created on: 11 nov. 2022
 *      Author: nahuu
 */

#include <RTC.h>

RTC::RTC() {
	uart1 = new uart( 0 , 16 , 0 , 17 , USART1 , 9600 , uart::ocho_bits , uart::NoParidad , 64 , 64 );


}

uint32_t RTC::getAnio() const {
	return Anio;
}

void RTC::setAnio(uint32_t anio) {
	Anio = anio;
}

uint8_t RTC::getDia() const {
	return Dia;
}

void RTC::setDia(uint8_t dia) {
	Dia = dia;
}

uint8_t RTC::getHora() const {
	return Hora;
}

void RTC::setHora(uint8_t hora) {
	Hora = hora;
}

uint8_t RTC::getMes() const {
	return Mes;
}

void RTC::setMes(uint8_t mes) {
	Mes = mes;
}

uint8_t RTC::getMinutos() const {
	return Minutos;
}

void RTC::setMinutos(uint8_t minutos) {
	Minutos = minutos;
}

uint8_t RTC::getSegundos() const {
	return Segundos;
}

void RTC::setSegundos(uint8_t segundos) {
	Segundos = segundos;
}
void RTC::Nada(void){

};
void RTC::PedirHora(void){
		uart1->Transmit(Comandos[In_Hora]);
		Estado=E_EsperandoHora;
	}
void RTC::EsperandoHora(void){
		Estado=(uart1->Buffer()[0]!=Code_ERR_UART)?E_HoraLista:E_EsperandoHora;
	//uart1->extrarRx(buf);
	}
void RTC::HoraLista(void){
		for(int i=0;i<4;i++){
			bs[i]=ASCII_DEC(uart1->Buffer()[i])
//			bs[i]=(uart1->Buffer()[i]-48);
		}
		static uint8_t Hora[5];	//-->	No funciona aun	<--
		static uint8_t val=uart1->UltimoValorRx();
		for(int i=0;i<4;i++){
		//	uart1->extrarRx(&Hora[i]);
		}
		static uint8_t HS[5];
		uart1->extrarRx(HS);
		uart1->extrarRx(Hora);
		setHora(Obtener_Hora(bs[0],bs[1]));
		setMinutos(Obtener_Hora(bs[2],bs[3]));
		Estado=E_PedirHora;
	}
void RTC::PedirMinutos(void){
		uart1->Transmit(Comandos[In_Minu]);
		Estado=E_EsperandoMinutos;
	}
void RTC::EsperandoMinutos(void){
		Estado=(uart1->Buffer()[0]!='4')?E_MinutosListos:E_EsperandoMinutos;
	}
void RTC::MinutosListos(void){
	//static uint8_t val=uart1->UltimoValorRx();
	static uint8_t* Minutos[2];
	uart1->ExtraerRx(Minutos[0],2);
//		uint8_t Min=(UltimoValorRx()-'0')*10+(uart1->Buffer()[1]-'0');
	//	Manejo->setMinutos(Min);
		Estado=E_Nada;
	}
void RTC::SegundosListos(){

}
void RTC::PedirSegundos(){

}


RTC::~RTC() {
	// TODO Auto-generated destructor stub
}

