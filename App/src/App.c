/*
 * App.c
 *
 *  Created on: May 8, 2021
 *      Author: Eiv
 */

#include <main.h>
#include <App.h>
#include <pin.h>
#include <r595.h>







static Pin pulsador;
static Pin led;

static Pin data;
static Pin clock;
static Pin latch;

static R595 registroDisplay;

static uint8_t palabras[2][4]={
		{0x79|0x80, 0x24|0x80, 0x30|0x80, 0x19|0x80},		//digitos 1 2 3 4 sin puntos,
		{0x88, 0x83, 0xC6, 0xA1}};		//letras A B C D sin puntos


void setup(void) {
	/*Inicializar objetos Pin*/
	Pin_init(&pulsador,pulsador_GPIO_Port,pulsador_Pin);
	Pin_init(&led,Led_GPIO_Port,Led_Pin);
	/* HACER: Terminar inicialización pines*/
	Pin_init(&data,data_GPIO_Port,data_Pin);
	Pin_init(&clock,clock_GPIO_Port,clock_Pin);
	Pin_init(&latch,latch_GPIO_Port,latch_Pin);

	/*Inicializar driver registro de desplazamiento*/
	R595_init(&registroDisplay, &data, &clock, &latch);
}


void loop(void) {
	int j=0;

	//Lee boton en A1
	if (Pin_leer(&pulsador) == 0) {
		j=1;
	}

	for(int i=0 ; i<4 ; i++){

		uint8_t config_catodos = palabras[j][i];
		uint8_t config_anodos = 1<<i;
		// actualiza pines de salida que controlan el display
		R595_ingresaByte(&registroDisplay, config_catodos);
		R595_ingresaByte(&registroDisplay, config_anodos);
		R595_actualizaSalidas(&registroDisplay);
	}




}
