/*******************************************************************************************************************************//**
 *
 * @file		DR_Teclado.c
 * @brief		Descripcion del modulo
 * @date		8 de jun. de 2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_Teclado.h"
#include "DR_gpio.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/
#define REBOTES				4



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
uint8_t Tecla = NO_KEY;

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
/** @fn void InicializarTeclado( void )
 * @brief Inicializacion del teclado de 4x1 de la placa BASE Infotronic
 * @details No portable
 * 		<ul>
 *		<li> KEY0..3: puerto y pin de cada tecla
 * 		<li> FUNCION_GPIO: Funcion GPIO del pin del micro
 * 		<li> ENTRADA: Configura a la GPIO como entrada
 * 		<li> PINMODE_PULLUP: aplica a la entrada un pullup interno
 * 		</ul>
 * @param 	void.
 * @return 	void.
 */
void InicializarTeclado( void )
{
	SetPINSEL ( KEY1 , FUNCION_GPIO );
	SetPINSEL ( KEY2 , FUNCION_GPIO );
	SetPINSEL ( KEY3 , FUNCION_GPIO );
	SetPINSEL ( KEY4 , FUNCION_GPIO );

	SetDIR ( KEY1 , ENTRADA );
	SetDIR ( KEY2 , ENTRADA );
	SetDIR ( KEY3 , ENTRADA );
	SetDIR ( KEY4 , ENTRADA );

	SetMODE ( KEY1 , PULLUP );
	SetMODE ( KEY2 , PULLUP );
	SetMODE ( KEY3 , PULLUP );
	SetMODE ( KEY4 , PULLUP );
}

/** @fn void DriverTecladoSW (  void )
 * @brief Elimina el rebote de la tecla pulsada
 * @details Portable
 * @details Caracteristicas de las macros utilizadas
 * 		<ul>
 * 		<li> REBOTES: Cantidad de veces que se cuenta un cambio de estado para darlo por valido
 * 		<li> NO_KEY: No hay tecla pulsada
 * 		</ul>
 * @param 	void.
 * @return	void.
 */
void DriverTecladoSW (  void )
{
	static unsigned char CodigoAnterior = NO_KEY;	//!< Conserva el valor del codigo de la tecla  ante el primer cambio de estado
	static unsigned char EstadosEstables;			//!< Contador de estados estables consecutivos
	unsigned char CodigoActual;						//!< Nueva lectura del las GPIO de teclado

	CodigoActual = DriverTecladoHW(  );

	if( CodigoActual == NO_KEY ) // Si no esta presionando ningun boton
	{
		CodigoAnterior = NO_KEY;
		EstadosEstables = 0;
		return;
	}

	if( EstadosEstables == 0 ) // Si recien apreto un boton por primera vez
	{
		CodigoAnterior = CodigoActual;
		EstadosEstables = 1;
		return;
	}

	if( CodigoActual != CodigoAnterior ) // Si solto al boton
	{
		CodigoAnterior = NO_KEY;
		EstadosEstables = 0;
		return;
	}

	if( EstadosEstables == REBOTES ) // Si mantuvo el boton el tiempo necesario
	{
		Tecla = CodigoActual;
		EstadosEstables++;

		return;
	}

	if( EstadosEstables == REBOTES + 1 ) // Si mantuvo el boton mas tiempo de lo necesario
		return;

	EstadosEstables ++; // Si aun no suelta el boton pero no llego al necesario

	return;
}

/** @fn unsigned char DriverTecladoHW( void )
 * @brief Lectura de las GPIO asignadas a las teclas
 * @details No Portable
 * @details Caracteristicas de las macros utilizadas
 * 		<ul>
 * 		<li> NO_KEY: No hay tecla pulsada
 * 		<li> KEY0..3: puerto y pin de cada tecla
 * 		<li> ACTIVO_ALTO: Configuracion del  puerto como activo alto
 * 		</ul>
 * @param 	void.
 * @return 	codigo asignado a la tecla leida.
 */
uint8_t DriverTecladoHW( void )
{
	uint8_t Codigo = NO_KEY;

	if ( ! GetPIN ( KEY1 , ALTO ) )
		return 1;

	if ( ! GetPIN ( KEY2 , ALTO ) )
		return 2;

	if ( ! GetPIN ( KEY3 , ALTO ) )
		return 3;

	if ( ! GetPIN ( KEY4 , ALTO ) )
		return 4;

	if ( ! GetPIN ( KEY5 , ALTO ) )
		return 5;

	return Codigo;
}



