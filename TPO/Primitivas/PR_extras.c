/*
 * PR_extras.c
 *
 *  Created on: 16 de oct. de 2016
 *      Author: santi_000
 */

#include "PR_extras.h"

/*
 @fn    uint8_t Temp(void);
 @brief   Devuelve el valor de la temperatura en °C.
  @author  Santiago Mac Mullen
  @return void
*/
int32_t ADCvalue( void ){
	uint16_t i = 0;
	int32_t valor = 0;
	if(flagADC == 1){
		for(i=0; i<MuestrasADC; i++){
			valor += ValorADC[i];
		}
		valor /= MuestrasADC;
		flagADC = 0;
		return valor;
	}
	else{
		return 0;
	}
}
