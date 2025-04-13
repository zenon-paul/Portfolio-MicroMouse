/*
 * pwmout.hpp
 *
 *  Created on: 2024/08/06
 *      Author: sakur
 */

#ifndef INC_PWMOUT_HPP_
#define INC_PWMOUT_HPP_
#include<math.h>
#include<stm32g4xx.h>
#include<stm32g431xx.h>
#include<stm32g4xx_hal_tim.h>

class PwmOut{
public:
	PwmOut(TIM_HandleTypeDef*,uint32_t,uint32_t,uint32_t);
	void pwm_start();
	void writepin(float);
	void writepin(uint32_t);
	void operator=(float);
	void operator=(uint32_t);
	uint32_t period;
private:
	TIM_HandleTypeDef* htimx;
	uint32_t channel;
	uint32_t prescaler;
};




#endif /* INC_PWMOUT_HPP_ */
