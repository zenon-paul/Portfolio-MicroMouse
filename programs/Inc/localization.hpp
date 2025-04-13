/*
 * odometry.hpp
 *
 *  Created on: Aug 11, 2024
 *      Author: sakur
 */

#ifndef INC_LOCALIZATION_HPP_
#define INC_LOCALIZATION_HPP_
#include<math.h>
#include<stm32g4xx.h>
#include<stm32g431xx.h>
#include<vector>
#include"displacement_meter.hpp"
#include"ticker.hpp"
#include"imusencer.hpp"
#include"filter.hpp"

class t_pose {
public:
	float x;//mm
    float y;//mm
	float rot;//rad
	t_pose(float initx,float inity,float initrot);
	t_pose(){}
};

class Localization{
public:
	t_pose glb;
	float approx_rot;
	Localization(IMUSencer*,DisplacementMeter*,DisplacementMeter*,TIM_HandleTypeDef*,uint32_t,uint32_t);
    void set_filter(float system_mat_a,float system_mat_b,float observation_mat,float system_noise,float observation_noise);
	void set_robot_parameters(float d,float radius);
	void start(float,float,float,float);
    void calculate(float d_l,float d_r);
    void calculate();
    void update();
	std::vector<float> get_wheel_velo_from_w_v(float w,float v);
	void activate();
	void deactivate();
	void reset_mileage();
	float half_wheel_dist_mm;
	float wheel_radius_mm;
	float mileage;
	float left_wheel_mileage;
	float right_wheel_mileage;
	float angular_velocity;//rad/s
	float imusnc_angular_velocity;//rad/s
	float forward_velocity;//m/s
private:
	DisplacementMeter* left_wheel;
	DisplacementMeter* right_wheel;
	IMUSencer* bno055;
	KalmanfilterD1 kalmanfilter;
	Ticker update_cycle;
	float period;//s
	uint32_t counter_period;
	uint32_t counter;
	float prev_rad;
	bool is_active;
};




#endif /* INC_LOCALIZATION_HPP_ */
