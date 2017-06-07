/*******************************************************************************************************************************//**
 *
 * @file		DR_MPP.c
 * @brief		Módulo que contiene el driver de utilizacion del MPP
 * @date		Fecha de creacion del archivo 5/4/2017
 * @author		Santiago, Mac Mullen
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/

#include "DR_gpio.h"
#include "DR_MPP.h"
#include "PR_Timer.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

#define 	A 		3,26
#define 	B		1,25
#define 	C		1,22
#define 	D		1,19

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/
uint8_t estadoX = 1;

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/

void Inicializar_MPP ( void )
{
	SetDIR ( A,SALIDA);
	SetDIR ( B,SALIDA);
	SetDIR ( C,SALIDA);
	SetDIR ( D,SALIDA);
}



void motpp_off(void)
{
	SetPIN( A, OFF); 		//Exp 6
	SetPIN( B, OFF);		//Exp 7
	SetPIN( C, OFF);		//Exp 8
	SetPIN( D, OFF);		//Exp 9
}

void motpp_r(void) // Esta funcion hace que el motor de un paso en sentido de las agujas del reloj.
{
	static unsigned char cpaso=0;

	cpaso = (cpaso + 1) % NPASOS; // Ponemos el paso siguiente a efectuar
    if (cpaso==0)
    	cpaso=1;
	switch(cpaso){
	case 1:
		SetPIN( A, ON);
		SetPIN( B, OFF);
		SetPIN( C, OFF);
		SetPIN( D, OFF);
		break;

	case 2:
		SetPIN( A, OFF);
		SetPIN( B, ON);
		SetPIN( C, OFF);
		SetPIN( D, OFF);
		break;

	case 3:
		SetPIN( A, OFF);
		SetPIN( B, OFF);
		SetPIN( C, ON);
		SetPIN( D, OFF);
		break;

	case 4:
		SetPIN( A, OFF);
		SetPIN( B, OFF);
		SetPIN( C, OFF);
		SetPIN( D, ON);
		break;
	}
}

void motpp_cr(void) // Esta funcion hace que el motor de una vuelta en sentido contrario a las agujas del reloj.
{
	static unsigned char cpaso=0;

	cpaso = (cpaso+1) % NPASOS; // Ponemos el paso siguiente a efectuar (esta funcion resta 1 ciclicamente, 3-1=2 2-1=1 1-1=0 0-1=3
	if (cpaso==0)
	    	cpaso=1;
	switch(cpaso){
	case 1:
		SetPIN( A, ON);
		SetPIN( B, OFF);
		SetPIN( C, OFF);
		SetPIN( D, ON);
		break;

	case 2:
		SetPIN( A, ON);
		SetPIN( B, ON);
		SetPIN( C, OFF);
		SetPIN( D, OFF);
		break;

	case 3:
		SetPIN( A, OFF);
		SetPIN( B, ON);
		SetPIN( C, ON);
		SetPIN( D, OFF);
		break;

	case 4:
		SetPIN( A, OFF);
		SetPIN( B, OFF);
		SetPIN( C, ON);
		SetPIN( D, ON);
		break;
	}
}

void girar(unsigned char s, unsigned int d) // La variable s indica si es en sentido R o CR, la variable t indica cuantos pasos se van a dar y la variable d indica el retraso (delay)
{
	if(estadoX){
		if (s) motpp_r(); // Si el sentido es R se ejecuta la function en sentido de las agujas del reloj
		else motpp_cr();// Si el sentido es CR se ejecuta la function en sentido contrario a las agujas del reloj
		estadoX = 0;
		retardo(d); // retraso entre paso y paso.
	}
}

void retardoX (uint8_t i) // Introduce un retraso
{
	TimerStart(MotorX, i, MIL, statX);
}

void retardoY (uint8_t i) // Introduce un retraso
{
	TimerStart(MotorY, i, MIL, statY);
}

void statX(void)
{
	estado[] = 1;
}

void statY(void)
{
	estado[] = 1;
}
