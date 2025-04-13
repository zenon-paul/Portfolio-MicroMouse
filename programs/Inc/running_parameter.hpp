/*
 * running_parameter.hpp
 *
 *  Created on: 2024/09/13
 *      Author: sakur
 */

#ifndef INC_RUNNING_PARAMETER_HPP_
#define INC_RUNNING_PARAMETER_HPP_
#include<stdint.h>

class RunningParameter{
public:
	float FV;
	float FA;
	float AA;
	float delay_time;
	RunningParameter();
	RunningParameter(float fv,float fa,float aa,float delay);
};

class RunningParameterList{
public:
	constexpr static uint32_t parameter_set_size = 16;
	uint32_t start_addr;
	uint8_t parameters_num;
	uint32_t next_addr;
	RunningParameterList(uint32_t start_addr);
	uint32_t register_parameter(RunningParameter pm);
	void load_parameter(uint8_t num,RunningParameter* p);
};



#endif /* INC_RUNNING_PARAMETER_HPP_ */
