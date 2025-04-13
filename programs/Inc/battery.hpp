/*
 * battery.hpp
 *
 *  Created on: 2024/09/10
 *      Author: sakur
 */

#ifndef INC_BATTERY_HPP_
#define INC_BATTERY_HPP_
#include"dma_adc.hpp"

class Battery{
public:
	constexpr static float adc2vbat = 0.0322;
	Battery(DmaAdc* pwr_dma);
	float voltage();
private:
	DmaAdc* pwr_dma;
};

#endif /* INC_BATTERY_HPP_ */
