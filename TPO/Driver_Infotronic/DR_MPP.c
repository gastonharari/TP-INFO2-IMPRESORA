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
#define 	E 		0,0
#define 	F		0,0
#define 	G		0,0
#define 	H		0,0
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
uint8_t e_mot[2] = {1,1};
uint8_t cpaso[2] = {0,0};
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
	SetDIR ( E,SALIDA);
	SetDIR ( F,SALIDA);
	SetDIR ( G,SALIDA);
	SetDIR ( H,SALIDA);
}



void motpp_off( uint8_t motor )
{
	if(!motor){
		SetPIN( A, OFF); 		//Exp 6
		SetPIN( B, OFF);		//Exp 7
		SetPIN( C, OFF);		//Exp 8
		SetPIN( D, OFF);		//Exp 9
	}
	else{
		SetPIN( E, OFF); 		//Exp
		SetPIN( F, OFF);		//Exp
		SetPIN( G, OFF);		//Exp
		SetPIN( H, OFF);		//Exp
	}
}

void motpp_r( uint8_t motor ) // Esta funcion hace que el motor de un paso en sentido de las agujas del reloj.
{
	cpaso[motor] = (cpaso[motor] + 1) % NPASOS; // Ponemos el paso siguiente a efectuar
	switch(cpaso[motor]){
	case 0:
		SetPIN( A, ON);
		SetPIN( B, OFF);
		SetPIN( C, OFF);
		SetPIN( D, OFF);
		break;

	case 1:
		SetPIN( A, OFF);
		SetPIN( B, ON);
		SetPIN( C, OFF);
		SetPIN( D, OFF);
		break;

	case 2:
		SetPIN( A, OFF);
		SetPIN( B, OFF);
		SetPIN( C, ON);
		SetPIN( D, OFF);
		break;

	case 3:
		SetPIN( A, OFF);
		SetPIN( B, OFF);
		SetPIN( C, OFF);
		SetPIN( D, ON);
		break;
	}
}

void motpp_cr( uint8_t motor ) // Esta funcion hace que el motor de una vuelta en sentido contrario a las agujas del reloj.
{
	cpaso[motor] = (cpaso[motor] + 1) % NPASOS; // Ponemos el paso siguiente a efectuar (esta funcion resta 1 ciclicamente, 3-1=2 2-1=1 1-1=0 0-1=3
	switch( cpaso[motor] ){
	case 3:
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

	case 1:
		SetPIN( A, OFF);
		SetPIN( B, ON);
		SetPIN( C, ON);
		SetPIN( D, OFF);
		break;

	case 0:
		SetPIN( A, OFF);
		SetPIN( B, OFF);
		SetPIN( C, ON);
		SetPIN( D, ON);
		break;
	}
}

void girar( uint8_t s, uint8_t d, uint8_t motor ) // La variable s indica si es en sentido R o CR, la variable t indica cuantos pasos se van a dar y la variable d indica el retraso (delay)
{
	if( e_mot[motor] ){
		if (s) motpp_r(motor); // Si el sentido es R se ejecuta la function en sentido de las agujas del reloj
		else motpp_cr(motor);// Si el sentido es CR se ejecuta la function en sentido contrario a las agujas del reloj
		retardo(d, motor); // retraso entre paso y paso.
	}
}

void retardo (uint8_t i, uint8_t motor ) // Introduce un retraso
{
	if(!motor){
		TimerStart(MotorX, i, MIL, statX);
		e_mot[MotorX] = 0;
	}
	else{
		e_mot[MotorY] = 0;
		TimerStart(MotorY, i, MIL, statY);
	}
}

void statX(void)
{
	e_mot[MotorX] = 1;
}

void statY(void)
{
	e_mot[MotorY] = 1;
}
