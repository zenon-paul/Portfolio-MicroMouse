/*
 * battery.cpp
 *
 *  Created on: 2024/09/10
 *      Author: sakur
 */
#include"battery.hpp"

Battery::Battery(DmaAdc* pwr_dma):pwr_dma(pwr_dma){}

float Battery::voltage(){
	float adc = this->pwr_dma->get_val(0);
	return Battery::adc2vbat*adc;
}



