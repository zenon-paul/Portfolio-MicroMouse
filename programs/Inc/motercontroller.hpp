/*
 * motercontroller.hpp
 *
 *  Created on: 2024/08/07
 *      Author: sakur
 */

#ifndef INC_MOTERCONTROLLER_HPP_
#define INC_MOTERCONTROLLER_HPP_
#include<stm32g4xx.h>
#include<stm32g431xx.h>
#include"ffcontroller.hpp"
#include"pidcontroller.hpp"
#include"moter.hpp"
#include"ticker.hpp"
#include"displacement_meter.hpp"
#include"wallcontroller.hpp"
#include"imusencercontroller.hpp"

class MoterController{
public:
	MoterController(Moter* mt,FFController* ff,WallController* wall,IMUSNCController* imu,DisplacementMeter* wh,TIM_HandleTypeDef* htimx,uint32_t prscl,uint32_t pd);
	void reset_pid();
	void set_gain(float p,float i,float d);
	void set_target(float tg);
	void set_factor(float f);
	void start(float pd);
	void update();
	void mode(bool);
	void activate();
	void deactivate();
private:
	Moter* moter;
	DisplacementMeter* wheel;
	Ticker drive_cycle;
	PIDController pidcontroller;
	FFController* ffcontroller;
	WallController* wallcontroller;
	IMUSNCController* imusnccontroller;
	float target;
	float period;
	uint32_t counter;
	uint32_t counter_period;
	float integral_output;
	bool is_ffctrl_active;
	bool is_active;
	float factor;
};




#endif /* INC_MOTERCONTROLLER_HPP_ */
