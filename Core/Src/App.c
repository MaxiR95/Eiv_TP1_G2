/*
 * App.c
 *
 *  Created on: May 8, 2021
 *      Author: Eiv
 */

#include <main.h>



/* Pin (encabezado - .h)*/
typedef struct Pin{
	GPIO_TypeDef *gpio;
	uint16_t pin;
}Pin;
void Pin_init(Pin *self, GPIO_TypeDef *gpio, uint16_t pin);
int Pin_leer(Pin *self);
void Pin_escribir(Pin *self,int valor);

/*Pin (implementación - .c)*/
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
/*----fin----*/


/* R595 (encabezado - .h)*/
/**
 * Controlador para registro de desplazamiento 74HC595
 */
typedef struct R595{
	Pin *dato;
	Pin *reloj;
	Pin *cerrojo;
}R595;

/**
 * Inicializa el objeto R595
 * @param self puntero a struct R595 a inicializar
 * @param dato puntero a objeto Pin que controla el pin conectado
 *             a la entrada Data del 74HC595
 * @param reloj puntero a objeto Pin que controla el pin conectado
 *              a la entrada Clock del 74HC595
 * @param reloj puntero a objeto Pin que controla el pin conectado
 *              a la entrada Latch del 74HC595
 */
void R595_init(R595 *self,Pin *dato, Pin *reloj, Pin *cerrojo);
/**
 * Ingresa un byte en el registro de desplazamiento controlado por este objeto
 * @param self puntero a struct con el estado correctamente inicializado
 *             del objeto R595
 * @param byte byte a ingresar en el registro de desplazamiento
 */
void R595_ingresaByte(R595 *self,uint8_t byte);
/**
 * Actualiza las salidas del registro de desplazamiento controlado por este objeto
 * desde el estado interno (operación de latch)
 * @param self puntero a struct con el estado correctamente inicializado
 *             del objeto R595
 */
void R595_actualizaSalidas(R595 *self);

/* R595 (implementación - .c)*/
void R595_init(R595 *self,Pin *dato, Pin *reloj, Pin *cerrojo)
{
	/* REEMPLAZAR POR UNA IMPLEMENTACIÓN QUE FUNCIONE */
	/*stub - implementación vacía, reemplazar con la verdadera implementación*/
	(void)self;
	(void)dato;
	(void)reloj;
	(void)cerrojo;
}
void R595_ingresaByte(R595 *self,uint8_t byte)
{
	/* REEMPLAZAR POR UNA IMPLEMENTACIÓN QUE FUNCIONE */
	/*stub - implementación vacía, reemplazar con la verdadera implementación*/
	(void)self;
	(void)byte;
}
void R595_actualizaSalidas(R595 *self)
{
	/* REEMPLAZAR POR UNA IMPLEMENTACIÓN QUE FUNCIONE */
	/*stub - implementación vacía, reemplazar con la verdadera implementación*/
	(void)self;
}

/*----fin----*/

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
