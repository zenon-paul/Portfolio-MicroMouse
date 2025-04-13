/*
 * search_utility.cpp
 *
 *  Created on: 2024/09/12
 *      Author: sakur
 */
#include"mouse_system_objects.hpp"
#include"search_utility.hpp"
#include"wall_adjustment.hpp"

uint16_t get_motion_list_cost(std::vector<uint8_t> motion_list){
	uint16_t score = 0;
	for(uint8_t motion : motion_list){
		if(2 == motion)score += 3;
		else if(0 == motion)score += 2;
		else if(1 == motion)score += 2;
		else score += 0;
	}
	return score;
}

uint8_t convert_direction(MazeLocation ml,XY to){
	XY glb_dir_vec = to - ml.glb_mylocation;
	uint8_t lcl_dir = 0;
	for (int i = 0; i < 4; i++) {
		if (directions[i] == glb_dir_vec) {
			lcl_dir = ml.convert_dir_glb2lcl(i);
			break;
		}
	}
	return lcl_dir;
}

std::vector<uint8_t> convert_grid_to_motion(MazeLocation initial_loc,std::vector<XY> route){
	if(route.empty()){
		return std::vector<uint8_t>(0,0);
	}
	if(initial_loc.glb_mylocation != route[0]){
		return std::vector<uint8_t>(0,0);
	}
	std::vector<uint8_t> motion_list;
	MazeLocation loc = initial_loc;

	for(int i = 1;i < static_cast<int>(route.size());i++){
		if(is_in_goal_area(loc))break;
		uint8_t motion = loc.detect_next_motion(route[i]);
		if((4 == motion) || (5 == motion))continue;
		motion_list.push_back(motion);
		loc.go_to(motion);
	}
	return motion_list;
}

void set_imusncctrl_target(){
	switch(maze_location.glb_forward_dir){
	case 0:
		imusnccontroller.set_target(0.5*M_PI);
		break;
	case 1:
		imusnccontroller.set_target(-0.5*M_PI);
		break;
	case 2:
		imusnccontroller.set_target(M_PI);
		break;
	case 3:
		imusnccontroller.set_target(0.0f);
		break;
	default:
		break;
	}
}

void set_imusncctrl_target(uint8_t dir){
	uint8_t glb_d = maze_location.convert_dir_lcl2lglb(dir);
	switch(glb_d){
	case 0:
		imusnccontroller.set_target(0.5*M_PI);
		break;
	case 1:
		imusnccontroller.set_target(-0.5*M_PI);
		break;
	case 2:
		imusnccontroller.set_target(M_PI);
		break;
	case 3:
		imusnccontroller.set_target(0.0f);
		break;
	default:
		break;
	}
}

bool is_in_goal_area(){
	for(auto xy : Goals){
		if(xy == maze_location.glb_mylocation){
			return true;
		}
	}
	return false;
}

bool is_in_goal_area(MazeLocation ml){
	for(auto xy : Goals){
		if(xy == ml.glb_mylocation){
			return true;
		}
	}
	return false;
}

std::vector<XY> prepare_for_second_search(RunningParameter param){//ゴールのいずれかのマスにいることが前提
	std::vector<XY> route;
	route.push_back(maze_location.glb_mylocation);
	//--------------------------------
	imusnccontroller.deactivate();
	wallctrl.deactivate();
//-------------------------------
	float FV = param.FV;
	float AA = param.AA;
	float delay_time = param.delay_time;
//-------------------------------
	update_maze(wallinfo,&maze,maze_location);
	uint8_t wall_lcl0 = maze.get_wall_status_xyd(maze_location.glb_mylocation,maze_location.convert_dir_lcl2lglb(0));
	uint8_t wall_lcl1 = maze.get_wall_status_xyd(maze_location.glb_mylocation,maze_location.convert_dir_lcl2lglb(1));
	uint8_t wall_lcl3 = maze.get_wall_status_xyd(maze_location.glb_mylocation,maze_location.convert_dir_lcl2lglb(3));
	//ゴールした時右左どちらに壁があるかで決めよう（ないときは指定する）
	if(wall_lcl0 == WALL_SEEN){//左手に壁がある
		while(wall_lcl0 == WALL_SEEN){
			if(wall_lcl3 == WALL_SEEN){//前に壁
				maze_location.go_to(1);
				adjust_with_wallsencer_non_back(param);
				HAL_Delay(delay_time);
				navigate_to_clothoid_curve_clock(&mtsdriver,&localization,deg_rad(30),deg_rad(30),deg_rad(30),0.0,AA,&bno055);
				HAL_Delay(delay_time);
				adjust_with_walltouch(param);
				wallctrl.activate();
				go_forward_simple(&mtsdriver,&localization,FV,GridSize::HALF,&bno055);
				wallctrl.deactivate();
				///navigate_with_daike_control(&mtsdriver,&localization,1.0,0.4,0.0,0.09,&bno055);
			}
			else{//前に壁なし
				maze_location.go_to(3);
				wallctrl.activate();
				set_imusncctrl_target();
				//imusnccontroller.activate();//20240927
				go_forward_simple(&mtsdriver,&localization,FV,GridSize::FULL,&bno055);
				imusnccontroller.deactivate();
				wallctrl.deactivate();
				///navigate_with_daike_control(&mtsdriver,&localization,1.0,0.4,0.0,0.18,&bno055);
			}
			//-------
			//--------------------
			route.push_back(maze_location.glb_mylocation);
			//--------------------
			update_maze(wallinfo,&maze,maze_location);
			wall_lcl0 = maze.get_wall_status_xyd(maze_location.glb_mylocation,maze_location.convert_dir_lcl2lglb(0));
			wall_lcl1 = maze.get_wall_status_xyd(maze_location.glb_mylocation,maze_location.convert_dir_lcl2lglb(1));
			wall_lcl3 = maze.get_wall_status_xyd(maze_location.glb_mylocation,maze_location.convert_dir_lcl2lglb(3));
			//--------
			if(is_in_goal_area() == false){//エリア外に出た
				break;
			}
		}
	}
	else{//
		while(wall_lcl1 == WALL_SEEN){
			if(wall_lcl3 == WALL_SEEN){//前壁有り
				maze_location.go_to(0);
				adjust_with_wallsencer_non_back(param);
				HAL_Delay(delay_time);
				navigate_to_clothoid_curve_anti(&mtsdriver,&localization,deg_rad(30),deg_rad(30),deg_rad(30),0.0,AA,&bno055);
				HAL_Delay(delay_time);
				adjust_with_walltouch(param);
				wallctrl.activate();
				go_forward_simple(&mtsdriver,&localization,FV,GridSize::HALF,&bno055);
				wallctrl.deactivate();
				///navigate_with_daike_control(&mtsdriver,&localization,1.0,0.4,0.0,GridSize::HALF,&bno055);
			}
			else{//無し
				maze_location.go_to(3);
				wallctrl.activate();
				set_imusncctrl_target();
				//imusnccontroller.activate();//20240927
				go_forward_simple(&mtsdriver,&localization,FV,GridSize::FULL,&bno055);
				imusnccontroller.deactivate();
				wallctrl.deactivate();
				///navigate_with_daike_control(&mtsdriver,&localization,1.0,0.4,0.0,GridSize::FULL,&bno055);
			}
			//--------------------
			route.push_back(maze_location.glb_mylocation);
			//--------------------
			//-------
			update_maze(wallinfo,&maze,maze_location);
			wall_lcl0 = maze.get_wall_status_xyd(maze_location.glb_mylocation,maze_location.convert_dir_lcl2lglb(0));
			wall_lcl1 = maze.get_wall_status_xyd(maze_location.glb_mylocation,maze_location.convert_dir_lcl2lglb(1));
			wall_lcl3 = maze.get_wall_status_xyd(maze_location.glb_mylocation,maze_location.convert_dir_lcl2lglb(3));
			//--------
			if(is_in_goal_area() == false){
				break;
			}
		}
	}
	return route;
}

const MazeRoute& compare(const MazeRoute& a,const MazeRoute& b){
	return a;//一時的に
}


