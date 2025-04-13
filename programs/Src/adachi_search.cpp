/*
 * search.cpp
 *
 *  Created on: 2024/08/22
 *      Author: sakur
 */
#include"stepmap.hpp"
#include"maze.hpp"
#include"maze_location.hpp"

uint8_t AdatiSearch(const Maze& maze,const MazeLocation& maze_location,const XY& goal){
	StepMap stepmap;
	calculate_stepmap(stepmap,maze,goal,maze_location.glb_mylocation);

	uint8_t next_dir = 2;
	uint16_t next_step = stepmap.get_step(maze_location.glb_mylocation) - 1;

	if ((maze.get_wall_status_xyd(maze_location.glb_mylocation, maze_location.convert_dir_lcl2lglb(1)) != WALL_SEEN)
		&& (next_step == stepmap.get_step(maze_location.glb_mylocation + directions[maze_location.convert_dir_lcl2lglb(1)]))) {
		next_dir = 1;
	}
	if ((maze.get_wall_status_xyd(maze_location.glb_mylocation, maze_location.convert_dir_lcl2lglb(3)) != WALL_SEEN)
		&& (next_step == stepmap.get_step(maze_location.glb_mylocation + directions[maze_location.convert_dir_lcl2lglb(3)]))) {
		next_dir = 3;
	}
	if ((maze.get_wall_status_xyd(maze_location.glb_mylocation, maze_location.convert_dir_lcl2lglb(0)) != WALL_SEEN)
		&& (next_step == stepmap.get_step(maze_location.glb_mylocation + directions[maze_location.convert_dir_lcl2lglb(0)]))) {
		next_dir = 0;
	}
	return next_dir;
}




