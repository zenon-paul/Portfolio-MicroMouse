/*
 * imucontrol_test.cpp
 *
 *  Created on: 2024/09/11
 *      Author: sakur
 */
#include"mouse_system_objects.hpp"

void test_imucontrol(float rad){
	imusnccontroller.deactivate();
	HAL_Delay(100);
	imusnccontroller.set_target(rad);
	imusnccontroller.activate();
	bno055.start(OPERATION_MODE_IMUPLUS);
	while(1){
		bno055.read_eul_heading(false);
		if(imusnccontroller.is_singularity){
			ind1 = GPIO_PIN_SET;
		}
		else{
			ind1 = GPIO_PIN_RESET;
		}
	}
}

void test_imucontrol_anti(float len){
	wallctrl.deactivate();//壁無効
	imusnccontroller.deactivate();
	//-------------------------------------
	bno055.start(OPERATION_MODE_IMUPLUS);
	while(1){
		imusnccontroller.set_target(0.0f);
		imusnccontroller.activate();
		navigate_with_daike_control(&mtsdriver,&localization,1.0,0.4,0.0,len,&bno055);
		imusnccontroller.deactivate();
		navigate_to_clothoid_curve_anti(&mtsdriver,&localization,deg_rad(30),deg_rad(30),deg_rad(30),0.0f,6*M_PI,&bno055);
		//-------------------------------------
		imusnccontroller.set_target(0.5*M_PI);
		imusnccontroller.activate();
		navigate_with_daike_control(&mtsdriver,&localization,1.0,0.4,0.0,len,&bno055);
		imusnccontroller.deactivate();
		navigate_to_clothoid_curve_anti(&mtsdriver,&localization,deg_rad(30),deg_rad(30),deg_rad(30),0.0f,6*M_PI,&bno055);
		//-------------------------------------
		imusnccontroller.set_target(M_PI);
		imusnccontroller.activate();
		navigate_with_daike_control(&mtsdriver,&localization,1.0,0.4,0.0,len,&bno055);
		imusnccontroller.deactivate();
		navigate_to_clothoid_curve_anti(&mtsdriver,&localization,deg_rad(30),deg_rad(30),deg_rad(30),0.0f,6*M_PI,&bno055);
		//-------------------------------------
		imusnccontroller.set_target(-0.5*M_PI);
		imusnccontroller.activate();
		navigate_with_daike_control(&mtsdriver,&localization,1.0,0.4,0.0,len,&bno055);
		imusnccontroller.deactivate();
		navigate_to_clothoid_curve_anti(&mtsdriver,&localization,deg_rad(30),deg_rad(30),deg_rad(30),0.0f,6*M_PI,&bno055);
	}
}

void test_imucontrol_clock(float len){
	wallctrl.deactivate();//壁無効
	imusnccontroller.deactivate();
	//-------------------------------------
	bno055.start(OPERATION_MODE_IMUPLUS);
	while(1){
		imusnccontroller.set_target(0.0f);
		imusnccontroller.activate();
		navigate_with_daike_control(&mtsdriver,&localization,1.0,0.4,0.0,len,&bno055);
		imusnccontroller.deactivate();
		navigate_to_clothoid_curve_clock(&mtsdriver,&localization,deg_rad(30),deg_rad(30),deg_rad(30),0.0f,6*M_PI,&bno055);
		//-------------------------------------
		imusnccontroller.set_target(-0.5*M_PI);
		imusnccontroller.activate();
		navigate_with_daike_control(&mtsdriver,&localization,1.0,0.4,0.0,len,&bno055);
		imusnccontroller.deactivate();
		navigate_to_clothoid_curve_clock(&mtsdriver,&localization,deg_rad(30),deg_rad(30),deg_rad(30),0.0f,6*M_PI,&bno055);
		//-------------------------------------
		imusnccontroller.set_target(M_PI);
		imusnccontroller.activate();
		navigate_with_daike_control(&mtsdriver,&localization,1.0,0.4,0.0,len,&bno055);
		imusnccontroller.deactivate();
		navigate_to_clothoid_curve_clock(&mtsdriver,&localization,deg_rad(30),deg_rad(30),deg_rad(30),0.0f,6*M_PI,&bno055);
		//-------------------------------------
		imusnccontroller.set_target(0.5*M_PI);
		imusnccontroller.activate();
		navigate_with_daike_control(&mtsdriver,&localization,1.0,0.4,0.0,len,&bno055);
		imusnccontroller.deactivate();
		navigate_to_clothoid_curve_clock(&mtsdriver,&localization,deg_rad(30),deg_rad(30),deg_rad(30),0.0f,6*M_PI,&bno055);
	}
}




