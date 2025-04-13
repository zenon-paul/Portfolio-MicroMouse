/*
 * moter.cpp
 *
 *  Created on: 2024/08/06
 *      Author: sakur
 */
#include"moter.hpp"

Moter::Moter(GPIO_TypeDef* GPIOx,GpioPin::PinName Pin,TIM_HandleTypeDef* htimx,uint32_t channel,uint32_t prescaler,uint32_t period)
:spd(htimx,channel,prescaler,period),
 dir(GPIOx,Pin){}

void Moter::start(){
	this->dir.configure(GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_LOW,0);
	this->spd.pwm_start();
	this->spd=(uint32_t)0;
	this->dir=PLUS;
}

void Moter::drive(int32_t velo){
	int32_t period = this->spd.period;
	uint32_t tmp = 0;
	if (velo >= 0){
		this->dir = PLUS;
		if (velo >= period){
			tmp = static_cast<uint32_t>(period);
		}
		else{
			tmp = static_cast<uint32_t>(velo);
		}
	}
	else{
		this->dir = MINUS;
		if (velo <= -period){
			tmp = static_cast<uint32_t>(period);
		}
		else{
			tmp = static_cast<uint32_t>(-velo);
		}
	}
	this->spd = tmp;
}

void Moter::drive(float velo){
	float tmp = 0;
	if (velo >= 0){
		this->dir = PLUS;
		if (velo >= 1){
			tmp = 1;
		}
		else{
			tmp = velo;
		}
	}
	else{
		this->dir = MINUS;
		if (velo <= -1){
			tmp = 1;
		}
		else{
			tmp = -velo;
		}
	}
	this->spd = tmp;
}

void Moter::operator=(int32_t velo){
	int32_t period = this->spd.period;
	uint32_t tmp = 0;
	if (velo >= 0){
		this->dir = PLUS;
		if (velo >= period){
			tmp = static_cast<uint32_t>(period);
		}
		else{
			tmp = static_cast<uint32_t>(velo);
		}
	}
	else{
		this->dir = MINUS;
		if (velo <= -period){
			tmp = static_cast<uint32_t>(period);
		}
		else{
			tmp = static_cast<uint32_t>(-velo);
		}
	}
	this->spd = tmp;
}

void Moter::operator=(float velo){
	float tmp = 0;
	if (velo >= 0){
		this->dir = PLUS;
		if (velo >= 1){
			tmp = 1;
		}
		else{
			tmp = velo;
		}
	}
	else{
		this->dir = MINUS;
		if (velo <= -1){
			tmp = 1;
		}
		else{
			tmp = -velo;
		}
	}
	this->spd = tmp;
}


