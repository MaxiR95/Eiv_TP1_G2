/*
 * App.c
 *
 *  Created on: May 8, 2021
 *      Author: Eiv
 */

#include <main.h>

void setup(void) {

}

void loop(void) {
	//enciende/apaga led D1, cada 500ms
	//HAL_GPIO_TogglePin(Led_D1_GPIO_Port, Led_D1_Pin);
	//HAL_Delay(500);

	//Lee boton en A1
	if (HAL_GPIO_ReadPin(pulsador_GPIO_Port, pulsador_Pin) == GPIO_PIN_RESET) {
		//si boton presionado, enciende led D1
		HAL_GPIO_WritePin(Led_GPIO_Port, Led_Pin, GPIO_PIN_RESET);
	} else {
		//sino, apaga led D1
		HAL_GPIO_WritePin(Led_GPIO_Port, Led_Pin, GPIO_PIN_SET);
	}
}
