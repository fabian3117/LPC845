/*******************************************************************************************************************************//**
 *
 * @file		uart.h
 * @brief		Driver de comunicacion UART
 * @date		5 oct. 2022
 * @author		Gonzalez Federico
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef I1_USART_UART_H_
#define I1_USART_UART_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include <ComunicacionAsincronica.h>
#include "LPC845.h"
#include "string.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLANTACION DE UNA CLASE
 **********************************************************************************************************************************/

//--->	Para poder utilizar las interrupciones del sistema	<--
#if defined (__cplusplus)
	extern "C" {
	void UART0_IRQHandler ( void );
	}
#endif
#if defined (__cplusplus)
	extern "C" {
	void UART1_IRQHandler ( void );
	}
#endif
#if defined (__cplusplus)
	extern "C" {
	void UART2_IRQHandler ( void );
	}
#endif
#if defined (__cplusplus)
	extern "C" {
	void UART3_IRQHandler ( void );
	}
#endif
#if defined (__cplusplus)
	extern "C" {
	void UART4_IRQHandler ( void );
	}
#endif

class uart : public ComunicacionAsincronica
{
	private:
		USART_Type * m_usart;
		uint8_t 	*m_bufferRX;
		uint32_t	m_inxRxIn , m_inxRxOut , m_maxRx;
		uint8_t 	*m_bufferTX;
		uint32_t	m_inxTxIn , m_inxTxOut , m_maxTx;
		bool m_flagTx;
	public:
		typedef enum  { NoParidad , par = 2, impar} paridad_t;
		typedef enum  { siete_bits , ocho_bits } bits_de_datos;
		~uart();
		uart( uint8_t portTx , uint8_t pinTx , uint8_t portRx , uint8_t pinRx ,
				USART_Type * usart,uint32_t baudrate, bits_de_datos BitsDeDatos, paridad_t paridad ,
				uint32_t maxRx , uint32_t maxTx);

		void Transmit ( const char * msg) ;
		void Transmit ( void * msg , uint32_t n );
		void* Message ( void * msg , uint32_t n );
		void UART_IRQHandler (void);
		char* Extraer(uint8_t* Donde,uint8_t Cuanto){
			const uint8_t* Copia=m_bufferRX;
					uint8_t Buf[Cuanto];
					for(int i=0;i<Cuanto&&(m_inxRxIn != m_inxRxOut );i++){
									Buf[i] = Copia[ m_inxRxOut ] ;
									m_inxRxOut ++;
									//m_inxRxOut %= m_maxRx;
					}
					uint8_t** p=&Donde;
					p[0]=Buf;


						return (char*)Copia;
				}
		uint8_t* Buffer(){

			return m_bufferRX;
		}
		uint8_t CantRx(){
			return m_inxRxIn;
		}
		void ExtraerRx(uint8_t* Buf,uint8_t Cantidad){

			//-->	Tengo que cargar en el buffer la cantidad de datos que tenga en el buffer resepcion	<---
			for(int i=0;i<Cantidad&&( m_inxRxIn != m_inxRxOut);i++){

				Buf[i] = m_bufferRX[ m_inxRxOut ] ;
				m_inxRxOut ++;
				m_inxRxOut %= m_maxRx;

			}
		}
		char** ExtraerRxx(char** Buf,uint8_t Cantidad){
			 static char** p =Buf;
			char Buff[Cantidad];
					//-->	Tengo que cargar en el buffer la cantidad de datos que tenga en el buffer resepcion	<---
					for(int i=0;i<Cantidad&&( m_inxRxIn != m_inxRxOut);i++){
						Buff[i] = m_bufferRX[ m_inxRxOut ] ;
						m_inxRxOut ++;
						m_inxRxOut %= m_maxRx;
					}

					p[0]=Buff;
return p;
				}
		uint8_t UltimoValorRx(){
			//m_bufferRX="";
			uint8_t buf=m_bufferRX[m_inxRxOut];
			m_inxRxOut+=1;
			m_inxRxOut %= m_maxRx;
			//m_inxRxIn-=1;
			return buf;
		}
		bool FinBufer(){
			return (m_inxRxIn == m_inxRxOut)?true:false;
		}
		uint8_t extrarRx (uint8_t * dato ){
			//-->	Tengo que pasar un buffer que tenga ese tamaño	<--
			if ( m_inxRxIn != m_inxRxOut )
				{
					*dato = m_bufferRX[ m_inxRxOut ] ;
					m_inxRxOut ++;
					m_inxRxOut %= m_maxRx;
					return 1;
				}
				return 0;
		};

private:
		void pushRx ( uint8_t dato ) ;
		uint8_t popRx (uint8_t * dato ) ;
		void pushTx ( uint8_t dato ) ;
		uint8_t popTx (uint8_t * dato ) ;
		void EnableInterupt (  void );
		void DisableInterupt (  void );

};

#endif /* I1_USART_UART_H_ */
