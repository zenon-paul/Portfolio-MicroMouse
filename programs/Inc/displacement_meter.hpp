/*
 * velocity_meter.hpp
 *
 *  Created on: Aug 13, 2024
 *      Author: sakur
 */

#ifndef INC_DISPLACEMENT_METER_HPP_
#define INC_DISPLACEMENT_METER_HPP_
#include<math.h>
#include<stm32g4xx.h>
#include<stm32g431xx.h>
#include"gpio.hpp"
#include"interruptin.hpp"
#include"encoder.hpp"
#include"ticker.hpp"
#include"body_parameters.hpp"

class DisplacementMeter{
public:
	DisplacementMeter(Encoder*,TIM_HandleTypeDef*,uint32_t,uint32_t);
	void start(float);
	void update();
	void activate();
	void deactivate();
	int32_t disp_pulse;
	float disp_rad;
	float disp_arch;
	float M_s;
private:
	Encoder* p_enc;
	Ticker update_cycle;
	float period;
	uint32_t counter_period;
	uint32_t counter;
	int32_t prev_cnt;
	float rad_per_pulse;
	bool is_active;
};




#endif /* INC_DISPLACEMENT_METER_HPP_ */
