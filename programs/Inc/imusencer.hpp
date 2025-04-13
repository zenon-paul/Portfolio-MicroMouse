/*
 * imusencer.hpp
 *
 *  Created on: Aug 11, 2024
 *      Author: sakur
 */

#ifndef INC_IMUSENCER_HPP_
#define INC_IMUSENCER_HPP_
#include<math.h>
#include<stm32g4xx.h>
#include<stm32g431xx.h>
#include<stm32g4xx_hal_i2c.h>
#include"i2c.hpp"
#include<mutex>

class IMUSencer{
public:
	IMUSencer(I2C_HandleTypeDef*,uint32_t,uint32_t);
	float read_eul_heading(bool);
	void start(uint8_t);
	void set_offset(float );
	static const int32_t max_eul_heading = 5760;
	static const int32_t half_eul_heading = 2880;
	//float deg;
	float rad;
	float continuous_rad;
	//float original_deg;
	float original_rad;
private:
	I2C i2c;
	const float eul_h_deg_lsb;
	const float eul_h_rad_lsb;
	float prev_continuous_rad;
	float drift;
	float offset;
};





#endif /* INC_IMUSENCER_HPP_ */
