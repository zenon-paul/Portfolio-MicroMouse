/*
 * filter.hpp
 *
 *  Created on: Aug 11, 2024
 *      Author: sakur
 */

#ifndef INC_FILTER_HPP_
#define INC_FILTER_HPP_

struct Norm{
	float mean;
	float variance;
	Norm(float,float);
	Norm(){}
};

class KalmanfilterD1{
public:
	KalmanfilterD1(float system_mat_a,float system_mat_b,float observation_mat);
	KalmanfilterD1(){}
	Norm calculate(float control,float observation);
	void set_filter_parameters(float system_mat_a,float system_mat_b,float observation_mat);
	void set_noise_parameters(float system_noise,float observation_noise,Norm init_state);
	Norm output;
private:
	float system_mat_a;
	float system_mat_b;
	float observation_mat;
	float system_noise_cov;
	float observation_noise_cov;
	float calculate_kalmangain(float predicted_state_cov);
	Norm predict(Norm prev_updated_state,float control);
	Norm update(Norm predicted_state,float observation,float kalmangain);
};

class LPFilter{
public:
	LPFilter(float T,float t_);
	float calculate(float r_n);
	void set_t_(float new_t_);
	void set_period(float new_T);
	void reset();
private:
	float y_n_1;
	float T;
	float t_;
	float a;
};




#endif /* INC_FILTER_HPP_ */
