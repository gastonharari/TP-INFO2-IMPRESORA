/*******************************************************************************************************************************//**
 *
 * @file		DR_adc.c
 * @brief		Descripcion del modulo
 * @date		5 de jul. de 2016
 * @author		Ing. Marcelo Trujillo
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "DR_adc.h"
#include "DR_EINT.h"
#include "DR_PLL.h"
#include "DR_gpio.h"

/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/


#define		AD0CR				ADC[0]
#define		AD0GDR				ADC[1]
#define		AD0INTEN			ADC[3]

#define			ADINTEN			8
#define			ADINTEN0		0
#define			ADINTEN1		1
#define			ADINTEN2		2
#define			ADINTEN3		3
#define			ADINTEN4		4
#define			ADINTEN5		5
#define			ADINTEN6		6
#define			ADINTEN7		7

#define		AD0DR0				ADC[4]
#define		AD0DR1				ADC[5]
#define		AD0DR2				ADC[6]
#define		AD0DR3				ADC[7]
#define		AD0DR4				ADC[8]
#define		AD0DR5				ADC[9]
#define		AD0DR6				ADC[10]
#define		AD0DR7				ADC[11]
#define		AD0STAT				ADC[12]
#define		AD0TRM				ADC[13]

#define		AD0CR_SEL( x )		( ADC[0] |= (1 << x ) )
#define		AD0CR_CLKDIV ( x )	( ADC[0] |= (x << 8 ) )

#define		CHN0				0
#define		CHN1				1
#define		CHN2				2
#define		CHN3				3
#define		CHN4				4
#define		CHN5				5
#define		CHN6				6
#define		CHN7				7
#define		BURST				16
#define		PDN					21




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
uint16_t	ValorADC[MuestrasADC];
uint8_t 	flagADC = 0;

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
	\fn  void ADC_IRQHandler(void)
	\brief Interrupcion del adc
 	\author Ing. Marcelo Trujillo
 	\date 5 de jul. de 2016
 	\param void
	\return void
*/
void ADC_IRQHandler(void)
{
	static uint8_t i = 0;
	flagADC = 0;
	ValorADC[i] = 0xfff & (AD0DR5 >> 4 );
	i++;
	if( i == 10 ){
		flagADC = 1;
		i = 0;
	}
	AD0CR |=  ( 1 << 24 ); // Disparo la conversion
}


/**
	\fn  void Inic_ADC( void )
	\brief Inicializacion del adc
 	\author Ing. Marcelo Trujillo
 	\date 5 de jul. de 2016
 	\param void
	\return void
*/
void Inic_ADC( void )
{
	SetPINSEL( 1 , 31 , 3 );		// CHN5
	SetPINSEL( 0 , 24 , 1 );		// CHN1 // Entrada analogica 1
	SetPINSEL( 0 , 25 , 1 );		// CHN2 // Entrada analogica 2

	// Pines sin pull down ni pull up
	SetMODE(1, 31, 2 );
	SetMODE(0, 24, 2 );
	SetMODE(0, 25, 2 );

	// ADC
	PCONP |= 1 << PCADC ;			// Activo la alimentacion del dispositivo desde el registro PCONP pag 63:
	PCLKSEL0 &= ~( 0x03 << 24 );	// Selecciono el clock del ADC como 25MHz: Pag 57 CLK/4 (100Mhz/4)
	AD0CR |= 0x0000100;				// Y el divisor como 2, para muestrear a <= 200kHz: Pag 577 CLKDIV bits 8 a 15---> [25Mhz/65(CLKDIV+1)]
	AD0CR  &= ~( 7 << 24 ); // No comienzan las conversiones
	AD0CR |= ( 1 << CHN5 ) | ( 1 << PDN ); // Se habilita el canal 5 y el ADC en si (PDN = 1)

	/*
	 * Se activan interrupciones en el canal 5
	 */
	AD0INTEN |= ( 1 << ADINTEN5 );
	AD0INTEN &= ~(1 << ADINTEN);
	ISE_ADC; // Habilito interrupciones del ADC en NVIC

	AD0CR |= ( 1 << 24 ); // Disparo una conversion
}

