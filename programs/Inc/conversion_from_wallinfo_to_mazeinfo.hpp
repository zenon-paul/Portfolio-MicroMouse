/*
 * update_maze_information.hpp
 *
 *  Created on: 2024/08/22
 *      Author: sakur
 */

#ifndef INC_CONVERSION_FROM_WALLINFO_TO_MAZEINFO_HPP_
#define INC_CONVERSION_FROM_WALLINFO_TO_MAZEINFO_HPP_
#include<stdint.h>
#include"wallinformation.hpp"
#include"maze.hpp"
#include"maze_location.hpp"

void update_maze(const WallInformation& wallinfo,Maze* maze,const MazeLocation& maze_location);



#endif /* INC_CONVERSION_FROM_WALLINFO_TO_MAZEINFO_HPP_ */
