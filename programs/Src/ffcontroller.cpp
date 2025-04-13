/*
 * ffcontroller.cpp
 *
 *  Created on: Aug 16, 2024
 *      Author: sakur
 */
#include"ffcontroller.hpp"

static float v2rpm(float v){//m/s
	return (60.0*v)/(2*MoterParameters::GEAR_RATE*M_PI*BodyParameters::WHEEL_RADIUS_M);
}

FFController::FFController(DmaAdc* dma)
:pwr_adc(dma){}

float FFController::calculate(float torque,float w){
	w = v2rpm(w);//M_s >> rpm
	float adc = this->pwr_adc->get_val(0);
	float Vbat = FFController::adc2vbat*adc;
	return gain*(Pram::REG*torque/Pram::Kt + Pram::Ke*w)/Vbat;
}//torque[Nm] w[rpm]//gain





