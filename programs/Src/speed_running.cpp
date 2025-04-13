/*
 * speed_running.cpp
 *
 *  Created on: 2024/09/13
 *      Author: sakur
 */
#include"mouse_system_objects.hpp"
#include<vector>
#include"search_utility.hpp"
#include"indicator_utility.hpp"
#include"wall_adjustment.hpp"

void speed_run(RunningParameter go_param,std::vector<uint8_t> motion_list){
	float FV = go_param.FV;
	float FA = go_param.FA;
	float AA = go_param.AA;
	float delay_time = go_param.delay_time;
	wallctrl.deactivate();
	imusnccontroller.deactivate();
	//-----------------------------加速
	adjust_with_walltouch(go_param);
	navigate_with_daike_control(&mtsdriver,&localization,FA,FV,FV,GridSize::HALF,&bno055);
	for(uint8_t next_motion:motion_list){
		switch(next_motion){
			case 0:
				maze_location.go_to(0);
				navigate_to_clothoid_curve_anti(&mtsdriver,&localization,deg_rad(30),deg_rad(30),deg_rad(30),FV,AA,&bno055);
				break;
			case 1:
				maze_location.go_to(1);
				navigate_to_clothoid_curve_clock(&mtsdriver,&localization,deg_rad(30),deg_rad(30),deg_rad(30),FV,AA,&bno055);
				break;
			case 2:
				navigate_with_daike_control(&mtsdriver,&localization,FA,FV,0.0,GridSize::HALF,&bno055);
				maze_location.go_to(2);
				HAL_Delay(delay_time);
				if(bno055.continuous_rad <= 0){
					navigate_to_clothoid_curve_anti(&mtsdriver,&localization,deg_rad(40.0),deg_rad(100.0),deg_rad(40.0),0.0,AA,&bno055);
				}
				else{
					navigate_to_clothoid_curve_clock(&mtsdriver,&localization,deg_rad(40.0),deg_rad(100.0),deg_rad(40.0),0.0,AA,&bno055);
				}
				set_imusncctrl_target();
				wallctrl.activate();
				imusnccontroller.activate();
				HAL_Delay(delay_time);
				navigate_with_daike_control(&mtsdriver,&localization,FA,FV,FV,GridSize::HALF,&bno055);
				wallctrl.deactivate();
				imusnccontroller.deactivate();
				break;
			case 3:
				maze_location.go_to(3);
				set_imusncctrl_target();
				wallctrl.activate();
				imusnccontroller.activate();
				navigate_with_daike_control(&mtsdriver,&localization,FA,FV,FV,GridSize::FULL,&bno055);
				//go_forward(&mtsdriver,&localization,FV,GridSize::FULL,&bno055);
				wallctrl.deactivate();
				imusnccontroller.deactivate();
				break;
			default:
				break;
		}
	}
	navigate_with_daike_control(&mtsdriver,&localization,FA,FV,0.0f,GridSize::HALF,&bno055);
	mtsdriver.set_target_angular_acceleration(0.0);
	mtsdriver.set_target_angular_velocity(0.0);
	mtsdriver.set_target_forward_acceleration(0.0);
	mtsdriver.set_target_forward_velocity(0.0);
	wallctrl.deactivate();
	imusnccontroller.deactivate();
	start_func();
}

