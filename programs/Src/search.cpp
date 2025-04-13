/*
 * search.cpp
 *
 *  Created on: 2024/09/15
 *      Author: sakur
 */
#include"mouse_system_objects.hpp"
#include"non_slalom_search_mode.hpp"
#include"wall_adjustment.hpp"
#include"search_utility.hpp"
#include"turn_angle_parameters.hpp"
#include<vector>
#include<iterator>

using TA = TurnAngles;

//マウスクラス作れば良かったな
std::vector<uint8_t> search(RunningParameter param){
	adjust_with_walltouch(param);
	bno055.start(OPERATION_MODE_IMUPLUS);
	//----------------------------------
	MazeRoute forward;
	MazeRoute backward;
	std::vector<XY> forward_;
	std::vector<XY> goal_area;
	std::vector<XY> backward_;
	//------search----------------------
	//------0 step-----------
	//forward.push(maze_location.glb_mylocation);///スタートpush
	maze.set_cell_status_xy(maze_location.glb_mylocation,CELL_CLOSE);
	maze_location.go_to(3);//位置情報の更新
	navigate_with_daike_control(&mtsdriver, &localization,param.FA,param.FV,0.0,GridSize::HALF,&bno055);//始めの区画はまず進んでよし
	//forward.push(maze_location.glb_mylocation);
	//----------------------------
	forward = non_slalom_search(goal_representative,param);
    goal_area = prepare_for_second_search(param);
    maze.set_zero_cell_status();////////
	backward = non_slalom_search(Start,param);
	maze.set_zero_cell_status();////////
	imusnccontroller.activate();
	wallctrl.activate();
	adjust_with_wallsencer_non_back(param);
	wallctrl.deactivate();
	imusnccontroller.deactivate();
	if(bno055.continuous_rad <= 0){
		navigate_to_clothoid_curve_anti(&mtsdriver,&localization,deg_rad(TA::TURN180_FIRST_DEG),deg_rad(TA::TURN180_MIDD_DEG),deg_rad(TA::TURN180_LAST_DEG),0.0,param.AA,&bno055);
	}
	else{
		navigate_to_clothoid_curve_clock(&mtsdriver,&localization,deg_rad(TA::TURN180_FIRST_DEG),deg_rad(TA::TURN180_MIDD_DEG),deg_rad(TA::TURN180_LAST_DEG),0.0,param.AA,&bno055);
	}
	adjust_with_walltouch(param);//003
	maze_location.glb_forward_dir = 3;
	//--------------------------
	indicators.turn_on_all();
	HAL_Delay(500);
	indicators.turn_off_all();
	HAL_Delay(500);
	//--------------------------
	//-----prosedure------------
	//--------------------------
	forward.reverse();
	forward_.push_back(XY{0,0});
	while(!forward.empty()){
		forward_.push_back(forward.pop());
	}
	//--------------------------
	while(!backward.empty()){
		backward_.push_back(backward.pop());
	}
	while(!goal_area.empty()){
		backward_.push_back(goal_area.back());
		goal_area.pop_back();
	}
	std::vector<uint8_t> f_motion_list = convert_grid_to_motion(maze_location,forward_);
	std::vector<uint8_t> b_motion_list = convert_grid_to_motion(maze_location,backward_);
	uint16_t f_cost = get_motion_list_cost(f_motion_list);
	uint16_t b_cost = get_motion_list_cost(b_motion_list);
	if(f_cost < b_cost){
		std::vector<uint8_t> route(f_motion_list.size()-1);
		std::copy(f_motion_list.begin()+1,f_motion_list.end(),route.begin());
		return route;
	}
	else {
		std::vector<uint8_t> route(b_motion_list.size()-1);
		std::copy(b_motion_list.begin()+1,b_motion_list.end(),route.begin());
		return route;
	}
	//--------------------------

	//------check route---------
	/*erase_flash(62);
	uint32_t next_addr = PAGE62START_ADDR;
	for(XY xy:forward_){
		next_addr = write_flash_words(next_addr,0,0,xy.x,xy.y);
	}
	next_addr = write_flash_words(next_addr,0,0,15,15);
	for(XY xy:backward_){
		next_addr = write_flash_words(next_addr,0,0,xy.x,xy.y);
	}
	next_addr = write_flash_words(next_addr,0,0,15,15);
	//------------------------------
	next_addr = write_flash_words(next_addr,0,maze_location.glb_forward_dir,maze_location.glb_mylocation.x,maze_location.glb_mylocation.y);
	next_addr = write_flash_words(next_addr,0,0,15,15);

	for(uint8_t motion:f_motion_list){
		next_addr = write_flash_words(next_addr,0,0,0,motion);
	}
	next_addr = write_flash_words(next_addr,0,0,15,15);
	for(uint8_t motion:b_motion_list){
		next_addr = write_flash_words(next_addr,0,0,0,motion);
	}
	next_addr = write_flash_words(next_addr,0,0,15,15);

	next_addr = write_flash_words(next_addr,0,0,f_cost,b_cost);
	next_addr = write_flash_words(next_addr,15,15,15,15);*/
}



