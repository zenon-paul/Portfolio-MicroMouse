/*
 * imusencer.cpp
 *
 *  Created on: Aug 11, 2024
 *      Author: sakur
 */
#include"imusencer.hpp"
#include"BNO055.hpp"

IMUSencer::IMUSencer(I2C_HandleTypeDef* hi2cx,uint32_t timeout,uint32_t addr_size)
:rad(0.0f),
 continuous_rad(0.0f),
 original_rad(0.0f),
 i2c(hi2cx,timeout,addr_size),
 eul_h_deg_lsb(16.0f),
 eul_h_rad_lsb(900.0f),
 prev_continuous_rad(0.0f),
 drift(0.0f),
 offset(0.0f){}

float IMUSencer::read_eul_heading(bool is_degree){
	uint8_t buff[2] = {0};
	this->i2c.mem_read(BNO055_I2C_ADDR0,BNO055_EULER_H_LSB_ADDR,buff,2);
	int16_t val = (buff[1]<<8)|buff[0];
	int16_t val_ = val;//original_radのため
	//---------------------------------------
	if(val > this->half_eul_heading){//原点の変更
		val = val - max_eul_heading;
	}
	float deg = -val/this->eul_h_deg_lsb;
	rad = deg*M_PI/180.0f;
	//------------------------------
	float original_deg = 360.0-val_/this->eul_h_deg_lsb;
	original_rad = original_deg*M_PI/180.0f;
	//--------------------------------------------
	//--------drift分の補正---------------------
	rad += drift;
	original_rad += drift;
	//----------------------------------------
	drift += offset;
	//----------------------------------------

	//--------calculate continuous rot-------
	continuous_rad = rad;
	float diff = continuous_rad - prev_continuous_rad;
	if(diff>M_PI){
		continuous_rad = prev_continuous_rad - 2*M_PI + diff;
	}
	else if(diff<-M_PI){
		continuous_rad = prev_continuous_rad + 2*M_PI + diff;
	}
	prev_continuous_rad = continuous_rad;

	if (is_degree){
		return deg;
	}
	return rad;
}

void IMUSencer::start(uint8_t mode){
	this->i2c.wait_mem_write(BNO055_I2C_ADDR0,BNO055_SYS_TRGGER_ADDR,SYS_RESET,255);
	HAL_Delay(50);
	this->i2c.wait_mem_write(BNO055_I2C_ADDR0,BNO055_PWR_MODE_ADDR,PWR_MODE_NORMAL,255);
	HAL_Delay(50);
	this->i2c.wait_mem_write(BNO055_I2C_ADDR0,BNO055_SYS_TRGGER_ADDR,0x0,255);
	HAL_Delay(50);
	this->i2c.wait_mem_write(BNO055_I2C_ADDR0,BNO055_OPR_MODE_ADDR,mode,255);
	HAL_Delay(50);
	this->drift = 0.0f;//ここでドラフトは一回リセットされる
	this->rad = 0.0f;
	this->continuous_rad = 0.0f;
	this->original_rad = 0.0f;
	this->prev_continuous_rad = 0.0f;
}

void IMUSencer::set_offset(float offset){
	this->offset = offset;
}




