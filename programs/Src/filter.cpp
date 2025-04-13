/*
 * filter.cpp
 *
 *  Created on: Aug 11, 2024
 *      Author: sakur
 */
#include"filter.hpp"

Norm::Norm(float u,float s)
:mean(u),
 variance(s){}

KalmanfilterD1::KalmanfilterD1(float system_mat_a,float system_mat_b,float observation_mat)
:output(0,0),
 system_mat_a(system_mat_a),
 system_mat_b(system_mat_b),
 observation_mat(observation_mat),
 system_noise_cov(0),
 observation_noise_cov(0){}

float KalmanfilterD1::calculate_kalmangain(float predicted_state_variance){
	float k = predicted_state_variance*this->observation_mat;
	return k / (this->observation_mat*predicted_state_variance*this->observation_mat + this->observation_noise_cov);
}

Norm KalmanfilterD1::predict(Norm prev_updated_state,float control){
	Norm predicted_state;
	predicted_state.mean = this->system_mat_a * prev_updated_state.mean + this->system_mat_b * control;
	predicted_state.variance = this->system_mat_a * prev_updated_state.variance * this->system_mat_a + this->system_noise_cov;
	return predicted_state;
}

Norm KalmanfilterD1::update(Norm predicted_state,float observation,float kalmangain){
	Norm updated_state;
	updated_state.mean = predicted_state.mean + kalmangain * (observation - this->observation_mat*predicted_state.mean);
	updated_state.variance = predicted_state.variance - kalmangain * this->observation_mat * predicted_state.variance;
	return updated_state;
}

Norm KalmanfilterD1::calculate(float control,float observation){
	Norm predicted_state = predict(this->output,control);
	float k = calculate_kalmangain(predicted_state.variance);
	this->output = update(predicted_state,observation,k);
	return this->output;
}

void KalmanfilterD1::set_filter_parameters(float sys_a,float sys_b,float obs){
	this->system_mat_a = sys_a;
	this->system_mat_b = sys_b;
	this->observation_mat = obs;
}

void KalmanfilterD1::set_noise_parameters(float system_noise,float observation_noise,Norm init_state){
	this->system_noise_cov = system_noise;
	this->observation_noise_cov = observation_noise;
	this->output = init_state;
}

LPFilter::LPFilter(float T,float t_)
:y_n_1(0.0f),
 T(T),
 t_(t_),
 a(t_/(T+t_)){}

float LPFilter::calculate(float r_n){
	float y_n = a*y_n_1 + (1 - a)*r_n;
	y_n_1 = y_n;//前回値
	return y_n;
}

void LPFilter::set_t_(float new_t_){
	t_ = new_t_;
	a = new_t_/(T+new_t_);
}

void LPFilter::set_period(float new_T){
	T = new_T;
	a = t_/(new_T+t_);
}

void LPFilter::reset(){
	y_n_1 = 0.0f;
}
