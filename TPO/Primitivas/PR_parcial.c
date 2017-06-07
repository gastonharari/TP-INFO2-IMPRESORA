/*******************************************************************************************************************************//**
 *
 * @file		void Display(unsigned int Val,unsigned char dsp)
 * @brief		valor int a presentar en el display
 * @date
 * @author		Año 2016
 *
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** INCLUDES
 **********************************************************************************************************************************/
#include "PR_parcial.h"
#include "Infotronic.h"
/***********************************************************************************************************************************
 *** DEFINES PRIVADOS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** MACROS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** TIPOS DE DATOS PRIVADOS AL MODULO
 **********************************************************************************************************************************/
uint8_t act = 0;
/***********************************************************************************************************************************
 *** TABLAS PRIVADAS AL MODULO
 **********************************************************************************************************************************/

/***********************************************************************************************************************************
 *** VARIABLES GLOBALES PUBLICAS
 **********************************************************************************************************************************/

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


/**
 @fn    void Segmento( uint8_t nlinea, uint8_t nseg , uint8_t estado);
 @brief   Muestra Enciende el segmento nseg le la linea nlinea
  @author  usted
 @param [in] nlinea: numero de lina de segmentos (1 a 3)
  @param [in] nseg: numero de segmento dentro dela linea (1 a 6)
 @param [in] estado: Encendido = 1 / Apagado = 0
  @return void
*/
void Segmento( uint8_t linea, uint8_t seg , uint8_t estado ){

	char aux[3]={0x01,0x40,0x08};
//	Digito_Display[seg] = aux[linea];
	if(estado){
		Digito_Display[seg] = aux[linea];
	}
	else {
		Digito_Display[seg] = ((Digito_Display[seg]) & (aux[linea]));
	}
}

/**
 @fn    void Ubicación ( void );
 @brief   indica la posición relativa de un movil
  @author  usted
 @param [in] nlinea: void
 @return un numero que indica la posición relativa de un movil
*/
void estacion ( void ){
	static uint8_t ant = 0;
	uint8_t aux;
	aux = GetKey();
	switch(aux){
	case 0:
		ResetSegmentos();

		break;
	case 1:
		if(act < 5){
			ant = act;
			act++;
			break;
		}
		if(act == 5 && ant < act){
			ResetSegmentos();
			ant = act;
			break;
		}
		break;
	case 2:
		ResetSegmentos();
		ant = 5;
		aux = ant;
		break;
	}
//	TimerStart(1, 1, 1000, (Segmento(1, aux, ON)));

}

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
uint16_t Temperatura( uint16_t cuentas){
	if(cuentas<=1000){
		Display(001, 0);
		cuentas=cuentas/5;
		return cuentas;
	}
	if(1000<cuentas)if(cuentas<=2000){
		Display(002, 0);
		cuentas=cuentas/(20/3);
		return cuentas;
	}
	if(2000<cuentas)if(cuentas<=3000){
		Display(003, 0);
		cuentas=cuentas/(250/34);
		return cuentas;
	}
	if(cuentas>3000){
		Display(004, 0);
		cuentas=cuentas/(100/7);
		return cuentas;
	}
	cuentas = (0xff);
	return cuentas;
}

void ParpadeaON ( void ){
	static uint8_t estado = 0;
	if(estado){
		FIO0PIN = FIO0PIN | ( 1 << 22 );
	}
	else{
		FIO0PIN = FIO0PIN & ~( 1 << 22 );
	}
	estado++;
	estado %= 2;
}
