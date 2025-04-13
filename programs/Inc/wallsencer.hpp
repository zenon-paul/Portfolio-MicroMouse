/*
 * wallsencer.hpp
 *
 *  Created on: Aug 8, 2024
 *      Author: sakur
 */

#ifndef INC_WALLSENCER_HPP_
#define INC_WALLSENCER_HPP_
#include<stm32g4xx.h>
#include<stm32g431xx.h>
#include<math.h>
#include"pwmout.hpp"
#include"dma_adc.hpp"
#include"filter.hpp"

class WallSencer{
public:
	WallSencer(TIM_HandleTypeDef*,uint32_t,uint32_t,uint32_t,DmaAdc*,uint8_t);
	void start();
	void calculate();
	void set_factor(float);
	void set_factor2(float);
	void set_factor3(float);
	float calculate_threshold(int);
	float calculate_threshold2(int);
	float calculate_threshold3(int);
	bool get_status()const;
	void set_filter_t_(float t_);
	float val;
	bool exist;
	bool rigidly_exist;
	bool exist2;
	bool exist3;
	//----------------
	float threshold;
	float threshold2;
	float threshold3;
	//----------------
	float factor;
	float factor2;
	float factor3;
private:
	DmaAdc* sencer_dma;
	PwmOut sencer_led;
	uint8_t cnt;
	float sum_c;
	float sum_s;
	uint8_t dma_pos;
	LPFilter filter;
};

void init_cs_list();




#endif /* INC_WALLSENCER_HPP_ */
