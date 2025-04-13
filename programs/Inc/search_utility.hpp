/*
 * search_utility.hpp
 *
 *  Created on: 2024/09/12
 *      Author: sakur
 */

#ifndef INC_SEARCH_UTILITY_HPP_
#define INC_SEARCH_UTILITY_HPP_
#include"maze.hpp"
#include"maze_route.hpp"
#include"running_parameter.hpp"
#include<vector>

uint16_t get_motion_list_cost(std::vector<uint8_t> motion_list);

uint8_t convert_direction(XY from,XY to);

std::vector<uint8_t> convert_grid_to_motion(MazeLocation initial_loc,std::vector<XY>route);

void set_imusncctrl_target();

void set_imusncctrl_target(uint8_t dir);

bool is_in_goal_area();

bool is_in_goal_area(MazeLocation ml);

std::vector<XY> prepare_for_second_search(RunningParameter param);

const MazeRoute& compare(const MazeRoute& a,const MazeRoute& b);

#endif /* INC_SEARCH_UTILITY_HPP_ */
