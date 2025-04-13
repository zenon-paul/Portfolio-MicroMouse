/*
 * stepmap.hpp
 *
 *  Created on: 2024/08/22
 *      Author: sakur
 */

#ifndef INC_STEPMAP_HPP_
#define INC_STEPMAP_HPP_
#include<vector>
#include<functional>
#include<queue>
#include"maximum_number.hpp"
#include"maze.hpp"


struct CellCost {
	XY xy;
	int cost;
};

class StepMap {
public:
	StepMap();
	uint16_t get_step(XY xy);
	uint16_t get_step(int8_t x,int8_t y);
	void set_step(XY xy,uint16_t val);
	void set_step(int8_t x, int8_t y,uint16_t val);
private:
	std::vector<std::vector<uint16_t>> stepmap;
};

void calculate_stepmap(StepMap& cost_table,const Maze& maze, XY start_xy, XY goal_xy);





#endif /* INC_STEPMAP_HPP_ */
