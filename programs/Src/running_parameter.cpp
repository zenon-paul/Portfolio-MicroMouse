/*
 * running_parameter.cpp
 *
 *  Created on: 2024/09/13
 *      Author: sakur
 */
#include"running_parameter.hpp"
#include"flash_memory.hpp"

RunningParameter::RunningParameter()
:FV(0.0f),
 FA(0.0f),
 AA(0.0f),
 delay_time(0.0f){}

RunningParameter::RunningParameter(float fv,float fa,float aa,float delay)
:FV(fv),
 FA(fa),
 AA(aa),
 delay_time(delay){}

RunningParameterList::RunningParameterList(uint32_t start_addr)
:start_addr(start_addr),
 parameters_num(0),
 next_addr(start_addr){}

uint32_t RunningParameterList::register_parameter(RunningParameter pm){
	this->next_addr = write_flash_float(this->next_addr,pm.FV,pm.FA);
	this->next_addr = write_flash_float(this->next_addr,pm.AA,pm.delay_time);
	this->parameters_num += 1;
	return this->next_addr;
}

void RunningParameterList::load_parameter(uint8_t num,RunningParameter* p){
	if(num >= this->parameters_num){
		return;
	}
	uint32_t n_addr = read_flash_float(this->start_addr + parameter_set_size*num,&(p->FV),&(p->FA));
	read_flash_float(n_addr,&(p->AA),&(p->delay_time));
}






