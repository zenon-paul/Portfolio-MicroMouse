/*
 * search.hpp
 *
 *  Created on: 2024/08/22
 *      Author: sakur
 */

#ifndef INC_ADACHI_SEARCH_HPP_
#define INC_ADACHI_SEARCH_HPP_
#include"stepmap.hpp"
#include"maze.hpp"
#include"maze_location.hpp"

uint8_t AdatiSearch(const Maze& maze,const MazeLocation& maze_location,const XY& goal);




#endif /* INC_ADACHI_SEARCH_HPP_ */
