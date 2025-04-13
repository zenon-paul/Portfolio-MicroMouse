/*
 * i2c.cpp
 *
 *  Created on: Aug 11, 2024
 *      Author: sakur
 */
#include"i2c.hpp"

I2C::I2C(I2C_HandleTypeDef* hi2cx,uint32_t timeout,uint32_t addr_size)
:hi2cx(hi2cx),
 timeout(timeout),
 i2c_mem_addr_size(addr_size){}

HAL_StatusTypeDef I2C::mem_read(uint8_t div_addr,uint8_t reg_addr,uint8_t* buff,uint8_t size){
	return HAL_I2C_Mem_Read(this->hi2cx,div_addr<<1,reg_addr,this->i2c_mem_addr_size,buff,size,this->timeout);
}

HAL_StatusTypeDef I2C::mem_read(uint8_t div_addr,uint8_t reg_addr,uint8_t* buff){
	return HAL_I2C_Mem_Read(this->hi2cx,div_addr<<1,reg_addr,this->i2c_mem_addr_size,buff,1,this->timeout);
}

HAL_StatusTypeDef I2C::mem_write(uint8_t div_addr,uint8_t reg_addr,uint8_t* buff,uint8_t size){
	return HAL_I2C_Mem_Write(this->hi2cx,div_addr<<1,reg_addr,this->i2c_mem_addr_size,buff,size,this->timeout);
}

HAL_StatusTypeDef I2C::mem_write(uint8_t div_addr,uint8_t reg_addr,uint8_t dat){
	return HAL_I2C_Mem_Write(this->hi2cx,div_addr<<1,reg_addr,this->i2c_mem_addr_size,&dat,1,this->timeout);
}

bool I2C::wait_mem_write(uint8_t div_addr,uint8_t reg_addr,uint8_t* buff,uint8_t size,uint8_t maxtrialnum){
	int f = HAL_ERROR;
	uint16_t cnt = 0;
	while(f != HAL_OK){
	  if (cnt >= maxtrialnum){
		return false;
	  }
	  f = HAL_I2C_Mem_Write(this->hi2cx,div_addr<<1,reg_addr,this->i2c_mem_addr_size,buff,size,this->timeout);
	}
	return true;
}

bool I2C::wait_mem_write(uint8_t div_addr,uint8_t reg_addr,uint8_t dat,uint8_t maxtrialnum){
	int f = HAL_ERROR;
	uint16_t cnt = 0;
	while(f != HAL_OK){
	  if (cnt >= maxtrialnum){
		return false;
	  }
	  f = HAL_I2C_Mem_Write(this->hi2cx,div_addr<<1,reg_addr,this->i2c_mem_addr_size,&dat,1,this->timeout);
	}
	return true;
}



