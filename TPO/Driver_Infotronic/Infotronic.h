/*******************************************************************************************************************************//**
 *
 * @file		Infotronic.h
 * @brief		Macros, tipos , prototipos, de la aplicacion
 * @date		23-03-16
 * @author		Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MODULO
 **********************************************************************************************************************************/

#ifndef INFOTRONIC_H_
#define INFOTRONIC_H_

/***********************************************************************************************************************************
 *** INCLUDES GLOBALES
 **********************************************************************************************************************************/
#include "Inicializacion.h"
#include "PR_7seg.h"
#include "PR_Teclado.h"
#include "PR_Timer.h"
#include "DR_timer0123.h"
#include "DR_adc.h"
#include "PR_parcial.h"
#include "PR_uart.h"
#include "PR_extras.h"
#include "DR_MPP.h"


/***********************************************************************************************************************************
 *** DEFINES GLOBALES
 **********************************************************************************************************************************/
#define		RELAY1				2,0
#define		RELAY2				0,23
#define		RELAY3				0,21
#define		RELAY4				0,27

#define 	LedAzul				2,1
#define 	LedRojo				2,2
#define 	LedVerde			2,3

#define		E_analog0			1,31
#define		E_analog1			0,24
#define		E_analog2			0,25

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


#endif /* INFOTRONIC_H_ */