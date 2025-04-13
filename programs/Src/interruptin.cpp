/*
 * interruptin.cpp
 *
 *  Created on: 2024/08/06
 *      Author: sakur
 */
#include"interruptin.hpp"

InterruptIn::InterruptIn(GPIO_TypeDef* GPIOx,GpioPin::PinName Pin)
:extipin(GPIOx,Pin){
}

void InterruptIn::start(){
	extipin.configure(GPIO_MODE_IT_RISING_FALLING,GPIO_NOPULL,0,0);
}

void InterruptIn::all_extipin_init(){
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

	HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

GPIO_PinState InterruptIn::readpin(){
	return this->extipin.readpin();
}

