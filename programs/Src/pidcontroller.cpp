/*
 * pidcontroller.cpp
 *
 *  Created on: 2024/08/07
 *      Author: sakur
 */
#include"pidcontroller.hpp"

PIDController::PIDController(float p,float i,float d,float dt)
:integral(0),
 prev_error(0),
 prev_tmp(0),
 prev_result(0),
 dTs(dt),
 Pg(p),
 Ig(i),
 Dg(d){}

void PIDController::reset_pid(){
	this->integral = 0.0f;
	this->prev_error = 0.0f;
	this->prev_tmp = 0.0f;
	this->prev_result = 0.0f;
}

void PIDController::set_gain(float p,float i,float d){
	this->Pg = p;
	this->Ig = i;
	this->Dg = d;
}

void PIDController::set_period(float pd){
	this->dTs = pd;
}

float PIDController::calculate(float goal,float current){
	float error = goal - current;
	this->integral += error*this->dTs;
	float diff = (error - this->prev_error)/this->dTs;

	this->prev_error = error;

	float tmp = this->Pg*error + this->Ig*this->integral + this->Dg*diff;
	//-------------------------------------------------
	float tmp_diff = (tmp - this->prev_tmp)/dTs;
	float result = tmp_diff + this->prev_result;

	this->prev_tmp = tmp;
	this->prev_result = result;

	return result;
}


