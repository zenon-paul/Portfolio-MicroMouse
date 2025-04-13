/*
 * wallcontroller.hpp
 *
 *  Created on: 2024/08/24
 *      Author: sakur
 */

#ifndef INC_WALLCONTROLLER_HPP_
#define INC_WALLCONTROLLER_HPP_
#include"wallsencer.hpp"
#include"PIDController.hpp"
#include"filter.hpp"

class WallController{
public:
	WallController(WallSencer* f1,WallSencer* l,WallSencer* r,WallSencer* f4);
	void reset_pid();
	void set_gain(float p,float i,float d);
	void set_period(float pd);
	void set_factor(float l,float r);
	float calculate();
	void activate();
	void deactivate();
	void set_filter_parameter(float t_);
	float tmp;
private:
	WallSencer* snc1_forward;
	WallSencer* snc2_left;
	WallSencer* snc3_right;
	WallSencer* snc4_forward;
	PIDController pidcontroller;
	LPFilter filter;
	bool is_active;
	float left_factor;
	float right_factor;
	float prev_left_val;
	float prev_right_val;
};




#endif /* INC_WALLCONTROLLER_HPP_ */
