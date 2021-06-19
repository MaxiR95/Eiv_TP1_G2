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
	uint8_t config_catodos = 0xFF; // por defecto - todo apagado
	uint8_t config_anodos = 0; // por defecto - todo apagado

	//Lee boton en A1
	if (Pin_leer(&pulsador) == 0) {
		//si boton presionado, enciende led D1
		Pin_escribir(&led, 0);
		//enciende todos los segmentos del primer display
		config_catodos = 0;
		config_anodos = 1;

	} else {
		//sino, apaga led D1
		Pin_escribir(&led, 1);

	}

	// actualiza pines de salida que controlan el display
	R595_ingresaByte(&registroDisplay, config_catodos);
	R595_ingresaByte(&registroDisplay, config_anodos);
	R595_actualizaSalidas(&registroDisplay);

}
