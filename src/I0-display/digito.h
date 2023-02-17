/*******************************************************************************************************************************//**
 *
 * @file		digito.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		17 ago. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef I0_DISPLAY_DIGITO_H_
#define I0_DISPLAY_DIGITO_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "LPC845.h"

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
// extern tipo nombreVariable;
/***********************************************************************************************************************************
 *** IMPLANTACION DE UNA CLASE
 **********************************************************************************************************************************/

class digito
{
	public:
		typedef enum {BCD,SEGMENTOS,ASCII} codigo_t;
		enum  modo {APAGADO = 0xff , FIJO = 0 ,PARPADEAR } ;

	private:
		uint8_t m_codigo;
		uint8_t m_valor;

	public:
		digito(codigo_t codigo = BCD , uint16_t valor = APAGADO): m_codigo ( codigo) , m_valor ( valor ){}
		bool set( uint16_t valor);
		uint8_t get( void);
		virtual ~digito();
};

#endif /* I0_DISPLAY_DIGITO_H_ */
