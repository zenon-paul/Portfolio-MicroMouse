/*
 * i2c.hpp
 *
 *  Created on: Aug 11, 2024
 *      Author: sakur
 */

#ifndef INC_I2C_HPP_
#define INC_I2C_HPP_
#include<stm32g4xx.h>
#include<stm32g431xx.h>
#include<stm32g4xx_hal_i2c.h>

class I2C{
public:
	I2C(I2C_HandleTypeDef*,uint32_t,uint32_t);
	HAL_StatusTypeDef mem_read(uint8_t,uint8_t,uint8_t*,uint8_t);
	HAL_StatusTypeDef mem_read(uint8_t,uint8_t,uint8_t*);
	HAL_StatusTypeDef mem_write(uint8_t,uint8_t,uint8_t*,uint8_t);
	HAL_StatusTypeDef mem_write(uint8_t,uint8_t,uint8_t);
	bool wait_mem_write(uint8_t,uint8_t,uint8_t*,uint8_t,uint8_t);
	bool wait_mem_write(uint8_t,uint8_t,uint8_t,uint8_t);
private:
	I2C_HandleTypeDef* hi2cx;
	uint32_t timeout;
	uint32_t i2c_mem_addr_size;
};




#endif /* INC_I2C_HPP_ */
