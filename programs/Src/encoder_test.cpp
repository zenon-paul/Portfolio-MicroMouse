/*
 * encoder_test.cpp
 *
 *  Created on: 2024/09/13
 *      Author: sakur
 */
#include"mouse_system_objects.hpp"

void test_encoder_count(){
	while(1){
		if(encA.count >= encA.resolution){
			ind1 = GPIO_PIN_SET;
		}
		else{
			ind1 = GPIO_PIN_RESET;
		}
		if(encB.count >= encB.resolution){
			ind2 = GPIO_PIN_SET;
		}
		else{
			ind2 = GPIO_PIN_RESET;
		}
		if(encA.count <= -encA.resolution){
			ind3 = GPIO_PIN_SET;
		}
		else{
			ind3 = GPIO_PIN_RESET;
		}
		if(encB.count <= -encB.resolution){
			ind4 = GPIO_PIN_SET;
		}
		else{
			ind4 = GPIO_PIN_RESET;
		}
	}
}



