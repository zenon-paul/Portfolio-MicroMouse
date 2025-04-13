/*
 * mouse_sysytem_non_slalom_search.hpp
 *
 *  Created on: 2024/09/10
 *      Author: sakur
 */

#ifndef INC_NON_SLALOM_SEARCH_MODE_HPP_
#define INC_NON_SLALOM_SEARCH_MODE_HPP_
#include"maze.hpp"
#include"running_parameter.hpp"
#include"maze_route.hpp"

void non_slalom_left(RunningParameter param);

void non_slalom_right(RunningParameter param);

void non_slalom_back(RunningParameter param);

void non_slalom_go(RunningParameter param);

MazeRoute non_slalom_search(XY goal,RunningParameter pram);

#endif /* INC_NON_SLALOM_SEARCH_MODE_HPP_ */
