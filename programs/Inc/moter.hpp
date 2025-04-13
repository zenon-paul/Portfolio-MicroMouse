/*
 * moter.hpp
 *
 *  Created on: 2024/08/06
 *      Author: sakur
 */

#ifndef INC_MOTER_HPP_
#define INC_MOTER_HPP_
#include<stm32g4xx.h>
#include<stm32g431xx.h>
#include<stm32g4xx_hal_tim.h>
#include"pwmout.hpp"
#include"gpio.hpp"

class Moter{
public:
	Moter(GPIO_TypeDef*,GpioPin::PinName,TIM_HandleTypeDef*,uint32_t,uint32_t,uint32_t);
	void start();
	void drive(int32_t);
	void drive(float);
	void operator=(int32_t);
	void operator=(float);
private:
	PwmOut spd;
	GpioPin dir;
	static const GPIO_PinState PLUS = GPIO_PIN_RESET;
	static const GPIO_PinState MINUS = GPIO_PIN_SET;
};





#endif /* INC_MOTER_HPP_ */
