/*
 * I2C.cpp
 *
 *  Created on: 3 dic. 2022
 *      Author: nahuu
 */
#include <I2C/I2C.h>
static void* InterI2C[4];
I2C::I2C(uint8_t NI2C,PinDescrip *SDA,PinDescrip *SCL,bool TestMode) {
	//-->	Habilito	<--

	SYSCON->SYSAHBCLKCTRL0|=(0x1<<7);	//-->	SWM	<--
	SYSCON->SYSAHBCLKCTRL0|=(0x1<<((NI2C==I2C_0)?5:21+NI2C));
	SYSCON->FCLKSEL[I2C_CLKSEL+NI2C]=I2C_MainClock;
	SYSCON->FCLKSEL[5] = 0x01;					//SELECT I2C0 CLOCK (MAIN = 0x01)
	//-->	Asigno Pines	<--
switch(NI2C){

case I2C_0:
	SYSCON->PRESETCTRL0&=~(0x1<<5);
	SYSCON->PRESETCTRL0|=(0x1<<5);
	SWM0->PINENABLE0&=~(0x3<<12);
	I2C0->CLKDIV = 11;							//I2C CLOCK DIVIDER  (original 11) PK
	I2C0->MSTTIME = (0x01<<0) | (0x00<<4);		//SLCLOW | SCLHIGH
	//I2C0->CLKDIV=0x1;	//-->	Divisor por 2	<--
	I2C0->CFG=(Maestro)|(TestMode<<2);
	I2C0->INTENCLR = (1<<0);					//DISABLE MASTER PENDING INTERRUPT
	NVIC->ISER[0]|=ISER_I2C0;
	//I2C0->INTENSET=(0x1)|(0x1<<4)|(0x1<<8)|(0x1<<16)|(0x1<<17);
	Base=I2C0;
	InterI2C[0]=(void*)this;
	break;

case I2C_1:
	SYSCON->PRESETCTRL0&=~(0x1<<21);
	SYSCON->PRESETCTRL0|=(0x1<<21);

	SWM0->PINASSIGN.PINASSIGN9&=~(0xFFFF<<16);	//-->	Limpio los bits de mi registro	<--
	SWM0->PINASSIGN.PINASSIGN9|=(SDA->PinRegist()<<16)|(SCL->PinRegist()<<24);	//-->	Asi los escribo sin pisar los demas bits	<--
	//I2C1->CLKDIV=0x1;	//-->	Divisor por 2	<--
	I2C1->CLKDIV = 11;							//I2C CLOCK DIVIDER  (original 11) PK
	I2C1->MSTTIME = (0x01<<0) | (0x00<<4);		//SLCLOW | SCLHIGH
	I2C1->INTENCLR = (1<<0);					//DISABLE MASTER PENDING INTERRUPT
	NVIC->ISER[0]|=ISER_I2C1;
	I2C1->INTENSET=(0x1)|(0x1<<4)|(0x1<<8)|(0x1<<16)|(0x1<<17);
	Base=I2C1;
	InterI2C[1]=(void*)this;
	break;

case I2C_2:
	SYSCON->PRESETCTRL0&=~(0x1<<22);
	SYSCON->PRESETCTRL0|=(0x1<<22);

	SWM0->PINASSIGN.PINASSIGN10&=~(0xFFFF);	//-->	Limpio los bits de mi registro	<--
	SWM0->PINASSIGN.PINASSIGN10|=(SDA->PinRegist())|(SCL->PinRegist()<<8);	//-->	Asi los escribo sin pisar los demas bits	<--
	//I2C2->CLKDIV=0x1;	//-->	Divisor por 2	<--
	I2C2->CLKDIV = 11;							//I2C CLOCK DIVIDER  (original 11) PK
	I2C2->MSTTIME = (0x01<<0) | (0x00<<4);		//SLCLOW | SCLHIGH
	I2C2->CFG=(Maestro)|(TestMode<<2);
	I2C2->INTENCLR = (1<<0);					//DISABLE MASTER PENDING INTERRUPT
	NVIC->ISER[0]|=ISER_I2C2;
	I2C2->INTENSET=(0x1)|(0x1<<4)|(0x1<<8)|(0x1<<16)|(0x1<<17);
	Base=I2C2;
	InterI2C[2]=(void*)this;
	break;

case I2C_3:
	SYSCON->PRESETCTRL0&=~(0x1<<23);
	SYSCON->PRESETCTRL0|=(0x1<<23);

	SWM0->PINASSIGN.PINASSIGN10&=~(0xFFFF<<16);	//-->	Limpio los bits de mi registro	<--
	SWM0->PINASSIGN.PINASSIGN10|=(SDA->PinRegist()<<16)|(SCL->PinRegist()<<24);	//-->	Asi los escribo sin pisar los demas bits	<--
	I2C3->CLKDIV = 11;							//I2C CLOCK DIVIDER  (original 11) PK
	I2C3->MSTTIME = (0x01<<0) | (0x00<<4);		//SLCLOW | SCLHIGH
	I2C3->CFG=(Maestro)|(TestMode<<2);
	I2C3->INTENCLR = (1<<0);					//DISABLE MASTER PENDING INTERRUPT
	NVIC->ISER[0]|=ISER_I2C3;
	I2C3->INTENSET=(0x1)|(0x1<<4)|(0x1<<8)|(0x1<<16)|(0x1<<17);
	Base=I2C3;
	InterI2C[3]=(void*)this;
	break;
}
	//-->	Habilito Interrupcioens	<--
InterI2C[NI2C]=(void*)this;
for(int i=0;i<I2C0_TRANSMIT_BUFFER_SIZE;i++){
	I2C0_Transmit[i]=new I2C_BufferTrans();
}
in_index=out_index=0;
}

I2C::~I2C() {
	// TODO Auto-generated destructor stub
}

int8_t I2C::I2C0_MasterWriteBlocking(uint8_t address, uint8_t regAddr,uint8_t *data, uint8_t size) {
	uint8_t bytesRemaining = size;
	int8_t aux=-3;
	Base->CFG = (1<<0);
	Base->INTENSET = (1<<24) | (1<<25); //ENABLE TIMEOUT INTERRUPT

	if(I2C_Disponible_Listo(Base->STAT)
			return aux;	// RETURN ERROR BUSY (-3)
			aux++;
	I2C_CargaDir(Base->MSTDAT,address)
	I2C_MST_Start(Base->MSTCTL)
	//-->	Espero de forma bloqueante el envio de datos	<--

	while(aux == -2){
if(I2C_Pendiente(Base->STAT)){
	if(I2C_TransmisionOK(Base->STAT)){
			Base->MSTDAT = regAddr;			//-->	Cargo direccion	<--
			I2C_MST_Continue(Base->MSTCTL);	//-->	Doy a continuar	<--
			aux++;
			}
		else{
			I2C_Stop(Base->MSTCTL)			//-->	STOP
			return aux;						//-->	Retorno Error Nack Direccion	<--
}}}
	while(bytesRemaining+1){
		if(I2C_Pendiente(Base->STAT)){

			if(I2C_TransmisionOK(Base->STAT)){
					if(bytesRemaining){
						Base->MSTDAT = data[size - bytesRemaining];
						I2C_MST_Continue(Base->MSTCTL);
						bytesRemaining--;
					}
					else
						I2C_Stop(Base->MSTCTL)
				}
				else{
					//-->	Datos No transmitidos	<--
					I2C_Stop(Base->MSTCTL)
					if(size - bytesRemaining)
						aux = size - bytesRemaining;
					return aux;	// RETURN ERROR NACK REG(-1) OR BYTES TRANSMITED
				}
			}
		}

		return size - bytesRemaining; //-->	Retorna la cantidad de bytes transmitos	<--
}

int8_t I2C::I2C0_MasterReadBlocking(uint8_t address, uint8_t regAddr,uint8_t *data, uint8_t size) {
	//-->	Desactivar interrupcion	<--

	Base->MSTDAT=(address|(Lectura<<0x8));
	Base->MSTCTL|=(0x1<<1);	//-->	Inicio la transmicion	<--
	while((Base->STAT&(0x1<<1)>>1)!=0x1);
	*data=(Base->MSTDAT&(0xFF));
	I2C_Stop(Base->MSTCTL)

	return 0;

}

int8_t I2C::I2C0_MasterWrite(uint8_t address, uint8_t regAddr, uint8_t *data,uint8_t size, void (*done)(void)) {

	I2C_BufferTrans aux,I2C0_Transmit;
	I2C0->CFG = (1<<0);
	aux.Modo=Escritura;
	aux.Direccion= address;
	aux.regAddr = regAddr;
	aux.Dato= data;
	aux.Tamanio = size;
	aux.IndexDato= 0;
	aux.EstadoTrans = Pendiente;
	Buffer_Push(aux);	//-->	Lo cargo en buffer Para enviar	<--
	if(I2C_DisponibleListo(Base->STAT)){
		return BUSY;	// RETURN ERROR BUSY (-3)
	}
	else
		{
			if(!Buffer_Pop(I2C0_Transmit))
				return ERROR;
			I2C_CargaDir(Base->MSTDAT,I2C0_Transmit.Direccion)
//			Base->MSTDAT = I2C0_Transmit.Direccion<<1 | 0;
			I2C_MST_Start(Base->MSTCTL)
			//Base->MSTCTL = (1<<1);//START
			Base->INTENSET = (1<<0) | (1<<24) | (1<<25);					//ENABLE MASTER PENDING INTERRUPT
		}
		return OK;

//	aux.done=done;
	//aux.done = done;



	return 0;

}

int8_t I2C::I2C0_MasterRead(uint8_t address, uint8_t regAddr, uint8_t *data,uint8_t size, void (*done)(void)) {
	I2C_BufferTrans aux,I2C0_Transmit;
	I2C0->CFG = (1<<0);

	aux.Modo = Lectura;
	aux.Direccion= address;
	aux.regAddr = regAddr;
	aux.Dato = data;
	aux.Tamanio = size;
	aux.IndexDato = 0;
	aux.EstadoTrans = 3;	//-->	No se que significa ese 3 aun	<--
	//aux.done = done;
	Buffer_Push(aux);
	if(I2C_DisponibleListo(Base->STAT)){
			return BUSY;	// RETURN ERROR BUSY (-3)
		}
	else{
		if(!Buffer_Pop(I2C0_Transmit))
			return ERROR;
		I2C_CargaDir(Base->MSTDAT,I2C0_Transmit.Direccion)
		I2C_MST_Start(Base->MSTCTL)
		I2C_Interrupciones(Base->INTENSET)
	}

	return 0;

}
void I2C::Buffer_Push(I2C_BufferTrans& data){
	I2C0_Transmit[0]->Dato=data.Dato;
	I2C0_Transmit[0]->IndexDato++;
	I2C0_Transmit[0]->IndexDato%= I2C0_TRANSMIT_BUFFER_SIZE;

}
uint8_t I2C::Buffer_Pop(I2C_BufferTrans& data){
	I2C0_Transmit[0]=&data;
	return 1;
	//data.IndexDato
}
void I2C::I2C_IRQHandler(void){
	//-->	Por ahora lo usare asi luego veo aunque mejor me manejo con un solo elemento buffer	<--

	if(I2C0_Transmit[0]->Modo==Escritura){
		if(I2C0_Transmit[0]->EstadoTrans==Pendiente){
			if(I2C_Pendiente(Base->STAT)){
				if(I2C_TransmisionOK(Base->STAT)){
					Base->MSTDAT = I2C0_Transmit[0]->regAddr;
					I2C_MST_Continue(Base->MSTCTL)
					I2C0_Transmit[0]->EstadoTrans= 2;
					}
				else{
					I2C_Stop(Base->MSTCTL)
					I2C0_Transmit[0]->EstadoTrans=ERROR_NACK_ADDR;// RETURN ERROR NACK ADDRESS(-2)
					I2C_InterrupcionesA(Base->INTENCLR)
					}
						}
		}
		if(I2C0_Transmit[0]->EstadoTrans== 2){
			if(I2C_Pendiente(Base->STAT)){
				if(I2C_TransmisionOK(Base->STAT)){
					//-->	Verifico Si quedan mas bytes	<--
					if(I2C0_Transmit[0]->IndexDato<I2C0_Transmit[0]->Tamanio){
						Base->MSTDAT = I2C0_Transmit[0]->Dato[I2C0_Transmit[0]->IndexDato];
						I2C_MST_Continue(Base->MSTCTL)
						I2C0_Transmit[0]->IndexDato++;
						}
					//-->	Transmicion completada	<--
					else{
						I2C_Stop(Base->MSTCTL)
						I2C0_Transmit[0]->EstadoTrans=Completa;
//								I2C0_Transmit.done();
						I2C_InterrupcionesA(Base->INTENCLR)
						/*if(Buffer_Pop(*I2C0_Transmit[0])) //START NEXT TRANSMIT IF THERE IS ONE
						{
							I2C_CargaDir(Base->MSTDAT,I2C0_Transmit[0]->Direccion)
							I2C_MST_Start(Base->MSTCTL)
							I2C_Interrupciones(Base->INTENSET)
						}*/
					}
						}
				//-->	Datos no transmitidos	<--
						else{
							I2C_Stop(Base->MSTCTL)
							I2C0_Transmit[0]->EstadoTrans= ERROR_NACK;	// RETURN ERROR NACK REG(-1) OR BYTES TRANSMITED
							I2C_InterrupcionesA(Base->INTENCLR)
						}
					}
				}
return;
	}
	if(I2C0_Transmit[0]->Modo==Lectura){

		if(I2C0_Transmit[0]->EstadoTrans== 3){
				if(I2C_Pendiente(Base->STAT)){
					if(I2C_TransmisionOK(Base->STAT)){
						Base->MSTDAT = I2C0_Transmit[0]->regAddr;
						I2C_MST_Continue(Base->MSTCTL)
						I2C0_Transmit[0]->EstadoTrans= 4;
					}
					else{
						I2C_Stop(Base->MSTCTL)
						I2C0_Transmit[0]->EstadoTrans= ERROR_NACK_ADDR;// RETURN ERROR NACK ADDRESS(-2)
						I2C_InterrupcionesA(Base->INTENCLR)
					}}
			}
			if(I2C0_Transmit[0]->EstadoTrans == 4){
				if(I2C_Pendiente(Base->STAT)){
					if(I2C_TransmisionOK(Base->STAT)){
						Base->MSTDAT = I2C0_Transmit[0]->Direccion<<1 | Lectura;
						I2C_MST_Start(Base->MSTCTL)
						I2C0_Transmit[0]->EstadoTrans= 5;
					}
					else{
						I2C_Stop(Base->MSTCTL)
						I2C0_Transmit[0]->EstadoTrans= ERROR_NACK;	// RETURN ERROR NACK REG(-1) OR BYTES TRANSMITED
						I2C_InterrupcionesA(Base->INTENCLR)
					}}
			}
			if(I2C0_Transmit[0]->EstadoTrans== 5){
				if(I2C_Pendiente(Base->STAT)){
					if(I2C_DatosRecibidos(Base->STAT)){
						I2C0_Transmit[0]->Dato[I2C0_Transmit[0]->IndexDato] = I2C0->MSTDAT;
						I2C0_Transmit[0]->IndexDato++;
						if(I2C0_Transmit[0]->IndexDato< I2C0_Transmit[0]->Tamanio)
							I2C_MST_Continue(Base->MSTCTL)
						else{
							I2C_Stop(Base->MSTCTL)
							I2C0_Transmit[0]->EstadoTrans= 0;
//							I2C0_Transmit.done();
							I2C_InterrupcionesA(Base->INTENCLR)
						/*	if(Buffer_Pop(&I2C0_Transmit)) //START NEXT TRANSMIT IF THERE IS ONE
							{
								I2C_CargaDir(Base->MSTDAT,I2C0_Transmit[0]->Direccion)
								I2C_MST_Start(Base->MSTCTL)
								I2C_InterrupcionesA(Base->INTENSET)
							}
							*/
						}
					}
					//-->	Datos no recividos	<--
					else{
						I2C_Stop(Base->MSTCTL)
						I2C0_Transmit[0]->EstadoTrans= ERROR_NACK;// RETURN ERROR NACK REG(-1) OR BYTES TRANSMITED
						I2C_InterrupcionesA(I2C0->INTENCLR)
					}
				}
			}
			return;
		}

	}

void I2C0_IRQHandler(){
	if(InterI2C[0]!=nullptr){
		((I2C*)InterI2C[0])->I2C_IRQHandler();
		//((I2C*)InterI2C[0])->I2C_IRQHandler();
		}
}
void I2C1_IRQHandler(){
	if(InterI2C[1]!=nullptr){
		((I2C*)InterI2C[1])->I2C_IRQHandler();
		}
}
void I2C2_IRQHandler(){
	if(InterI2C[0]!=nullptr){
		((I2C*)InterI2C[2])->I2C_IRQHandler();
		}
}
void I2C3_IRQHandler(){
	if(InterI2C[3]!=nullptr){
		((I2C*)InterI2C[3])->I2C_IRQHandler();
		}
}
