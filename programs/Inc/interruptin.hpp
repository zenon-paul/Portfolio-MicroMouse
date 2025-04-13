/*
 * interruptin.hpp
 *
 *  Created on: 2024/08/06
 *      Author: sakur
 */

#ifndef INC_INTERRUPTIN_HPP_
#define INC_INTERRUPTIN_HPP_
#include<stm32g4xx.h>
#include<stm32g431xx.h>
#include"gpio.hpp"

class InterruptIn{
public:
	InterruptIn(GPIO_TypeDef*,GpioPin::PinName);
	void start();
	static void all_extipin_init();
	GPIO_PinState readpin();
private:
	GpioPin extipin;
};





#endif /* INC_INTERRUPTIN_HPP_ */
