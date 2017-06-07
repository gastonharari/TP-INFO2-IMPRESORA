/*******************************************************************************************************************************//**
 *
 * @file		Template.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Fecha de creacion del archivo XX/XX/XXXX
 * @author		Nombre, Apellido
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

/*
 * display_7seg.h
 *
 *  Created on: 14/05/2016
 *      Author: Usuario
 */

#ifndef PR_PARCIAL_H_
#define PR_PARCIAL_H_





/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_Teclado.h"
#include "DR_7seg.h"
#include "PR_Teclado.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define DSP0        0
#define DSP1        1
#define Linea1		1
#define Linea2		2
#define Linea3		3


/***********************************************************************************************************************************
 *** MACROS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPO DE DATOS GLOBALES
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES
 **********************************************************************************************************************************/


/***********************************************************************************************************************************
 *** PROTOTIPOS DE FUNCIONES GLOBALES
 **********************************************************************************************************************************/
void Display(unsigned int,unsigned char );

/**
 @fn    void Segmento( uint8_t nlinea, uint8_t nseg , uint8_t estado);
 @brief   Muestra Enciende el segmento nseg le la linea nlinea
  @author  usted
 @param [in] nlinea: numero de lina de segmentos (1 a 3)
  @param [in] nseg: numero de segmento dentro dela linea (1 a 6)
 @param [in] estado: Encendido = 1 / Apagado = 0
  @return void
*/
void Segmento( uint8_t linea, uint8_t seg , uint8_t estado );

/**
 @fn    void Ubicación ( void );
 @brief   indica la posición relativa de un movil
  @author  usted
 @param [in] nlinea: void
 @return un numero que indica la posición relativa de un movil
*/
//uint8_t Ubicacion ( void );

/**
 @fn   uint16_t Temperatura( uint16_t cuentas)
 @brief  Convierte el valor de cuentas en un valor de tempeatura  tal que ;
0 cuenta  0 grados
1000 cuentas 200 grados
2000 cuentas  300 grados
3000 cuentas  380 grados
4000 cuentas  450 grados
En cada segmento la temperatura se comporta de forma lineal .
  @author  usted
 @param [in] cuentas: valor leido del Bufer del ADC
   @return valor de temperatura
*/
//uint16_t Temperatura( uint16_t cuentas);
/**
 @fn   void RGB( uint16_t color,uint8_t accion )
 @brief  Genera el funcionamiento de cada color del RGB
  @author  usted
 @param [in] color: 1:R,2:G, B:3
 @param [in] accion: 0: APAGADO, 1: PRENDIDO, 2: PARPADEA con una frecuencia de 1Hz.
   @return void
*/
//void RGB( uint16_t color,uint8_t accion );
void estacion( void );

void ResetSegmentos( void );
void Cabecera( uint8_t );
void ParpadeaON( void );
void ParpadeaOFF( void );


#endif /* PR_PARCIAL_H_ */
