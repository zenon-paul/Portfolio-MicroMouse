/*
 * ffcontroller.hpp
 *
 *  Created on: Aug 16, 2024
 *      Author: sakur
 */

#ifndef INC_FFCONTROLLER_HPP_
#define INC_FFCONTROLLER_HPP_
#include<math.h>
#include"dma_adc.hpp"
#include"moter_parameters.hpp"
#include"body_parameters.hpp"

class FFController{
public:
	constexpr static float gain = 0.25;
	constexpr static float adc2vbat = 0.0322;
	FFController(DmaAdc*);
	float calculate(float,float);
private:
	using Pram = MoterParameters;
	DmaAdc* pwr_adc;
};




#endif /* INC_FFCONTROLLER_HPP_ */
