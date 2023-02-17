/*
 * swhandler.h
 *
 *  Created on: 6 jul. 2022
 *      Author: Marcelo
 */

#ifndef SWHANDLER_H_
#define SWHANDLER_H_

#include <list>
using namespace std;


class swhandler {
	public:
		swhandler();
		virtual void SWhandler(void) = 0 ;
		virtual ~swhandler();
};

extern list <swhandler *> g_swhandler;

#endif /* SWHANDLER_H_ */
