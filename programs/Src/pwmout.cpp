/*
 * pwmout.cpp
 *
 *  Created on: 2024/08/06
 *      Author: sakur
 */
#include"pwmout.hpp"

PwmOut::PwmOut(TIM_HandleTypeDef* htimx,uint32_t ch,uint32_t prscl,uint32_t pd)
:period(pd),
 htimx(htimx),
 channel(ch),
 prescaler(prscl){}

void PwmOut::pwm_start(){
	HAL_TIM_PWM_Start(this->htimx,this->channel);
}

void PwmOut::writepin(float duty){
	if (duty < 0) return;
	if (duty > 1) return;
	uint32_t count = static_cast<uint32_t>(std::round(this->period*duty));
	__HAL_TIM_SET_COMPARE(this->htimx,this->channel,count);
}

void PwmOut::writepin(uint32_t count){
	if(count > this->period) return;
	__HAL_TIM_SET_COMPARE(this->htimx,this->channel,count);
}

void PwmOut::operator=(float duty){
	if (duty < 0) return;
	if (duty > 1) return;
	uint32_t count = static_cast<uint32_t>(std::round(this->period*duty));
	__HAL_TIM_SET_COMPARE(this->htimx,this->channel,count);
}

void PwmOut::operator=(uint32_t count){
	if(count > this->period) return;
	__HAL_TIM_SET_COMPARE(this->htimx,this->channel,count);
}


