/*
 * wall_adjustment.cpp
 *
 *  Created on: 2024/09/10
 *      Author: sakur
 */
#include"mouse_system_objects.hpp"

void adjust_with_wallsencer(RunningParameter param){
	float FV = param.FV;

	mtsdriver.deactivate();

	left_ctrl.set_target(-FV);
	right_ctrl.set_target(FV);

	HAL_Delay(1000);

	left_ctrl.set_target(0.0);
	right_ctrl.set_target(0.0);

	HAL_Delay(100);

	left_ctrl.set_target(FV);
	right_ctrl.set_target(-FV);

	bool left_moving = true;
	bool right_moving = true;

	while(left_moving || right_moving){
		bno055.read_eul_heading(false);
		if(left_moving && sencer1.exist3){
			left_ctrl.set_target(0.0);
			left_moving = false;
		}
		if(right_moving && sencer4.exist3){
			right_ctrl.set_target(0.0);
			right_moving = false;
		}
		HAL_Delay(50);
	}
	mtsdriver.activate();
}

void adjust_with_wallsencer_non_back(RunningParameter param){
	float FV = param.FV;

	mtsdriver.deactivate();

	left_ctrl.set_target(FV);
	right_ctrl.set_target(-FV);

	bool left_moving = true;
	bool right_moving = true;

	while(left_moving || right_moving){
		bno055.read_eul_heading(false);
		if(left_moving && sencer1.exist3){
			left_ctrl.set_target(0.0);
			left_moving = false;
		}
		else if(!left_moving && !sencer1.exist3){
			left_ctrl.set_target(FV);
			left_moving = true;
		}
		if(right_moving && sencer4.exist3){
			right_ctrl.set_target(0.0);
			right_moving = false;
		}
		else if(!right_moving && !sencer4.exist3){
			right_ctrl.set_target(-FV);
			right_moving = true;
		}
	}
	left_ctrl.set_target(0.0);
	right_ctrl.set_target(0.0);
	mtsdriver.activate();
}

void adjust_with_walltouch(RunningParameter param){
	float FV = 0.15;//param.FV;速すぎなので

	mtsdriver.set_target_forward_velocity(-FV);

	HAL_Delay(1200);

	mtsdriver.set_target_forward_velocity(0.0f);

	HAL_Delay(100);

	mtsdriver.set_target_forward_velocity(FV);

	float pre_milage = localization.mileage/1000.0;
	while((localization.mileage/1000.0 - pre_milage)<(0.09-BodyParameters::CENTER_TAIL_DIST/1000.0)){
		bno055.read_eul_heading(false);
	}

	mtsdriver.set_target_forward_velocity(0.0f);
}


