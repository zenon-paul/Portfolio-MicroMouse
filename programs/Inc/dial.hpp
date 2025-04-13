/*
 * dial.hpp
 *
 *  Created on: 2024/09/16
 *      Author: sakur
 */

#ifndef INC_DIAL_HPP_
#define INC_DIAL_HPP_
#include"encoder.hpp"
#include"indicators.hpp"

class Dial{
public:
	Dial(Encoder* e,Encoder* s,int32_t count,int32_t enter_count,Indicators*);
	uint16_t get_ID();
private:
	Encoder* enter_dial;
	Encoder* selection_dial;
	int32_t count_up_num;
	int32_t enter_dial_threshold;
	Indicators* inds;
};




#endif /* INC_DIAL_HPP_ */
