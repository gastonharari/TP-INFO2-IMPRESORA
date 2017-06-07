/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "PR_uart.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/
extern uint8_t bufferTX[MAX_TX]; 	//Buffer de escritura
extern uint8_t bufferRX[MAX_RX];	//Buffer de Lectura
extern uint8_t inx_TX_out;			//Flag de escritura(primitiva)
extern uint8_t inx_TX_in;			//Flag de escritura(driver)
extern uint8_t inx_RX_out;			//Flag de lectura(driver)
extern uint8_t inx_RX_in;			//Flag de lectura(primitiva)
extern uint8_t fEnviando;			//Flag de estado de escritura(PR) 1: escribiendo | 0: libre

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** PROTOTIPO DE FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES PRIVADAS AL MODULO
 **********************************************************************************************************************************/

 /***********************************************************************************************************************************
 *** FUNCIONES GLOBALES AL MODULO
 **********************************************************************************************************************************/
/**/
void Push_TX ( uint8_t dato ){
	if( !fEnviando  ){
		fEnviando = 1;					//Si no esta enviando, pongo el flag en 1(enviando)
		U0THR = dato;					//Forzo el primer dato
	}
	else{
		bufferTX[inx_TX_in] = dato;		//Meto el dato en el buffer
		inx_TX_in++;					//Aumento el flag
		inx_TX_in %= MAX_TX;
	}
}

int16_t Pop_RX ( void )
{
	int8_t aux;

	if (inx_RX_in == inx_RX_out)
		return -1 ;					//No hay dato que sacar

	aux = bufferRX[inx_RX_out]; 	//Tomo el dato
	inx_RX_out++;					//Incremento la variable
	inx_RX_out %= MAX_RX;

	return ( uint16_t ) aux;		//Devuelvo el dato

}

void Transmitir ( int8_t *S)
{
	while(*S)
	{
		Push_TX(*S);
		S++;
	}
}