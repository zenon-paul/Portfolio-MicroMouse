/*
 * imusencer_test.cpp
 *
 *  Created on: 2024/09/11
 *      Author: sakur
 */
#include"math.h"
#include"mouse_system_objects.hpp"

void test_rad(){
	while(1){
		bno055.read_eul_heading(false);
		if(bno055.rad < -0.5*M_PI){
			ind1 = GPIO_PIN_SET;
		}
		else{
			ind1 = GPIO_PIN_RESET;
		}
		if((-0.5*M_PI <= bno055.rad) && (bno055.rad < 0) ){
			ind2 = GPIO_PIN_SET;
		}
		else{
			ind2 = GPIO_PIN_RESET;
		}
		if((0 <= bno055.rad) && (bno055.rad < 0.5*M_PI)){
			ind3 = GPIO_PIN_SET;
		}
		else{
			ind3 = GPIO_PIN_RESET;
		}
		if(0.5*M_PI <= bno055.rad){
			ind4 = GPIO_PIN_SET;
		}
		else{
			ind4 = GPIO_PIN_RESET;
		}
	}
}

/*void test_deg(){
	while(1){
		bno055.read_eul_heading(false);
		if(bno055.deg < -90.0f){
			ind1 = GPIO_PIN_SET;
		}
		else{
			ind1 = GPIO_PIN_RESET;
		}
		if((-90.0f <= bno055.deg) && (bno055.deg < 0.0f) ){
			ind2 = GPIO_PIN_SET;
		}
		else{
			ind2 = GPIO_PIN_RESET;
		}
		if((0.0f <= bno055.deg) && (bno055.deg < 90.0f)){
			ind3 = GPIO_PIN_SET;
		}
		else{
			ind3 = GPIO_PIN_RESET;
		}
		if(90.0f <= bno055.deg){
			ind4 = GPIO_PIN_SET;
		}
		else{
			ind4 = GPIO_PIN_RESET;
		}
	}
}*/

void test_continuous_rad(){
	while(1){
		bno055.read_eul_heading(false);
		if(bno055.continuous_rad < -1.5*M_PI){
			ind1 = GPIO_PIN_SET;
		}
		else{
			ind1 = GPIO_PIN_RESET;
		}
		if(bno055.continuous_rad < -0.5*M_PI){
			ind2 = GPIO_PIN_SET;
		}
		else{
			ind2 = GPIO_PIN_RESET;
		}
		if(bno055.continuous_rad > 0.5*M_PI){
			ind3 = GPIO_PIN_SET;
		}
		else{
			ind3 = GPIO_PIN_RESET;
		}
		if(bno055.continuous_rad > 1.5*M_PI){
			ind4 = GPIO_PIN_SET;
		}
		else{
			ind4 = GPIO_PIN_RESET;
		}
	}
}

void test_original_rad(){
	while(1){
		bno055.read_eul_heading(false);
		if(0.0f < bno055.original_rad){
			ind1 = GPIO_PIN_SET;
		}
		else{
			ind1 = GPIO_PIN_RESET;
		}
		if(0.5*M_PI < bno055.original_rad){
			ind2 = GPIO_PIN_SET;
		}
		else{
			ind2 = GPIO_PIN_RESET;
		}
		if(M_PI < bno055.original_rad){
			ind3 = GPIO_PIN_SET;
		}
		else{
			ind3 = GPIO_PIN_RESET;
		}
		if(1.5*M_PI < bno055.original_rad){
			ind4 = GPIO_PIN_SET;
		}
		else{
			ind4 = GPIO_PIN_RESET;
		}
	}
}

/*void test_original_deg(){
	while(1){
		bno055.read_eul_heading(false);
		if(0.0f < bno055.original_deg){
			ind1 = GPIO_PIN_SET;
		}
		else{
			ind1 = GPIO_PIN_RESET;
		}
		if(90.0f < bno055.original_deg){
			ind2 = GPIO_PIN_SET;
		}
		else{
			ind2 = GPIO_PIN_RESET;
		}
		if(180.0f < bno055.original_deg){
			ind3 = GPIO_PIN_SET;
		}
		else{
			ind3 = GPIO_PIN_RESET;
		}
		if(270.0f < bno055.original_deg){
			ind4 = GPIO_PIN_SET;
		}
		else{
			ind4 = GPIO_PIN_RESET;
		}
	}
}*/



