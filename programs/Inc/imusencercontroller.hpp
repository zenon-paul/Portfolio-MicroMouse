/*
 * imusencercontroller.hpp
 *
 *  Created on: 2024/08/25
 *      Author: sakur
 */

#ifndef INC_IMUSENCERCONTROLLER_HPP_
#define INC_IMUSENCERCONTROLLER_HPP_
#include"imusencer.hpp"
#include"pidcontroller.hpp"
#include"filter.hpp"

class IMUSNCController{
public:
	IMUSNCController(IMUSencer*);
	void reset_pid();
	void set_gain(float p,float i,float d);
	void set_period(float pd);
	void set_target(float tg);
	float calculate();
	void activate();
	void deactivate();
	void set_filter_parameter(float t_);
	bool is_singularity;
	float tmp;
private:
	IMUSencer* imusencer;
	PIDController pidcontroller;
	LPFilter filter;
	bool is_active;
	float target;
};




#endif /* INC_IMUSENCERCONTROLLER_HPP_ */
