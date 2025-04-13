/*
 * drive_moters.cpp
 *
 *  Created on: Aug 17, 2024
 *      Author: sakur
 */
#include"motercontroller.hpp"
#include"imusencercontroller.hpp"
#include"wallcontroller.hpp"
#include"drive_moters.hpp"
#include"body_parameters.hpp"

DriveMoters::DriveMoters(MoterController* l,MoterController* r,IMUSNCController* imu,WallController* wall,TIM_HandleTypeDef* htimx,uint32_t prscl,uint32_t pd)
:control_conter(0),
 left_mt_ctrl(l),
 right_mt_ctrl(r),
 imusnccontroller(imu),
 wallcontroller(wall),
 update_cycle(htimx,prscl,pd),
 tg_fv(0.0f),
 tg_fa(0.0f),
 tg_av(0.0f),
 tg_aa(0.0f),
 period(0.0f),
 counter(0),
 counter_period(0),
 is_active(false){}

void DriveMoters::set_target_forward_velocity(float fv){
	this->tg_fv = fv;
}

void DriveMoters::set_target_angular_velocity(float av){
	this->tg_av = av;
}

void DriveMoters::set_target_forward_acceleration(float fa){
	this->tg_fa = fa;
}

void DriveMoters::set_target_angular_acceleration(float aa){
	this->tg_aa = aa;
}

void DriveMoters::start(float pd){
	this->period = pd;
	this->counter_period = static_cast<int>(this->update_cycle.maxHz*pd);
}

void DriveMoters::update(){
	if(this->counter >= this->counter_period){
		this->counter = 0;
		if(this->is_active == false){
			return;
		}
		this->left_mt_ctrl->set_target(this->tg_fv - BodyParameters::HALF_WHEEL_DIST_M*this->tg_av);
		this->right_mt_ctrl->set_target(-this->tg_fv - BodyParameters::HALF_WHEEL_DIST_M*this->tg_av);
		this->tg_fv += this->tg_fa*this->period;
		this->tg_av += this->tg_aa*this->period;
		this->control_conter++;
	}
	this->counter += 1;
}
// 右モーターは前進方向が負であることに注意
// 車体状態の角度の符号に注意 +<-|->-となっている
void DriveMoters::activate(){
	this->is_active = true;
}

void DriveMoters::deactivate(){
	this->is_active = false;
	this->set_target_forward_velocity(0.0f);
	this->set_target_angular_velocity(0.0f);
	this->set_target_forward_acceleration(0.0f);
	this->set_target_angular_acceleration(0.0f);
}
