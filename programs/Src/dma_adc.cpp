/*
 * dma_adc.cpp
 *
 *  Created on: 2024/08/06
 *      Author: sakur
 */
#include"dma_adc.hpp"

DmaAdc::DmaAdc(DMA_HandleTypeDef* hdma_adcx,ADC_HandleTypeDef* hadcx,uint8_t buffsize)
:hdma_adcx(hdma_adcx),
 hadcx(hadcx),
 adc_buff(new uint16_t[buffsize]),
 buffsize(buffsize){}

DmaAdc::~DmaAdc(){
	delete[] this->adc_buff;
}

void DmaAdc::dma_start(){
	HAL_ADCEx_Calibration_Start(this->hadcx, ADC_SINGLE_ENDED);
	HAL_ADC_Start_DMA(this->hadcx, (uint32_t *)this->adc_buff,this->buffsize);
	this->hdma_adcx->Instance->CCR &= ~(DMA_IT_TC | DMA_IT_HT);
}

uint16_t DmaAdc::operator[](uint8_t index)const &{
	if (index > this->buffsize) return 0;
	return this->adc_buff[index];
}

uint16_t DmaAdc::get_val(uint8_t index){
	if (index > this->buffsize) return 0;
	return this->adc_buff[index];
}

