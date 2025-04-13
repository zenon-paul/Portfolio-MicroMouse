/*
 * encoder.hpp
 *
 *  Created on: 2024/08/06
 *      Author: sakur
 */

#ifndef INC_ENCODER_HPP_
#define INC_ENCODER_HPP_
#include<stm32g4xx.h>
#include<stm32g431xx.h>
#include"gpio.hpp"
#include"interruptin.hpp"

class Encoder{
public:
	Encoder(GPIO_TypeDef*,GpioPin::PinName,GPIO_TypeDef*,GpioPin::PinName,int32_t);
	void start();
	void calculate(uint32_t);
	void set_count_zero();
	int32_t count;
	int32_t resolution;
private:
	InterruptIn Apin;
	uint32_t A_GPIO_Pin;
	InterruptIn Bpin;
	uint32_t B_GPIO_Pin;
};




#endif /* INC_ENCODER_HPP_ */
