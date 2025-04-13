/*
 * wallsencer.cpp
 *
 *  Created on: Aug 8, 2024
 *      Author: sakur
 */
#include"wallsencer.hpp"
#include"filter.hpp"

float co[100] = {0};
float si[100] = {0};
void init_cs_list();
const uint8_t N = 100;
const uint8_t n = 10;

WallSencer::WallSencer(TIM_HandleTypeDef* htimx,uint32_t channel,uint32_t prescaler,uint32_t period,DmaAdc* sencer_dma,uint8_t dma_pos)
:val(0),
 exist(false),
 rigidly_exist(false),
 exist2(false),
 exist3(false),
 threshold(0.0f),
 threshold2(0.0f),
 threshold3(0.0f),
 factor(1.0f),
 factor2(1.0f),
 factor3(1.0f),
 sencer_dma(sencer_dma),
 sencer_led(htimx,channel,prescaler,period),
 cnt(0),
 sum_c(0),
 sum_s(0),
 dma_pos(dma_pos),
 filter(0.001,0.0){}

void WallSencer::start(){
	this->sencer_led.pwm_start();
	this->sencer_led.writepin((uint32_t)49);

	//this->sencer_dma->dma_start();
}

void WallSencer::calculate(){
	if(cnt >= N){
		val = this->filter.calculate(sum_c*sum_c+sum_s*sum_s);
		///val = sum_c*sum_c+sum_s*sum_s;
	    cnt = 0;
	    sum_c = 0;
	    sum_s = 0;
	    if(val < factor*threshold){//off
	    	exist = false;
	    }
	    else{
	    	exist = true;//on
	    }
	    if(val < threshold){//追記
	    	rigidly_exist = false;
	    }
	    else{
	    	rigidly_exist = true;
	    }
	    if(val < factor2*threshold2){
	    	exist2 = false;
	    }
	    else{
	    	exist2 = true;
	    }
	    if(val < factor3*threshold3){
	    	exist3 = false;
	    }
	    else{
	    	exist3 = true;
	    }
	}
	float c_ = co[cnt];
	float s_ = si[cnt];
	uint16_t a = sencer_dma->get_val(dma_pos);
	sum_c += c_*a;
	sum_s += s_*a;
	cnt++;
}

void WallSencer::set_factor(float f){
	this->factor = f;
}

void WallSencer::set_factor2(float f){
	this->factor2 = f;
}

void WallSencer::set_factor3(float f){
	this->factor3 = f;
}

float WallSencer::calculate_threshold(int sample_num){
	if(sample_num <= 0){
		return 0.0f;
	}
	this->threshold = 0;
	int i = 0;
	while(i<sample_num){
		this->threshold += this->val/sample_num;
		HAL_Delay(5);
		i++;
	}
	return this->threshold;
}

float WallSencer::calculate_threshold2(int sample_num){
	if(sample_num <= 0){
		return 0.0f;
	}
	this->threshold2 = 0;
	int i = 0;
	while(i<sample_num){
		this->threshold2 += this->val/sample_num;
		HAL_Delay(5);
		i++;
	}
	return this->threshold2;
}

float WallSencer::calculate_threshold3(int sample_num){
	if(sample_num <= 0){
		return 0.0f;
	}
	this->threshold3 = 0;
	int i = 0;
	while(i<sample_num){
		this->threshold3 += this->val/sample_num;
		HAL_Delay(5);
		i++;
	}
	return this->threshold3;
}

bool WallSencer::get_status()const{
//	if(this->val < this->factor*this->threshold){
//		return false;//wall off
//	}
//	else{
//		return true; //wall on
//	}
	return exist;
}

void WallSencer::set_filter_t_(float t_){
	this->filter.set_t_(t_);
}

void init_cs_list(){
	for(int i = 0;i<100;i++){
		float rad_ = (-2*3.141592*10*i)/100;
		co[i] = round(10*cos(rad_))/1000.0f;
		si[i] = round(10*sin(rad_))/1000.0f;
	}
}


