/*******************************************************************************************************************************//**
 *
 * @file		I4511.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		17 ago. 2022
 * @author		Gonzalez Federico
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef I0_DISPLAY_I4511_H_
#define I0_DISPLAY_I4511_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "Gpio/gpio.h"
#include "LPC845.h"
#include "segmentos.h"
#include <vector>
using namespace std;

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

class I4511 : public segmentos
{
	const vector <gpio* > &m_pinesI4511;

	public:
		I4511(const vector <gpio* > &pinesI4511):m_pinesI4511(pinesI4511){}
		void SetSegmentos ( uint16_t valor ) ;
		void Inicializar ( void ) ;

		virtual ~I4511();
};

#endif /* I0_DISPLAY_I4511_H_ */
