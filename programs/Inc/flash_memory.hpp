/*
 * flash_memory.hpp
 *
 *  Created on: Aug 20, 2024
 *      Author: sakur
 */

#ifndef INC_FLASH_MEMORY_HPP_
#define INC_FLASH_MEMORY_HPP_
#include<stm32g4xx.h>
#include<stm32g431xx.h>
#include<stm32g4xx_hal_flash.h>
#include<string.h>
#include<stdint.h>

#define PAGE61START_ADDR (0x0801E800)
#define PAGE61END_ADDR (0x0801EFFF)
#define PAGE62START_ADDR (0x0801F000)
#define PAGE62END_ADDR (0x0801F7FF)
#define PAGE63START_ADDR (0x0801F800)
#define PAGE63END_ADDR (0x0801FFFF)
#define DOUBLE_WORD (64)
#define HALF_WORD (32)

union floatint{
	uint32_t dvalue;
	float fvalue;
};

uint32_t erase_flash(uint8_t page);
void write_flash(uint64_t dat,uint32_t addr,uint8_t page);
void write_flash_non_erase(uint64_t dat,uint32_t addr);
void read_flash(uint32_t addr,uint64_t* dat);
uint32_t write_flash_float(uint32_t addr,float v1,float v2);
uint32_t read_flash_float(uint32_t addr,float* v1,float* v2);
uint32_t write_flash_words(uint32_t addr,uint8_t w1,uint8_t w2,uint8_t w3,uint8_t w4);
uint32_t read_flash_words(uint32_t addr,uint8_t* w1,uint8_t* w2,uint8_t* w3,uint8_t* w4);
#endif /* INC_FLASH_MEMORY_HPP_ */
