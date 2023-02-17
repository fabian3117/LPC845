#include <MRT/MRT.h>
static void* InterrupMRT[MaxChanels];
MRT::MRT(uint8_t Cana,uint8_t Modo,void (*F)(),bool Interrumpe,uint32_t Va) {
SYSCON->SYSAHBCLKCTRL0|=(0x1<<10);
//-->	Faltaria linea Reset	<--
//-->	Conexion a NVIC 10	<--
NVIC->ISER[0]|=ISER_MRT;
MRT0->CHANNEL[Cana].INTVAL=(0x1<<31);	//-->	Detiene inmediatamente el reloj	<--
//-->	Esta linea podria dar fallos	<---
MRT0->CHANNEL[Cana].INTVAL=(Va)|(0x1<<31);	//-->	Cargo el valor	<--

MRT0->CHANNEL[Cana].CTRL=(0x1)|(Modo<<1);
InterrupMRT[Cana]=(void*)this;
InterrAsociada=F;
Valor=Va;
Erro=SinError;

}

MRT::~MRT() {
	// TODO Auto-generated destructor stub
}
void MRT_IRQHandler(){
	uint8_t CanalInterrumpe=(((MRT0->IRQ_FLAG)&(0xF))>>1);	//-->	Limpio los bits que reservados -  Divido /2 Para tener el canal	<--
	MRT0->IRQ_FLAG|=(0xF);									//-->	Limpio esa interrupcion	<--

	if(InterrupMRT[CanalInterrumpe]!=nullptr){
			//-->	Tengo que hacerlo asi para poder manejar las interrupciones de los canales sin perderme	<--
			((MRT*)InterrupMRT[CanalInterrumpe])->MRT_IRQHandler();
			};
	return;
}
void MRT0_DriverIRQHandler(){
	//-->	Si bien tiene multiples Canales utilizan todas la misma interrupcion	<--
	//-->	Asi que lo mejor es guardar en el objeto una referencia a que canal es	<--
	//-->	Verifico que canal interrumpe	<--
	/*uint8_t CanalInterrumpe=(((MRT0->IRQ_FLAG)&(0xF))>>1);	//-->	Limpio los bits que reservados -  Divido /2 Para tener el canal	<--
	MRT0->IRQ_FLAG|=(0xF);	//-->	Limpio esa interrupcion	<--
	if(InterrupMRT[CanalInterrumpe]!=nullptr){
		//-->	Tengo que hacerlo asi para poder manejar las interrupciones de los canales sin perderme	<--
		((MRT*)InterrupMRT[CanalInterrumpe])->MRT_IRQHandler();
		}*/
}
MRT& MRT::operator <<(void (*F)()){
	this->InterrAsociada=F;
	return *this;
}
void MRT::MRT_IRQHandler(void){

if(InterrAsociada!=nullptr){
	InterrAsociada();
}
}
