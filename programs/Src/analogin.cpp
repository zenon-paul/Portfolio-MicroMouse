/*
 * analogin.cpp
 *
 *  Created on: 2024/08/06
 *      Author: sakur
 */
#include"analogin.hpp"

AnalogIn::AnalogIn(ADC_HandleTypeDef* hadcx,uint32_t timeout)
:hadcx(hadcx),
 timeout(timeout){}

uint16_t AnalogIn::analogread(){
	HAL_ADC_Start(this->hadcx);
	HAL_ADC_PollForConversion(this->hadcx,this->timeout);
	HAL_ADC_Stop(this->hadcx);
	return HAL_ADC_GetValue(this->hadcx);
}



