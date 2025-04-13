/*
 * ticker.hpp
 *
 *  Created on: 2024/08/06
 *      Author: sakur
 */

#ifndef INC_TICKER_HPP_
#define INC_TICKER_HPP_
#include<functional>
#include<stm32g4xx.h>
#include<stm32g431xx.h>
#include<stm32g4xx_hal_tim.h>
#include<vector>
#include<functional>

class Ticker{
public:
	static const uint32_t clock = 170000000;
	Ticker(TIM_HandleTypeDef*,uint32_t,uint32_t);
	void start();
	uint32_t period;
	float maxHz;
private:
	TIM_HandleTypeDef* htimx;
	uint32_t prescaler;
};




#endif /* INC_TICKER_HPP_ */
