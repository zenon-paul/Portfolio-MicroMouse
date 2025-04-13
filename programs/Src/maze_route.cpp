/*
 * maze_route.cpp
 *
 *  Created on: 2024/09/13
 *      Author: sakur
 */
#include"mouse_system_objects.hpp"
#include<vector>
#include<stack>
#include<algorithm>

MazeRoute::MazeRoute(){}

void MazeRoute::push(XY xy){
	this->route.push(xy);
}

XY MazeRoute::pop(){
	if(this->route.empty()){
		return XY{-1,-1};
	}
	XY xy = this->route.top();
	this->route.pop();
	return xy;
}

bool MazeRoute::empty(){
	return this->route.empty();
}

void MazeRoute::reverse(){
	std::stack<XY> tmp;
	while(!this->route.empty()){
		tmp.push(this->route.top());
		this->route.pop();
	}
	this->route = tmp;
}



