/*
 * r595.c
 *
 *  Created on: 18 jun. 2021
 *      Author: Dra Escudero Rocio I
 */
#include<r595.h>
/* R595 (implementación - .c)*/
void R595_init(R595 *self,Pin *dato, Pin *reloj, Pin *cerrojo)
{
	/* REEMPLAZAR POR UNA IMPLEMENTACIÓN QUE FUNCIONE */
	self->dato=dato;
	self->reloj=reloj;
	self->cerrojo=cerrojo;
}
void R595_ingresaByte(R595 *self,uint8_t byte)
{
	for(int i=7;i>=0;--i){
		const uint8_t mascara=(1<<i);

		Pin_escribir(self->reloj, 0);
		const int bit= (byte & mascara)==mascara;
		Pin_escribir(self->dato,bit);
		Pin_escribir(self->reloj,1);
	}
	Pin_escribir(self->reloj,0);
	Pin_escribir(self->dato,0);
}
void R595_actualizaSalidas(R595 *self)
{
	Pin_escribir(self->cerrojo,1);
	Pin_escribir(self->cerrojo,0);

}

/*----fin----*/

