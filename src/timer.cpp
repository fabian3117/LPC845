/*
 * timer.cpp
 *
 *  Created on: 6 jul. 2022
 *      Author: Marcelo
 */

#include "timer.h"

timer::timer() {
	// TODO Auto-generated constructor stub
	m_TmrRun = 0;
	m_TmrEvent = false;
	m_TmrStanBy = RUN ;
	m_TmrBase = DEC;
	m_TmrHandler = nullptr ;
	g_swhandler.push_back(this);

}
timer::timer(void (*handler)() , uint8_t base )
{
	// TODO Auto-generated constructor stub
	m_TmrRun = 0;
	m_TmrEvent = false;
	m_TmrStanBy = RUN ;
	m_TmrBase = base;
	m_TmrHandler = handler;
	g_swhandler.push_back(this);

}

timer::~timer() {
	// TODO Auto-generated destructor stub
}

void timer::SWhandler(void)
{
	if ( m_TmrStanBy == RUN )
	{
		if ( m_TmrRun )
		{
			m_TmrRun--;
			if (!m_TmrRun )
				m_TmrEvent = true;
		}
	}
}
timer& timer::operator=( uint32_t t)
{
	m_TmrRun = t * DECIMAS;
	m_TmrEvent = false;
	return *this;
}
bool timer::operator!(void)
{
	if ( m_TmrRun )
	{
		m_TmrEvent = false;
		return true;
	}
	return false;
}

void timer::TimerRun ( uint32_t t , void (*handler)() , uint8_t base)
{
	if ( base != NO_MODIFICAR)
		m_TmrBase = base ;

	switch ( m_TmrBase )
	{
		case DEC:
			t *= DECIMAS ;
			break;
		case SEG:
			t *= SEGUNDOS ;
			break;
		case MIN:
			t *= MINUTOS ;
			break;
		case HOR:
			t *= HORA;
			break;
	}

	if ( handler )
		m_TmrHandler = handler ;
	m_TmrRun = t;
}
void timer::TimerEvent ( void )
{
	if ( m_TmrEvent )
	{
		m_TmrEvent = false;
		m_TmrHandler();
	}
}
void timer::TimerStop ( void )
{
	m_TmrRun = 0;
	m_TmrEvent = false;
	m_TmrStanBy = RUN ;
}
