/*
 * drive_moters.hpp
 *
 *  Created on: Aug 17, 2024
 *      Author: sakur
 */

#ifndef INC_DRIVE_MOTERS_HPP_
#define INC_DRIVE_MOTERS_HPP_
#include<math.h>
#include"imusencer.hpp"
#include"motercontroller.hpp"
#include"imusencercontroller.hpp"
#include"wallcontroller.hpp"

class DriveMoters{
public:
	DriveMoters(MoterController* l,MoterController* r,IMUSNCController* imu,WallController* wall,TIM_HandleTypeDef* htimx,uint32_t prscl,uint32_t pd);
	void set_target_forward_velocity(float fv);
	void set_target_angular_velocity(float av);
	void set_target_forward_acceleration(float fa);
	void set_target_angular_acceleration(float aa);
	void start(float pd);
	void update();
	void activate();
	void deactivate();
	uint32_t control_conter;
private:
	MoterController* left_mt_ctrl;
	MoterController* right_mt_ctrl;
	IMUSNCController* imusnccontroller;
	WallController* wallcontroller;
	Ticker update_cycle;
	float tg_fv;//m/s
	float tg_fa;//m/s^2
	float tg_av;//rad/s
	float tg_aa;//rad/s^2
	float period;
	uint32_t counter;
	uint32_t counter_period;
	bool is_active;
};



#endif /* INC_DRIVE_MOTERS_HPP_ */
