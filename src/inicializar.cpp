#include "inicializar.h"

void inicializar (void)
{
	Inicializar_PLL( );
	//SYSCON->SYSAHBCLKCTRL0 |= (1 << 7);								// 7 = SWM
	//SYSCON->SYSAHBCLKCTRL0 |= (1 << 6) | (1 << 20) | (1 << 18);		// 6 = GPIO0	20 = GPIO1	18 = IOCON
	systick_Inicializar(1);
}
