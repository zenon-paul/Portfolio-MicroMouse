/*
 * velocity_meter.cpp
 *
 *  Created on: Aug 13, 2024
 *      Author: sakur
 */
#include"displacement_meter.hpp"

DisplacementMeter::DisplacementMeter(Encoder* p_enc,TIM_HandleTypeDef* htimx,uint32_t prscl,uint32_t pd)
:disp_pulse(0),
 disp_rad(0.0f),
 disp_arch(0.0f),
 M_s(0.0f),
 p_enc(p_enc),
 update_cycle(htimx,prscl,pd),
 period(0.0f),
 counter_period(0),
 counter(0),
 prev_cnt(0),
 rad_per_pulse(2*M_PI/p_enc->resolution),
 is_active(false){}

void DisplacementMeter::start(float period){
	this->period = period;
	this->counter_period = static_cast<uint32_t>(this->update_cycle.maxHz*period);
}

void DisplacementMeter::update(){
	if (this->counter >= this->counter_period){
		this->counter = 0;
		if(this->is_active == false){
			return;
		}
		//--------------
		int32_t cnt = this->p_enc->count;
		this->disp_pulse = cnt - this->prev_cnt;
		this->prev_cnt = cnt;
		//--------------
		this->disp_rad = this->rad_per_pulse * this->disp_pulse;
		this->disp_arch = this->disp_rad*BodyParameters::WHEEL_RADIUS;
		this->M_s = this->disp_arch/(this->period*1000.0);
	}
	this->counter += 1;
}//arch[mm]

void DisplacementMeter::activate(){
	this->is_active = true;
}

void DisplacementMeter::deactivate(){
	this->is_active = false;
}

