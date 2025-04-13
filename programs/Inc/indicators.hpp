/*
 * indicators.hpp
 *
 *  Created on: 2024/09/16
 *      Author: sakur
 */

#ifndef INC_INDICATORS_HPP_
#define INC_INDICATORS_HPP_
#include"gpio.hpp"

class Indicators{
public:
	Indicators(GpioPin*,GpioPin*,GpioPin*,GpioPin*);
	void display_number(uint8_t);
	void turn_off_all();
	void turn_on_all();
private:
	GpioPin* ind1;
	GpioPin* ind2;
	GpioPin* ind3;
	GpioPin* ind4;
};




#endif /* INC_INDICATORS_HPP_ */
