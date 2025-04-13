/*
 * wallsencer_test.cpp
 *
 *  Created on: 2024/09/12
 *      Author: sakur
 */
#include"mouse_system_objects.hpp"

void test_wall_exist(){
	while(1){
	  if(sencer1.exist){
		  ind1 = GPIO_PIN_SET;
	  }
	  else{
		  ind1 = GPIO_PIN_RESET;
	  }
	  if(sencer2.exist){
		  ind2 = GPIO_PIN_SET;
	  }
	  else{
		  ind2 = GPIO_PIN_RESET;
	  }
	  if(sencer3.exist){
		  ind3 = GPIO_PIN_SET;
	  }
	  else{
		  ind3 = GPIO_PIN_RESET;
	  }
	  if(sencer4.exist){
		  ind4 = GPIO_PIN_SET;
	  }
	  else{
		  ind4 = GPIO_PIN_RESET;
	  }
	}
}

void test_wall_rigidly_exist(){
	while(1){
	  if(sencer1.rigidly_exist){
		  ind1 = GPIO_PIN_SET;
	  }
	  else{
		  ind1 = GPIO_PIN_RESET;
	  }
	  if(sencer2.rigidly_exist){
		  ind2 = GPIO_PIN_SET;
	  }
	  else{
		  ind2 = GPIO_PIN_RESET;
	  }
	  if(sencer3.rigidly_exist){
		  ind3 = GPIO_PIN_SET;
	  }
	  else{
		  ind3 = GPIO_PIN_RESET;
	  }
	  if(sencer4.rigidly_exist){
		  ind4 = GPIO_PIN_SET;
	  }
	  else{
		  ind4 = GPIO_PIN_RESET;
	  }
	}
}

void test_wall_exist2(){
	while(1){
	  if(sencer1.exist2){
		  ind1 = GPIO_PIN_SET;
	  }
	  else{
		  ind1 = GPIO_PIN_RESET;
	  }
	  if(sencer2.exist2){
		  ind2 = GPIO_PIN_SET;
	  }
	  else{
		  ind2 = GPIO_PIN_RESET;
	  }
	  if(sencer3.exist2){
		  ind3 = GPIO_PIN_SET;
	  }
	  else{
		  ind3 = GPIO_PIN_RESET;
	  }
	  if(sencer4.exist2){
		  ind4 = GPIO_PIN_SET;
	  }
	  else{
		  ind4 = GPIO_PIN_RESET;
	  }
	}
}

void test_wall_exist3(){
	while(1){
	  if(sencer1.exist3){
		  ind1 = GPIO_PIN_SET;
	  }
	  else{
		  ind1 = GPIO_PIN_RESET;
	  }
	  if(sencer2.exist3){
		  ind2 = GPIO_PIN_SET;
	  }
	  else{
		  ind2 = GPIO_PIN_RESET;
	  }
	  if(sencer3.exist3){
		  ind3 = GPIO_PIN_SET;
	  }
	  else{
		  ind3 = GPIO_PIN_RESET;
	  }
	  if(sencer4.exist3){
		  ind4 = GPIO_PIN_SET;
	  }
	  else{
		  ind4 = GPIO_PIN_RESET;
	  }
	}
}


