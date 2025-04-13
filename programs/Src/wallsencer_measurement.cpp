/*
 * wallsencer_measurement.cpp
 *
 *  Created on: 2024/09/10
 *      Author: sakur
 */
#include"mouse_system_objects.hpp"
#include"indicator_utility.hpp"

void set_threshold(){//THRESHOLDS_ADDR+0,THRESHOLDS_ADDR+8
	wallinfo.calculate_side_threshold(1000);
	HAL_Delay(100);
	tika1();
	HAL_Delay(10000);
	tika1();
	HAL_Delay(100);
	wallinfo.calculate_forward_threshold(1000);
	HAL_Delay(1000);
	///erase_flash(63);
	wallinfo.register_threshold(THRESHOLDS_ADDR);
}

void register_forward_threshold_full_grid(){
	tika1();
	float t1 = sencer1.calculate_threshold2(1000);
	float t4 = sencer4.calculate_threshold2(1000);
	tika1();
	write_flash_float(THRESHOLDS_ADDR+16,t1,t4);
}


void register_forward_threshold_half_grid(){
	tika1();
	float t1 = sencer1.calculate_threshold3(1000);
	float t4 = sencer4.calculate_threshold3(1000);
	tika1();
	write_flash_float(THRESHOLDS_ADDR+24,t1,t4);
}

void load_forward_threshold_full_grid(){
	float t1 = 0.0f;
	float t4 = 0.0f;
	read_flash_float(THRESHOLDS_ADDR+16,&t1,&t4);
	sencer1.threshold2 = t1;
	sencer4.threshold2 = t4;
}

void load_forward_threshold_half_grid(){
	float t1 = 0.0f;
	float t4 = 0.0f;
	read_flash_float(THRESHOLDS_ADDR+24,&t1,&t4);
	sencer1.threshold3 = t1;
	sencer4.threshold3 = t4;
}

