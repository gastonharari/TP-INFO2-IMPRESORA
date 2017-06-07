/*******************************************************************************************************************************//**
 *
 * @file		DR_uart.c
 * @brief		Descripcion del modulo
 * @date		31 de ago. de 2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_uart.h"


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
uint8_t bufferTX[MAX_TX]; 	//Buffer de escritura
uint8_t bufferRX[MAX_RX];	//Buffer de Lectura
uint8_t inx_TX_out;			//Flag de escritura(primitiva)
uint8_t inx_TX_in;			//Flag de escritura(driver)
uint8_t inx_RX_out;			//Flag de lectura(driver)
uint8_t inx_RX_in;			//Flag de lectura(primitiva)
uint8_t fEnviando;			//Flag de estado de escritura(PR) 1: escribiendo | 0: libre

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
/**
	\fn  void UART0_IRQHandler (void)
	\brief Interrupcion de UART0
 	\author Ing. Marcelo Trujillo
 	\date 31 de ago. de 2016
 	\param void
	\return void
*/
void UART0_IRQHandler (void)
{
	uint8_t iir, aux;
	int16_t dato;
	do
	{
		//IIR es reset por HW, una vez que lo lei se resetea.
		iir = U0IIR;

		if ( iir & 0x04 ) 							//Data ready
		{
			//Display_lcd ("LLEGO msj -UART0", 0 , 0);
			aux = U0RBR;
			Push_RX ( aux );   	//guardo en buffer e incremento índice
									//garantizo el buffer circular

		}

		if ( iir & 0x02 ) //THRE
		{
			dato = Pop_TX();
			if(dato != -1)			//fuerzo el primer dato
				U0THR = dato;
			else
				fEnviando = 0;		//pongo el flag en NoEnviando(0)
		}
	}
	while( ! ( iir & 0x01 ) ); /* me fijo si cuando entre a la ISR habia otra
						     	int. pendiente de atencion: b0=1 (ocurre unicamente si dentro del mismo
								espacio temporal lleguan dos interrupciones a la vez) */
}

/**
	\fn  void UART0_IRQHandler (void)
	\brief Interrupcion de UART0
 	\author Ing. Marcelo Trujillo
 	\date 31 de ago. de 2016
 	\param void
	\return void
*/


void Push_RX ( uint8_t dato)		//Recibo el dato
{
	bufferRX[inx_RX_in] = dato;		//Lo guardo
	inx_RX_in++;					//Pongo el flag en la posicion siguiente
	inx_RX_in %= MAX_RX;

}

int16_t Pop_TX ( void ){
	int16_t aux;
	if(inx_TX_in == inx_TX_out)		//Miro si el flag de salida esta en el mismo lugar que de entrada, por lo que no hay dato que enviar
		return -1;
	else
		aux = bufferTX[inx_TX_out];	//guardo el dato y aumento el flag
		inx_TX_out++;
		inx_TX_out %= MAX_TX;
		return aux;
}

