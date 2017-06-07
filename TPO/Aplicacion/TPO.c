/*
===============================================================================
 Name        : TPO.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>
#include "Infotronic.h"
#include "Inicializacion.h"

void teststepper ( void );

int main(void) {

		Inicializacion();
		while(1)
		{
			teststepper();
			TimerEvent();
		}
		return 0;
}

void teststepper ( void ){
	static uint8_t c = 0, a=0;
	c = GetKey();
	if(c == 255){
		c = a;
	}
	switch(c){
		case 1:
			girar( CR, 1, MotorX); //Sentido R 200 pasos 10 u.t.
			a = 1;
			break;
		case 2:
			girar( R, 1, MotorX); //Sentido R 200 pasos 10 u.t.
			a = 2;
			break;
		case 3:
			motpp_off(MotorX);
			a = 0;
			break;
	}
	return;
}
