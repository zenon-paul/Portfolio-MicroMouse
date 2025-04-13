/*
 * maze_location.hpp
 *
 *  Created on: 2024/08/22
 *      Author: sakur
 */

#ifndef INC_MAZE_LOCATION_HPP_
#define INC_MAZE_LOCATION_HPP_
#include<stdint.h>
#include"maze.hpp"
#include"flash_memory.hpp"

class MazeLocation {
public:
	enum class Motion{LEFT,RIGHT,BACK,FORWARD,STOP,NONE};
	uint8_t glb_forward_dir;
	XY glb_mylocation;
	MazeLocation();
	MazeLocation(XY start,uint8_t f_dir);
	uint8_t convert_dir_lcl2lglb(uint8_t lcl) const;
	uint8_t convert_dir_glb2lcl(uint8_t glb) const;
	void go_to_left();
	void go_to_right();
	void back();
	void go_forward();
	void go_to(uint8_t dir);
	uint8_t detect_next_motion(XY neiborhood) const;
	uint32_t register_maze_location(uint32_t addr,uint8_t extra_word);
	uint32_t read_maze_location(uint32_t addr,uint8_t* x,uint8_t* y,uint8_t* glb_fdir,uint8_t* extra);
};





#endif /* INC_MAZE_LOCATION_HPP_ */
