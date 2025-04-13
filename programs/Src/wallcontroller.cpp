/*
 * wallcontroller.cpp
 *
 *  Created on: 2024/08/24
 *      Author: sakur
 */
#include"wallcontroller.hpp"

WallController::WallController(WallSencer* f1,WallSencer* l,WallSencer* r,WallSencer* f4)
:tmp(0.0f),
 snc1_forward(f1),
 snc2_left(l),
 snc3_right(r),
 snc4_forward(f4),
 pidcontroller(0.0f,0.0f,0.0f,1.0f),
 filter(1.0,0.0),
 is_active(false),
 left_factor(1.0f),
 right_factor(1.0f),
 prev_left_val(0.0f),
 prev_right_val(0.0f){}

void WallController::reset_pid(){
	this->pidcontroller.reset_pid();
}

void WallController::set_gain(float p,float i,float d){
	this->pidcontroller.set_gain(p,i,d);
}

void WallController::set_period(float pd){
	this->pidcontroller.set_period(pd);
	this->filter.set_period(pd);
}

void WallController::set_factor(float l,float r){
	this->left_factor = l;
	this->right_factor = r;
}

float WallController::calculate(){
	if(this->is_active == false){
		tmp = 0.0f;
		return 0.0f;
	}
	/*if((this->snc1_forward->val > this->snc1_forward->threshold2) && (this->snc4_forward->val > this->snc4_forward->threshold2)){//追記前壁による誤作動が起こる前に制御を切る
		return 0.0f;
	}*/
	//前回の値との差を参考にする<=しなくてよい//前壁ブレーキの実装
	float err_l = 0.0f;
	float err_r = 0.0f;
	float left_val = this->snc2_left->val;
	float right_val = this->snc3_right->val;

	if(this->snc2_left->rigidly_exist){//左壁の壁切れ
		err_l = left_val - (this->snc2_left->threshold + left_factor);
		err_l *= this->left_factor;
	}//右壁の計算を変更した　*-1を追加した
	if(this->snc3_right->rigidly_exist){//右壁の壁切れ
		err_r = right_val - (this->snc3_right->threshold + right_factor);
		err_r *= -1;
		err_r *= this->right_factor;
	}
	if(this->snc1_forward->exist3){//hafl
		//err_l = 0.0f;
		this->pidcontroller.reset_pid();
		this->filter.reset();
		tmp = 0.0f;
		return 0.0f;
	}
	if(this->snc4_forward->exist3){
		//err_r = 0.0f;
		this->pidcontroller.reset_pid();
		this->filter.reset();
		tmp = 0.0f;
		return 0.0f;
	}
	this->prev_left_val = left_val;
	this->prev_right_val = right_val;
	tmp = this->filter.calculate(this->pidcontroller.calculate(0.0f,-(err_l+err_r)));
	return tmp;
}

void WallController::activate(){
	this->is_active = true;
}

void WallController::deactivate(){
	this->is_active = false;
	this->pidcontroller.reset_pid();
	this->filter.reset();
}

void WallController::set_filter_parameter(float t_){
	this->filter.set_t_(t_);
}
