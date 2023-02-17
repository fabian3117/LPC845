#include "Letras/Letras.h"

Letras::Letras(uint8_t  Valor){

	 for(uint8_t i=0;i<MAX_Leds;i++){
	    	Leds[i]= new gpio (gpio::port0,16+i, gpio::pushpull , gpio::output , gpio::low);
	    	Leds[i]->SetDir();
	    	Leds[i]->SetPin();

	    }
	 Indice=0;
	 I_Estado=MOSTRANDO;
	 M_Estad[0]=&Letras::Mostrando;
	 M_Estad[1]=&Letras::Actualizando;
	 M_Estad[2]=&Letras::Apagar;
	 controler=new timer(nullptr,timer::DEC);
	// M_Timer<<controler;

	// controler=new timer((void)()Letras::Cambio0,timer::DEC);
	 //secuenciaLeds=new timer(Prender,timer::SEG);
	 //secuenciaIncremento=new timer(this->IncrementaValor,timer::SEG);
	 //secuenciaIncremento->TimerRun(2);
	 ValorMostrar=Valor;
}
void Letras::Mostrando(){
//-->	Nos encargamos de mostrar el numero deseado	<--
	for(uint8_t i=0;i<MAX_Leds;i++){
		//-->	El bit correspondiente esta en 1? PrendeLedAsociada - ApagaLedAsociada	<--

		(ValorMostrar&(0x1<<i))?Leds[i]->SetPin():Leds[i]->ClrPin();
	}
}
void Letras::IncrementaValor(void){
	Indice+=1;
	secuenciaIncremento->TimerRun(2);
}
void Letras::Prender(){
for(uint8_t i=0;i<MAX_Leds;i++){
			if(Character[Indice]&(0x1<<i)){
				Leds[i]->ClrPin();
			}
			else{
				Leds[i]->SetPin();
			}
			}

		//secuenciaLeds->TimerRun(1);
}
void Letras::Prender(uint8_t Valor){

	for(uint8_t i=0;i<MAX_Leds;i++){
	if(Valor&(0x1<<i)){

				//	Leds[i]->ClrPin();
		Prende(Leds[i])
				}
				else{
					Apaga(Leds[i])
					//Leds[i]->SetPin();
				}
}
}
void Letras::Apagar(){
	for(uint8_t i=0;i<MAX_Leds;i++){
					Leds[i]->SetPin();
				}

}
