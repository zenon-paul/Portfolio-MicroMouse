/*
 * odometry.cpp
 *
 *  Created on: Aug 11, 2024
 *      Author: sakur
 */
#include"localization.hpp"

//mm rad//
t_pose::t_pose(float initx,float inity,float initrot)
:x(initx),
 y(inity),
 rot(initrot){}

Localization::Localization(IMUSencer* p_imu,DisplacementMeter* left,DisplacementMeter* right,TIM_HandleTypeDef* htimx,uint32_t prscl,uint32_t pd)
:glb(0.0f,0.0f,0.0f),
 approx_rot(0.0f),
 half_wheel_dist_mm(0.0f),
 wheel_radius_mm(0.0f),
 mileage(0.0f),
 left_wheel_mileage(0.0f),
 right_wheel_mileage(0.0f),
 angular_velocity(0.0f),
 imusnc_angular_velocity(0.0f),
 forward_velocity(0.0f),
 left_wheel(left),
 right_wheel(right),
 bno055(p_imu),
 kalmanfilter(),
 update_cycle(htimx,prscl,pd),
 period(0),
 counter_period(0),
 counter(0),
 prev_rad(0.0f),
 is_active(false){}

void Localization::set_filter(float system_mat_a,float system_mat_b,float observation_mat,float system_noise,float observation_noise){
	this->kalmanfilter.set_filter_parameters(system_mat_a,system_mat_b, observation_mat);
	this->kalmanfilter.set_noise_parameters(system_noise, observation_noise, Norm(0,0));
}

void Localization::set_robot_parameters(float d,float radius){
	this->half_wheel_dist_mm = d;
    this->wheel_radius_mm = radius;
}

void Localization::start(float initx,float inity,float initrot,float dts){
	this->glb.x = initx;
	this->glb.y = inity;
	this->glb.rot = initrot;
	this->period = dts;
	this->counter_period = static_cast<uint32_t>(update_cycle.maxHz*period);
	this->kalmanfilter.output.mean = initrot;
	this->kalmanfilter.output.variance = 0;
}

void Localization::calculate(float d_l,float d_r) {//d_l d_rの+-は正しい
	this->mileage += 0.5*(d_l+d_r);///mm
	this->left_wheel_mileage += d_l;//mm
	this->right_wheel_mileage += d_r;//mm
	float lcl_x = 0;
	float lcl_y = 0;
	float lcl_rot = 0;
	if (d_l == d_r)
	{
		lcl_x = d_l;
		lcl_y = 0;
		lcl_rot = 0;
	}
	else {
		lcl_rot = (d_r - d_l) / (2.0 * this->half_wheel_dist_mm);//anti=+ clock=-
		float radius = ((d_r + d_l) * this->half_wheel_dist_mm) / (d_r - d_l);
		float d_len = 2 * radius * sin(0.5 * lcl_rot);//+
		lcl_x = d_len * cos(0.5 * lcl_rot);
		lcl_y = d_len * sin(0.5 * lcl_rot);
	}
//--------------------------------
	//this->kalmanfilter.calculate(lcl_rot,this->bno055->rad);///
//--------------------------------
	glb.x = glb.x + cos(glb.rot) * lcl_x - sin(glb.rot) * lcl_y;//sekibun
	glb.y = glb.y + sin(glb.rot) * lcl_x + cos(glb.rot) * lcl_y;//sekibun
	this->approx_rot += lcl_rot;
	glb.rot = this->bno055->continuous_rad;//this->kalmanfilter.output.mean;///

	this->angular_velocity = lcl_rot/this->period;
	this->imusnc_angular_velocity = (this->glb.rot - this->prev_rad)/this->period;
	if(this->imusnc_angular_velocity < -0.0068){//clock
		this->bno055->set_offset(-0.000002);
	}
	else if(this->imusnc_angular_velocity > 0.0068){//anti
		this->bno055->set_offset(0.0000019);
	}
	else{
		this->bno055->set_offset(0.0);
	}
	this->prev_rad = this->glb.rot;
	this->forward_velocity = 0.5*(this->left_wheel->M_s - this->right_wheel->M_s);
}//右モーターは正の方向が左と逆のため

void Localization::calculate(){
	this->calculate(this->left_wheel->disp_arch,-this->right_wheel->disp_arch);
}

std::vector<float> Localization::get_wheel_velo_from_w_v(float w,float v) {
	float vr = 0.5 * (2*v + w*this->half_wheel_dist_mm);
	float vl = 0.5 * (2*v - w*this->half_wheel_dist_mm);
	std::vector<float>list = {vl,vr};
	return list;
}

void Localization::update(){
	if (this->counter >= this->counter_period){
		this->counter = 0;
		if(this->is_active == false){
			return;
		}
		this->calculate(this->left_wheel->disp_arch,-this->right_wheel->disp_arch);
	}//右のモーターは符号が逆のため
	this->counter += 1;
}

void Localization::activate(){
	this->is_active = true;
}

void Localization::deactivate(){
	this->is_active = false;
}

void Localization::reset_mileage(){
	this->mileage = 0.0f;
}

