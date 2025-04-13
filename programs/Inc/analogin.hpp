/*
 * analogin.hpp
 *
 *  Created on: 2024/08/06
 *      Author: sakur
 */

#ifndef INC_ANALOGIN_HPP_
#define INC_ANALOGIN_HPP_

#include<stm32g4xx.h>
#include<stm32g431xx.h>
#include<stm32g4xx_hal_tim.h>

class AnalogIn{
private:
	AnalogIn(ADC_HandleTypeDef*,uint32_t timeout = 100);
	uint16_t analogread();
public:
	ADC_HandleTypeDef* hadcx;
	uint32_t timeout;
};



#endif /* INC_ANALOGIN_HPP_ */
