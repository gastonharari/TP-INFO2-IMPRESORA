/*******************************************************************************************************************************//**
 *
 * @file		Inicializacion.h
 * @brief		Breve descripción del objetivo del Módulo
 * @date		Fecha de creacion del archivo XX/XX/XXXX
 * @author		Nombre, Apellido
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef INICIALIZACION_H_
#define INICIALIZACION_H_
/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "DR_gpio.h"
#include "DR_SysTick.h"
#include "DR_PLL.h"
#include "DR_EINT.h"
#include "DR_adc.h"
#include "DR_uart.h"

/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/

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
void Inicializacion( void );
void RELAYS_OFF (void);
void UART0_Inicializacion (void);

#endif /* INICIALIZACION_H_ */
