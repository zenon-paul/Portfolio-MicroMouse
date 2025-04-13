/*
 * indicator_utility.cpp
 *
 *  Created on: 2024/09/12
 *      Author: sakur
 */
#include"mouse_system_objects.hpp"

void start_func(){
	ind1 = GPIO_PIN_SET;
	ind2 = GPIO_PIN_SET;
	HAL_Delay(500);
	ind1 = GPIO_PIN_RESET;
	ind2 = GPIO_PIN_RESET;
	HAL_Delay(500);
	ind1 = GPIO_PIN_SET;
	ind2 = GPIO_PIN_SET;
	HAL_Delay(500);
	ind1 = GPIO_PIN_RESET;
	ind2 = GPIO_PIN_RESET;
	HAL_Delay(500);
}

void tika1(){
	ind1 = GPIO_PIN_SET;
	ind2 = GPIO_PIN_SET;
	HAL_Delay(100);
	ind1 = GPIO_PIN_RESET;
	ind2 = GPIO_PIN_RESET;
	HAL_Delay(100);
	ind1 = GPIO_PIN_SET;
	ind2 = GPIO_PIN_SET;
	HAL_Delay(100);
	ind1 = GPIO_PIN_RESET;
	ind2 = GPIO_PIN_RESET;
	HAL_Delay(100);
}

void indicate_entor(){
	for(int i = 0;i<4;i++){
	ind1.togglepin();
	ind2.togglepin();
	ind3.togglepin();
	ind4.togglepin();
	HAL_Delay(100);
	}
}



