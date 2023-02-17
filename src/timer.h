/*
 * timer.h
 *
 *  Created on: 6 jul. 2022
 *      Author: Marcelo
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <swhandler.h>
#include"tipos.h"

class timer: public swhandler
{
	private:
		volatile uint32_t 	m_TmrRun;
		volatile bool 		m_TmrEvent;
		volatile bool 		m_TmrStanBy;
		volatile uint8_t 	m_TmrBase;
		void 	(* m_TmrHandler)(void);

	public:
		enum base_t		{NO_MODIFICAR, DEC,SEG,MIN,HOR};
		enum ticks_t	{DECIMAS = 10 , SEGUNDOS = 100 , MINUTOS = 6000 , HORA = 360000};
		enum standby_t	{RUN,PAUSE};
		void SWhandler(void);
		timer& operator=( uint32_t t);
		bool operator!(void);
		timer();
		timer( void (*handler)()  , uint8_t base );
		void TimerRun ( uint32_t t , void (*)() = nullptr , uint8_t  = NO_MODIFICAR);
		void TimerEvent ( void );
		void TimerStop ( void );

		virtual ~timer();
};

#endif /* TIMER_H_ */
