/*
 * slalom_search.cpp
 *
 *  Created on: 2024/09/10
 *      Author: sakur
 */
#include"mouse_system_objects.hpp"
#include"wall_adjustment.hpp"
#include"search_utility.hpp"
#include"indicator_utility.hpp"
#include"grid_size.hpp"

void slalom_left(RunningParameter param){

}

void slalom_right(RunningParameter param){

}

void slalom_back(RunningParameter param){

}

void slalom_go(RunningParameter param){

}

void slalom_search(XY goal,RunningParameter param){
	  float acc_cloth_deg = 30.0f;
	  float circle_deg = 30.0f;
	  float dec_cloth_deg = 30.0f;
	  //-------------------------------------
	  float delay_time = param.delay_time;//8;
	  float FV = param.FV;//0.4;
	  float FA = param.FA;//1.0;
	  float AA = param.AA;//12*M_PI;
	  //------imu cntrl activate----------------
	  set_imusncctrl_target();
	  imusnccontroller.activate();
	  //--------------------------------
	  //-------wall ctrl activate-------
	  wallctrl.activate();
	  //--------------------------------
	  while(1){
		  float pre_milage = localization.mileage/1000.0f;//mにしろ
		  bno055.read_eul_heading(false);
		  //--------search--------------
		  update_maze(wallinfo, &maze, maze_location);//迷路情報の更新
	      uint8_t next_dir = AdatiSearch(maze, maze_location,goal);//次のマスの決定
	      //-----------------------------
	      float casting_mileage = localization.mileage/1000.0f - pre_milage;//惰行距離の算出
	  	  float turn_R = GridSize::HALF - casting_mileage;
	  	  float turn_FV = 0.0f;
	  	  if(turn_R < 0){
	  		  turn_FV = 0.0f;
	  		  casting_mileage = GridSize::HALF;//0.0ではないよ;
	  	  }
	  	  else{
	  		  //FV = (0.4f*turn_R)/0.09f;
	  		  turn_FV = (FV*turn_R)/GridSize::HALF;
	  	  }
	  	//---------------------------------------------------
	  	  switch(next_dir){
	  	  case 0:
	  		  imusnccontroller.deactivate();///無効
	  		  wallctrl.deactivate();///無効
	  		  ind1 = GPIO_PIN_SET;
	  		  maze_location.go_to(next_dir);
	  		  navigate_to_clothoid_curve_anti(&mtsdriver,&localization,deg_rad(acc_cloth_deg),deg_rad(circle_deg),deg_rad(dec_cloth_deg),turn_FV,AA,&bno055);
	  		  set_imusncctrl_target();
	  		  imusnccontroller.activate();///有効
	  		  go_forward(&mtsdriver,&localization,FV,casting_mileage,&bno055);
	  		  ///navigate_with_daike_control(&mtsdriver, &localization,FA,FV,FV,casting_milage,&bno055);
	  		  HAL_Delay(delay_time);
	  		  wallctrl.activate();///有効
	  		  break;
	  	  case 1:
	  		  ind2 = GPIO_PIN_SET;
	  		  imusnccontroller.deactivate();///無効
	  		  wallctrl.deactivate();///無効
	  		  maze_location.go_to(next_dir);
	  		  navigate_to_clothoid_curve_clock(&mtsdriver,&localization,deg_rad(acc_cloth_deg),deg_rad(circle_deg),deg_rad(dec_cloth_deg),turn_FV,AA,&bno055);
	  		  set_imusncctrl_target();
	  		  imusnccontroller.activate();///有効
	  		  go_forward(&mtsdriver,&localization,FV,casting_mileage,&bno055);
	  		  ///navigate_with_daike_control(&mtsdriver, &localization,FA,FV,FV,casting_milage,&bno055);
	  		  HAL_Delay(delay_time);
	  		  wallctrl.activate();///有効
	  		  break;
	  	  case 2:
				ind3 = GPIO_PIN_SET;
				navigate_with_daike_control(&mtsdriver, &localization,FA,FV,0.0,GridSize::HALF-casting_mileage,&bno055);
				imusnccontroller.deactivate();///無効
				maze_location.go_to(next_dir);
				wallctrl.deactivate();//無効
				if(bno055.continuous_rad <= 0){
					navigate_to_clothoid_curve_anti(&mtsdriver,&localization,deg_rad(40.0),deg_rad(100.0),deg_rad(40.0),0.0,AA,&bno055);
				}
				else{
					navigate_to_clothoid_curve_clock(&mtsdriver,&localization,deg_rad(40.0),deg_rad(100.0),deg_rad(40.0),0.0,AA,&bno055);
				}
				adjust_with_walltouch(param);
				wallctrl.activate();//有効
				set_imusncctrl_target();
				imusnccontroller.activate();///有効
				navigate_with_daike_control(&mtsdriver,&localization,FA,FV,FV,GridSize::HALF,&bno055);
				break;
	  	  case 3:
	  		  imusnccontroller.deactivate();///無効
	  		  ind4 = GPIO_PIN_SET;
	  		  maze_location.go_to(next_dir);
	  		  go_forward(&mtsdriver,&localization,FV,GridSize::FULL-casting_mileage,&bno055);
	  		  ///navigate_with_daike_control(&mtsdriver, &localization,FA,FV,FV,GridSize::FULL-casting_milage,&bno055);
	  		  set_imusncctrl_target();
	  		  imusnccontroller.activate();///有効
	  		  break;
	  	  default:
	  		  tika1();
	  		  break;
	  	  }
		  ind1 = GPIO_PIN_RESET;
		  ind2 = GPIO_PIN_RESET;
		  ind3 = GPIO_PIN_RESET;
		  ind4 = GPIO_PIN_RESET;
		  if(maze_location.glb_mylocation == goal){//ゴールで停止
		      //navigate_with_daike_control(&mtsdriver,&localization,1.0,0.4,0.0,0.09,&bno055);
		  	  break;
		  }
	  }
	  imusnccontroller.deactivate();///無効
	  wallctrl.deactivate();///無効
	  mtsdriver.set_target_forward_velocity(0.0f);
}


