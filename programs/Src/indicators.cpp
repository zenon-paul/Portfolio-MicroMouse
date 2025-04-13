/*
 * indicators.cpp
 *
 *  Created on: 2024/09/16
 *      Author: sakur
 */
#include"indicators.hpp"

Indicators::Indicators(GpioPin* i1,GpioPin* i2,GpioPin* i3,GpioPin* i4)
:ind1(i1),
 ind2(i2),
 ind3(i3),
 ind4(i4){}

void Indicators::display_number(uint8_t num){
	(*ind1) = (num>>0)&1;
	(*ind2) = (num>>1)&1;
	(*ind3) = (num>>2)&1;
	(*ind4) = (num>>3)&1;
}

void Indicators::turn_off_all(){
	(*ind1) = 0;
	(*ind2) = 0;
	(*ind3) = 0;
	(*ind4) = 0;
}

void Indicators::turn_on_all(){
	(*ind1) = 1;
	(*ind2) = 1;
	(*ind3) = 1;
	(*ind4) = 1;
}
