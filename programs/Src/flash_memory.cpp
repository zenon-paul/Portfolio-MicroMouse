/*
 * flash_memory.cpp
 *
 *  Created on: Aug 20, 2024
 *      Author: sakur
 */
#include"flash_memory.hpp"

uint32_t erase_flash(uint8_t page){//エラーを戻り値で返せ
	HAL_FLASH_Unlock();
	FLASH_EraseInitTypeDef erase_init;
	erase_init.TypeErase = FLASH_TYPEERASE_PAGES;
	erase_init.Page = page;
	erase_init.NbPages = 1;
	uint32_t erase_error = 0;
	HAL_FLASHEx_Erase(&erase_init,&erase_error);
	HAL_FLASH_Lock();
	return erase_error;

}
void write_flash(uint64_t dat,uint32_t addr,uint8_t page){
	erase_flash(page);
	HAL_FLASH_Unlock();

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,addr,dat);

	HAL_FLASH_Lock();
}
void write_flash_non_erase(uint64_t dat,uint32_t addr){
	HAL_FLASH_Unlock();

	HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,addr,dat);

	HAL_FLASH_Lock();
}

void read_flash(uint32_t addr,uint64_t* dat){
	memcpy(dat,(uint32_t*)addr,8);
}

uint32_t write_flash_float(uint32_t addr,float v1,float v2){
	  uint64_t dat = 0;

	  union floatint val1;
	  val1.fvalue = v1;
	  union floatint val2;
	  val2.fvalue = v2;

	  dat |= (uint64_t(val2.dvalue))<<32;
	  dat |= val1.dvalue;

	  write_flash_non_erase(dat,addr);

	  return addr+8;
}
uint32_t read_flash_float(uint32_t addr,float* v1,float* v2){
	  uint64_t res = 0;

	  union floatint res1;
	  res1.dvalue = 0;
	  union floatint res2;
	  res2.dvalue = 0;

	  read_flash(addr,&res);
	  res2.dvalue = uint32_t((res&0xFFFFFFFF00000000)>>32);
	  res1.dvalue = uint32_t(res&0xFFFFFFFF);
	  *v1 = res1.fvalue;
	  *v2 = res2.fvalue;

	  return addr+8;
}

uint32_t write_flash_words(uint32_t addr,uint8_t w1,uint8_t w2,uint8_t w3,uint8_t w4){
	uint64_t dat = 0;

	dat |= (uint64_t(w4))<<24;
	dat |= (uint64_t(w3))<<16;
	dat |= (uint64_t(w2))<<8;
	dat |= uint64_t(w1);

	write_flash_non_erase(dat,addr);

	return addr+8;
}

uint32_t read_flash_words(uint32_t addr,uint8_t* w1,uint8_t* w2,uint8_t* w3,uint8_t* w4){
	uint64_t res = 0;

	read_flash(addr,&res);

	*w4 = uint8_t((res>>24)&0x0000000F);
	*w3 = uint8_t((res>>16)&0x0000000F);
	*w2 = uint8_t((res>>8)&0x0000000F);
	*w1 = uint8_t(res&0x0000000F);

	return addr+8;
}

