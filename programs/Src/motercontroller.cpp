/*
 * motercontroller.cpp
 *
 *  Created on: 2024/08/07
 *      Author: sakur
 */
#include"motercontroller.hpp"

MoterController::MoterController(Moter* mt,FFController* ff,WallController* wall,IMUSNCController* imu,DisplacementMeter* wh,TIM_HandleTypeDef* htimx,uint32_t prscl,uint32_t pd)
:moter(mt),
 wheel(wh),
 drive_cycle(htimx,prscl,pd),
 pidcontroller(0.0f,0.0f,0.0f,1.0f),
 ffcontroller(ff),
 wallcontroller(wall),
 imusnccontroller(imu),
 target(0.0f),
 period(0),
 counter(0),
 counter_period(0),
 is_ffctrl_active(false),
 is_active(false),
 factor(1.0f){}

void MoterController::reset_pid(){
	this->pidcontroller.reset_pid();
}

void MoterController::set_gain(float p,float i,float d){
	this->pidcontroller.set_gain(p,i,d);
}

void MoterController::set_target(float tg){
	this->target = tg;//m/s
	if(tg == 0.0f){//目標値0で振動するのを防ぐため
		*(moter) = 0.0f;
		this->reset_pid();
	}
}

void MoterController::set_factor(float f){
	this->factor = f;
}

void MoterController::start(float pd){
	this->pidcontroller.set_period(pd);
	this->period = pd;
	this->counter_period = static_cast<uint32_t>(this->drive_cycle.maxHz*pd);
}

void MoterController::update(){
	if(this->counter >= this->counter_period){
		this->counter = 0;
		if(this->is_active == false){
			return;
		}
		//------sub ctrl---------------(wall imu ...)
		float revision = 0;
		revision += this->wallcontroller->calculate();
		//if(revision < 0.2f){//壁制御と角度補正の兼ね合い
			revision += this->imusnccontroller->calculate();
		//}
		//-----main velocity ctrl----------------
		float moter_input = 0.0f;
		float pid_output = this->pidcontroller.calculate(this->target,this->wheel->M_s);
		this->integral_output += pid_output*this->period;
		if (this->is_ffctrl_active){
		    moter_input = this->factor*(pid_output + this->ffcontroller->calculate(0.0f,this->target) + revision);
		}
		else{
			moter_input = this->factor*(this->integral_output + revision);
		}
		*(moter) = moter_input;
	}
	this->counter += 1;
}

void MoterController::mode(bool isactive){
	this->is_ffctrl_active = isactive;
}

void MoterController::activate(){
	this->is_active = true;
}

void MoterController::deactivate(){
	this->is_active = false;
	this->pidcontroller.reset_pid();
	*(moter) = 0.0f;
}
