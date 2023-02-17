/*******************************************************************************************************************************//**
 *
 * @file		tipos.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		22 jun. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef TIPOS_H_
#define TIPOS_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define  __I      	volatile const  /*Defines 'read only' permission */
#define  __O    	volatile             /*Defines 'write only' permission */
#define  __IO   	volatile             /*Defines 'read / write' permission */

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/
typedef		unsigned char 		uint8_t;
typedef		char 				int8_t;
typedef		short unsigned int 	uint16_t;
typedef		short int 			int16_t;
typedef		unsigned int 		uint32_t;
typedef		int 				int32_t;
/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
// extern tipo nombreVariable;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/

#endif /* TIPOS_H_ */