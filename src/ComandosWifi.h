#ifndef COMANDOSWIFI_H_
#define COMANDOSWIFI_H_
#include "LPC845.h"
uint8_t cosa;
class ComandosWifi {
public:
	ComandosWifi();
	const char* Comandos[5]={"#RTh","#RTm","#RTs","#RTy","#RTt"};	//-->	Comandos Para RTC	<--
	virtual ~ComandosWifi();
};

#endif /* COMANDOSWIFI_H_ */
