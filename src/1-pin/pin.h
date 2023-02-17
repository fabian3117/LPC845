/*******************************************************************************************************************************//**
 *
 * @file		pin.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		22 jun. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef PIN_H_
#define PIN_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "tipos.h"

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
 *** IMPLANTACION DE LA CLASE
 **********************************************************************************************************************************/

class pin
{
	public:
		pin(){}

		virtual uint8_t SetPin( void )  = 0 ;
		virtual uint8_t ClrPin( void )  = 0 ;
		virtual uint8_t SetTogglePin( void )  = 0 ;
		virtual uint8_t SetDir( void )  = 0 ;
		virtual uint8_t SetToggleDir( void )  = 0 ;
		virtual uint8_t GetPin( void ) const = 0 ;
		virtual uint8_t SetPinMode( void ) = 0 ;
		virtual uint8_t SetPinResistor( void ) = 0 ;

		virtual ~pin(){}
};
#endif /* PIN_H_ */
