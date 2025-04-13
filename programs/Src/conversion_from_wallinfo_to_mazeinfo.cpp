/*
 * update_maze_information.cpp
 *
 *  Created on: 2024/08/22
 *      Author: sakur
 */
#include"conversion_from_wallinfo_to_mazeinfo.hpp"

void update_maze(const WallInformation& wallinfo,Maze* maze,const MazeLocation& maze_location){
	bool left = wallinfo.get_status(2);
	bool right = wallinfo.get_status(3);
	bool forward = wallinfo.get_status(1) && wallinfo.get_status(4);


	uint8_t wall_lcl0 = 0;
	uint8_t wall_lcl1 = 0;
	uint8_t wall_lcl3 = 0;
	if(left){
		wall_lcl0 = WALL_SEEN;
	}
	else{
		wall_lcl0 = WALL_OFF;
	}

	if(right){
		wall_lcl1 = WALL_SEEN;
	}
	else{
		wall_lcl1 = WALL_OFF;
	}

	if(forward){
		wall_lcl3 = WALL_SEEN;
	}
	else{
		wall_lcl3 = WALL_OFF;
	}
	maze->set_wall_status_xyd(maze_location.glb_mylocation, maze_location.convert_dir_lcl2lglb(0), wall_lcl0);
	maze->set_wall_status_xyd(maze_location.glb_mylocation, maze_location.convert_dir_lcl2lglb(1), wall_lcl1);
	maze->set_wall_status_xyd(maze_location.glb_mylocation, maze_location.convert_dir_lcl2lglb(3), wall_lcl3);
	maze->set_outer_wall();//端の壁バグの修正のために追加
}
