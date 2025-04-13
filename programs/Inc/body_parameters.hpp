/*
 * body_parameters.hpp
 *
 *  Created on: 2024/08/10
 *      Author: sakur
 */
#ifndef INC_BODY_PARAMATERS_HPP_
#define INC_BODY_PARAMATERS_HPP_

class BodyParameters{
public:
	constexpr static float HALF_WIDTH = 41.6;//mm
	constexpr static float HALF_WHEEL_DIST = 37.4;//mm//36.6
	constexpr static float HALF_WHEEL_DIST_M = HALF_WHEEL_DIST/1000.0;//m
	constexpr static float HEAD_CENTER_DIST = 50.0;//mm
	constexpr static float CENTER_TAIL_DIST = 28.0;//mm
	constexpr static float WHEEL_RADIUS = 10.5;//mm
	constexpr static float WHEEL_RADIUS_M = WHEEL_RADIUS/1000.0;//m
	constexpr static float WEIGHT = 0.1;//kg

};

#endif


