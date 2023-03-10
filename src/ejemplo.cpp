/*******************************************************************************************************************************//**
 *
 * @file		ejemplo.cpp
 * @brief		Descripcion del modulo
 * @date		13 jul. 2022
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "ejemplo.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
gpio *LedRojo;

timer *t_ledRojo_on , *t_ledRojo_off;
timers g_maquina;

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** IMPLEMENTACION DE LOS METODODS DE LA CLASE
 **********************************************************************************************************************************/
void inicializarEjemplo ( void )
{
	LedRojo = new gpio ( gpio::port1 , 2 , gpio::pushpull , gpio::output , gpio::low);
	t_ledRojo_on = new timer ( Ev_t_ledRojo_on , timer::DEC );
	t_ledRojo_off = new timer ( Ev_t_ledRojo_off , timer::SEG );

	LedRojo->SetDir();

	g_maquina << t_ledRojo_on << t_ledRojo_off;
}

void Ev_t_ledRojo_on ( void )
{
	//apago el led
	LedRojo->ClrPin();
	// disparo tiempo de ofF
	t_ledRojo_off->TimerRun(3);
}

void Ev_t_ledRojo_off ( void )
{
	//prender el led
	LedRojo->SetPin();
	// disparo tiempo de on
	t_ledRojo_on->TimerRun(5);

}
