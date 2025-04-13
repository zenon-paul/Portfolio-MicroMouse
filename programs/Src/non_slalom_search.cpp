/*
 * non_slalom_search.cpp
 *
 *  Created on: 2024/09/10
 *      Author: sakur
 */
#include"mouse_system_objects.hpp"
#include"wall_adjustment.hpp"
#include"search_utility.hpp"
#include"indicator_utility.hpp"
#include"grid_size.hpp"
#include"maze_route.hpp"
#include"turn_angle_parameters.hpp"

using TA = TurnAngles;

void non_slalom_left(RunningParameter param){//0
	  //-----------------------------------
	  float delay_time = param.delay_time;
	  float FV = param.FV;
	  float FA = param.FA;
	  float AA = param.AA;
	  //----------------------------------------
		//wallctrl.deactivate();
		if(maze.get_wall_status_xyd(maze_location.glb_mylocation,maze_location.glb_forward_dir) == WALL_OFF){//wall off
			go_forward_simple(&mtsdriver,&localization,FV,GridSize::HALF,&bno055);
		}
		else{
			adjust_with_wallsencer_non_back(param);
		}
		wallctrl.deactivate();//無効
		imusnccontroller.deactivate();///無効
		maze_location.go_to(0);
		HAL_Delay(delay_time);
		navigate_to_clothoid_curve_anti(&mtsdriver, &localization,deg_rad(TA::TURN90_FIRST_DEG),deg_rad(TA::TURN90_MIDD_DEG),deg_rad(TA::TURN90_LAST_DEG),0.0f,AA,&bno055);
		HAL_Delay(delay_time);
		set_imusncctrl_target();
		imusnccontroller.activate();///有効
		wallctrl.activate();//有効
		go_forward_simple(&mtsdriver,&localization,FV,GridSize::HALF,&bno055);
		//wallctrl.activate();
}

void non_slalom_right(RunningParameter param){//1
	  //-----------------------------------
	  float delay_time = param.delay_time;
	  float FV = param.FV;
	  float FA = param.FA;
	  float AA = param.AA;
	  //----------------------------------------
		//wallctrl.deactivate();
		if(maze.get_wall_status_xyd(maze_location.glb_mylocation,maze_location.glb_forward_dir) == WALL_OFF){//wall off
			go_forward_simple(&mtsdriver,&localization,FV,GridSize::HALF,&bno055);
		}
		else{
			adjust_with_wallsencer_non_back(param);
		}
		wallctrl.deactivate();//無効
		imusnccontroller.deactivate();///無効
		maze_location.go_to(1);
		HAL_Delay(delay_time);
		navigate_to_clothoid_curve_clock(&mtsdriver, &localization,deg_rad(TA::TURN90_FIRST_DEG),deg_rad(TA::TURN90_MIDD_DEG),deg_rad(TA::TURN90_LAST_DEG),0.0f,AA,&bno055);
		HAL_Delay(delay_time);
		set_imusncctrl_target();
		imusnccontroller.activate();///有効
		wallctrl.activate();//有効
		go_forward_simple(&mtsdriver,&localization,FV,GridSize::HALF,&bno055);
		//wallctrl.activate();
}

void non_slalom_back(RunningParameter param){//2
	  //-----------------------------------
	  float delay_time = param.delay_time;
	  float FV = param.FV;
	  float FA = param.FA;
	  float AA = param.AA;
	  //----------------------------------------
	    go_forward_simple(&mtsdriver,&localization,FV,GridSize::HALF,&bno055);
	    wallctrl.deactivate();//無効
	    imusnccontroller.deactivate();///無効
		HAL_Delay(delay_time);
		maze_location.go_to(2);
		HAL_Delay(delay_time);
		if(bno055.continuous_rad <= 0){
			navigate_to_clothoid_curve_anti(&mtsdriver,&localization,deg_rad(TA::TURN180_FIRST_DEG),deg_rad(TA::TURN180_MIDD_DEG),deg_rad(TA::TURN180_LAST_DEG),0.0,AA,&bno055);
		}
		else{
			navigate_to_clothoid_curve_clock(&mtsdriver,&localization,deg_rad(TA::TURN180_FIRST_DEG),deg_rad(TA::TURN180_MIDD_DEG),deg_rad(TA::TURN180_LAST_DEG),0.0,AA,&bno055);
		}
		HAL_Delay(delay_time);
		adjust_with_walltouch(param);
		if(maze_location.glb_forward_dir == 3){
			bno055.start(OPERATION_MODE_IMUPLUS);
		}
		set_imusncctrl_target();
		imusnccontroller.activate();///有効
		wallctrl.activate();//有効
		go_forward_simple(&mtsdriver,&localization,FV,GridSize::HALF,&bno055);
}

void non_slalom_go(RunningParameter param){//3
	  //-----------------------------------
	  float delay_time = param.delay_time;
	  float FV = param.FV;
	  float FA = param.FA;
	  float AA = param.AA;
	  //----------------------------------------
		//imusnccontroller.deactivate();///無効
		maze_location.go_to(3);
		go_forward_simple(&mtsdriver,&localization,FV,GridSize::FULL,&bno055);
		set_imusncctrl_target();
		//imusnccontroller.activate();///有効
}


MazeRoute non_slalom_search(XY goal,RunningParameter param){
//	uint32_t next_addr = PAGE62START_ADDR;
	//---------------------------------------
	MazeRoute route;//route
	route.push(maze_location.glb_mylocation);
	//------imu　ctrl activate----------------
	set_imusncctrl_target();
	imusnccontroller.activate();///有効
	//--------------------------------
	//------wall ctrl activate--------
	wallctrl.activate();
	//--------------------------------
	while (1)
	{
		bno055.read_eul_heading(false);
		//------search--------
		//-----------------------
		update_maze(wallinfo, &maze, maze_location);//迷路情報の更新
		uint8_t next_dir = AdatiSearch(maze, maze_location,goal);//次のマスの決定
		//-----------------------経路記憶のため追記-----------------------
		maze.set_cell_status_xy(maze_location.glb_mylocation,CELL_PATH);
		//-------------------------------------------------------------
		uint8_t w0 = maze.get_wall_status_xyd(maze_location.glb_mylocation,maze_location.convert_dir_lcl2lglb(0));
		uint8_t w1 = maze.get_wall_status_xyd(maze_location.glb_mylocation,maze_location.convert_dir_lcl2lglb(1));
		uint8_t w3 = maze.get_wall_status_xyd(maze_location.glb_mylocation,maze_location.convert_dir_lcl2lglb(3));
		switch(next_dir){
		case 0:
			ind1 = GPIO_PIN_SET;
			non_slalom_left(param);
			break;
		case 1:
			ind2 = GPIO_PIN_SET;
			non_slalom_right(param);
			break;
		case 2:
			ind3 = GPIO_PIN_SET;
			//--------------------------------------------------------------
			if((w0 == WALL_SEEN) && (w1 == WALL_SEEN) && (w3 == WALL_SEEN)){
				maze.set_cell_status_xy(maze_location.glb_mylocation,CELL_CLOSE);
			}
			else{
				maze.set_cell_status_xy(maze_location.glb_mylocation,CELL_OPEN);
			}
			//--------------------------------------------------------------
			non_slalom_back(param);
			break;
		case 3:
			ind4 = GPIO_PIN_SET;
			non_slalom_go(param);
			break;
		default:
			tika1();
			break;
		}
		ind1 = GPIO_PIN_RESET;
		ind2 = GPIO_PIN_RESET;
		ind3 = GPIO_PIN_RESET;
		ind4 = GPIO_PIN_RESET;

		if(maze.get_cell_status_xy(maze_location.glb_mylocation) == CELL_PATH){
			route.pop();
		}
		else{
			route.push(maze_location.glb_mylocation);
		}

		if(maze_location.glb_mylocation == goal){//ゴールで停止
			break;
		}
	}
	imusnccontroller.deactivate();///無効
	wallctrl.deactivate();///無効
	mtsdriver.set_target_angular_acceleration(0.0);
	mtsdriver.set_target_angular_velocity(0.0);
	mtsdriver.set_target_forward_acceleration(0.0);
	mtsdriver.set_target_forward_velocity(0.0f);
	return route;
}



