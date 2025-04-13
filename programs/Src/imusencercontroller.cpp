/*
 * imusencercontroller.cpp
 *
 *  Created on: 2024/08/25
 *      Author: sakur
 */
#include<math.h>
#include"imusencercontroller.hpp"

IMUSNCController::IMUSNCController(IMUSencer* imu)
:is_singularity(false),
 imusencer(imu),
 pidcontroller(0.0f,0.0f,0.0f,1.0f),
 filter(1.0,0.0),
 is_active(false),
 target(0.0f){}

void IMUSNCController::reset_pid(){
	this->pidcontroller.reset_pid();
}

void IMUSNCController::set_gain(float p,float i,float d){
	this->pidcontroller.set_gain(p,i,d);
}

void IMUSNCController::set_period(float pd){
	this->pidcontroller.set_period(pd);
	this->filter.set_period(pd);
}

void IMUSNCController::set_target(float tg){
	this->pidcontroller.reset_pid();//追記
	//--------特異点付近の処理-----------
	//float a = 0.0f;
	//float f = modff(tg/M_PI,&a);
	if(abs(abs(tg)-M_PI) < 0.01){//2dir
		this->target = M_PI;
		this->is_singularity = true;
		return;
	}
	if(abs(tg + 0.5*M_PI) < 0.01){//1dir
		this->target = 1.5*M_PI;
		this->is_singularity = true;
		return;
	}
	if(abs(tg - 0.5*M_PI) < 0.01){
		this->target = 0.5*M_PI;
		this->is_singularity = true;
		return;
	}
	if(abs(tg) < 0.01){
		this->target = 0.0f;
		this->is_singularity = true;
		return;
	}
	//---------------------------------
	//----------目標値の加工-----------
	float current = this->imusencer->continuous_rad;
	float err = tg - current;
	while(err >= M_PI){//条件変更
		tg -= 2.0*M_PI;
		err = tg - current;
	}
	while(err <= -M_PI){
		tg += 2.0*M_PI;
		err = tg - current;
	}
	//----------------------------
	//---------目標値更新------------
	this->target = tg;
	this->is_singularity = false;
}

float IMUSNCController::calculate(){
	//return 0.0f;///一時的に
	if(this->is_active == false){
		return 0.0f;
	}
	if(this->is_singularity){
		float s = 0.0f;
		if(abs(this->target - this->imusencer->original_rad) > M_PI){
			s = 2.0*M_PI;
		}
		return this->filter.calculate(-(this->pidcontroller.calculate(this->target+s,this->imusencer->original_rad)));
	}
	return this->filter.calculate(-(this->pidcontroller.calculate(this->target,this->imusencer->continuous_rad)));
}

void IMUSNCController::activate(){
	this->is_active = true;
}

void IMUSNCController::deactivate(){
	this->is_active = false;
	this->pidcontroller.reset_pid();
}

void IMUSNCController::set_filter_parameter(float t_){
	this->filter.set_t_(t_);
}
