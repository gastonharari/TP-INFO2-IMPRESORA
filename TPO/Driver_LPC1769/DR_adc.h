/*******************************************************************************************************************************//**
 *
 * @file		DR_adc.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		5 de jul. de 2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/
#ifndef DR_ADC_H_
#define DR_ADC_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_tipos.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

#define		ADC					( ( __RW unsigned int  * ) 0x40034000UL )

#define		AD0DR_RESULT( x ) 		( ( ADC[ 4 + x ] >> 4) & 0xfff )
#define		AD0DR_OVERRUN( x )		( ( ADC[ 4 + x ] >> 30 ) & 1 )
#define		AD0DR_DONE( x )			( ( ADC[ 4 + x ] >> 31 ) & 1 )

#define 	canal1		0
#define 	canal2		1
#define 	canal5		2

/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/
#define 	MuestrasADC 		100

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/
extern uint16_t	ValorADC[MuestrasADC];
extern uint8_t flagADC;

/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/

void Inic_ADC( void );
void ADC_IRQHandler(void);


#endif /* DR_ADC_H_ */
