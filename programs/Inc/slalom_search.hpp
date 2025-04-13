/*
 * slalom_search.hpp
 *
 *  Created on: 2024/09/10
 *      Author: sakur
 */

#ifndef INC_SLALOM_SEARCH_HPP_
#define INC_SLALOM_SEARCH_HPP_
#include"maze.hpp"
#include"running_parameter.hpp"

void slalom_left(XY goal,RunningParameter param);
void slalom_right(XY goal,RunningParameter param);
void slalom_back(XY goal,RunningParameter param);
void slalom_go(XY goal,RunningParameter param);
void slalom_search(XY goal,RunningParameter param);


#endif /* INC_SLALOM_SEARCH_HPP_ */
