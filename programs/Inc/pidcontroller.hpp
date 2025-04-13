/*
 * pidcontroller.hpp
 *
 *  Created on: 2024/08/07
 *      Author: sakur
 */

#ifndef INC_PIDCONTROLLER_HPP_
#define INC_PIDCONTROLLER_HPP_

class PIDController{
public:
	PIDController(float,float,float,float);
	PIDController(){}
	void reset_pid();
	void set_gain(float,float,float);
	void set_period(float);
	float calculate(float,float);
private:
	float integral;
	float prev_error;
	float prev_tmp;
	float prev_result;

	float dTs;

	float Pg;
	float Ig;
	float Dg;
};




#endif /* INC_PIDCONTROLLER_HPP_ */
