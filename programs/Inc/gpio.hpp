/*
 * gpio.hpp
 *
 *  Created on: 2024/08/06
 *      Author: sakur
 */

#ifndef INC_GPIO_HPP_
#define INC_GPIO_HPP_
#include<stm32g4xx.h>
#include<stm32g431xx.h>
#include<stm32g4xx_hal_rcc.h>
#include<stm32g4xx_hal_gpio.h>

class GpioPin{
public:
	using PinName = uint32_t;
	using PinMode = uint32_t;
	using PinPull = uint32_t;
	using PinSpeed = uint32_t;
	using PinAlternate = uint32_t;

	GpioPin(GPIO_TypeDef*,PinName);
	GpioPin(GPIO_TypeDef*,PinName,PinMode,PinPull,PinSpeed,PinAlternate);
	void configure(PinMode,PinPull,PinSpeed,PinAlternate);
	void deconfigure();
	void exti_config(IRQn_Type);
	static void all_gpio_init();

	GPIO_PinState readpin();
	void writepin(GPIO_PinState);
	void operator=(GPIO_PinState);
	void operator=(int);
	void operator=(bool);
	void togglepin();
	void on();
	void off();
	HAL_StatusTypeDef lockpin();

	uint32_t pin();
private:
	static const uint8_t GPIO_NUMBER = 16U;
	GPIO_TypeDef *GPIOx;
	PinName Pin;
	static uint8_t instance_num;
};




#endif /* INC_GPIO_HPP_ */
