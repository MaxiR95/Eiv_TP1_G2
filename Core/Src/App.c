/*
 * App.c
 *
 *  Created on: May 8, 2021
 *      Author: Eiv
 */

#include <main.h>



/* Pin */
/*-----struct-----*/
typedef struct Pin{
	GPIO_TypeDef *gpio;
	uint16_t pin;
}Pin;
/*-----funciones-----*/
void Pin_init(Pin *self, GPIO_TypeDef *gpio, uint16_t pin)
{
	self->gpio=gpio;
	self->pin=pin;
}
int Pin_leer(Pin *self)
{
	return HAL_GPIO_ReadPin(self->gpio, self->pin);
}
void Pin_escribir(Pin *self,int valor)
{
	HAL_GPIO_WritePin(self->gpio, self->pin, valor);
}
/*-----fin----------*/





static Pin pulsador;
static Pin led;

void setup(void) {
	Pin_init(&pulsador,pulsador_GPIO_Port,pulsador_Pin);
	Pin_init(&led,Led_GPIO_Port,Led_Pin);
}
void loop(void) {
	//Lee boton en A1
	if (Pin_leer(&pulsador) == 0) {
		//si boton presionado, enciende led D1
		Pin_escribir(&led, 0);
	} else {
		//sino, apaga led D1
		Pin_escribir(&led, 1);
	}

}
