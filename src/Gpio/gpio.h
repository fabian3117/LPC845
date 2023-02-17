/*******************************************************************************************************************************//**
 *
 * @file		gpio.h
 * @brief		Objeto que contiene todo el manejo de gpio
 * @date		31/12/2022
 * @author		Ing. Marcelo Trujillo - Gonzalez Federico
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "pin.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
#define Base_InterrNVIC 24
#define Interrup0	Base_InterrNVIC
#define Interrup1	(Interrup0+0x1)
#define Interrup2	(Interrup1+0x1)
#define Interrup3	(Interrup2+0x1)
#define Interrup4	(Interrup3+0x1)
#define Interrup5	(Interrup4+0x1)
#define Interrup6	(Interrup5+0x1)
#define Interrup7	(Interrup6+0x1)
#define MODO_Detector_Nivel	0x1
#define Habilita_Interr	0x1
/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
class gpio : public pin
{
	protected:
		const uint8_t m_puerto;
		const uint8_t m_bit;
		const uint8_t m_modo;
			  uint8_t m_direccion;
		const uint8_t m_actividad;

		  uint8_t m_error;

	public:
		enum	error_t		{ error = 2 , ok };
		enum	power_t		{ off , on };
		enum	port_t		{ port0 , port1 };
		enum	direction_t	{ input , output };
		enum	activity_t	{ low , high };
		enum	nbits_t		{ max_bits_port0 = 31 , max_bits_port1 = 9 };
		enum	modo_t		{ inactive , pulldown , pullup , repeater };
		enum	resistor_t	{ pushpull , opencolector };
		//enum Interrupciones	{}
		static uint8_t CantdadInterrup;
		gpio ( uint8_t puerto , uint8_t bit , uint8_t modo , uint8_t direccion , uint8_t actividad ,bool Interrupciones=false);
		uint8_t SetPin( void );
		uint8_t ClrPin( void ) ;
		uint8_t SetTogglePin( void );
		uint8_t SetDir( void ) ;
		uint8_t SetToggleDir( void )  ;
		uint8_t GetPin( void ) const ;
		uint8_t SetPinMode( void ) ;
		uint8_t SetPinResistor( void )  ;
};
#endif /* GPIO_H_ */
