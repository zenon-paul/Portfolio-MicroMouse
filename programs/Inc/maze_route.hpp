/*
 * maze_route.hpp
 *
 *  Created on: 2024/09/13
 *      Author: sakur
 */

#ifndef INC_MAZE_ROUTE_HPP_
#define INC_MAZE_ROUTE_HPP_
#include<stack>
#include<vector>
#include"maze.hpp"
#include"maze_location.hpp"

class MazeRoute{
public:
	MazeRoute();
	void push(XY xy);
	XY pop();
	bool empty();
	void reverse();
private:
	std::stack<XY> route;
};




#endif /* INC_MAZE_ROUTE_HPP_ */
