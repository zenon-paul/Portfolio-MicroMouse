/*
 * dma_adc.hpp
 *
 *  Created on: 2024/08/06
 *      Author: sakur
 */

#ifndef INC_DMA_ADC_HPP_
#define INC_DMA_ADC_HPP_
#include<stm32g4xx.h>
#include<stm32g431xx.h>
#include<stm32g4xx_hal_tim.h>
#include"analogin.hpp"

class DmaAdc{
public:
	DmaAdc(DMA_HandleTypeDef*,ADC_HandleTypeDef*,uint8_t);
	~DmaAdc();
	void dma_start();
	uint16_t operator[](uint8_t)const &;
	uint16_t get_val(uint8_t);
private:
	DMA_HandleTypeDef* hdma_adcx;
	ADC_HandleTypeDef* hadcx;
	uint16_t* adc_buff;
	uint8_t buffsize;
};





#endif /* INC_DMA_ADC_HPP_ */
