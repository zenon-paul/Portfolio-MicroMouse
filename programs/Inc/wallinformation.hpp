/*
 * wallinformation.hpp
 *
 *  Created on: Aug 20, 2024
 *      Author: sakur
 */

#ifndef INC_WALLINFORMATION_HPP_
#define INC_WALLINFORMATION_HPP_
#include<stm32g4xx.h>
#include<stm32g431xx.h>
#include<stm32g4xx_hal_flash.h>
#include"flash_memory.hpp"
#include"wallsencer.hpp"
#define THRESHOLDS_ADDR (PAGE63START_ADDR)
//ture->on false->off
class WallInformation{
public:
	WallInformation(WallSencer*,WallSencer*,WallSencer*,WallSencer*);
	void set_factor(float,float,float,float);
	uint32_t register_threshold(uint32_t addr)const;
	void load_threshold(uint32_t addr);
	bool operator[](uint8_t)const;
	bool get_status(uint8_t)const;
	void calculate_threshold(int);
	void calculate_side_threshold(int);
	void calculate_forward_threshold(int);
private:
	WallSencer* snc1_forward;
	WallSencer* snc2_left;
	WallSencer* snc3_right;
	WallSencer* snc4_forward;
};



#endif /* INC_WALLINFORMATION_HPP_ */
