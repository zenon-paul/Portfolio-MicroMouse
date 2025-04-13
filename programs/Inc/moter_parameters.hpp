/*
 * moter_parameters.hpp
 *
 *  Created on: Aug 16, 2024
 *      Author: sakur
 */

#ifndef INC_MOTER_PARAMETERS_HPP_
#define INC_MOTER_PARAMETERS_HPP_
#include"phisics_parameters.hpp"

class MoterParameters{
public:
	constexpr static float REG = 3.5;//Ω
	constexpr static float Ke = 0.00141;//0.00141;//V/rmp
	constexpr static float Kt = 0.0135;//0.0135;//Nm/A
	constexpr static float GEAR_RATE = 0.10039;//9.9615;//0.10039;//9.9615;
};
//I = 0.68T
//Kt_[kgfmm/A] = 1/0.68;
//Kt[Nm/A] = Kt_*G*10^(-3);
//Ke [V/rmp] = 2*PI*Kt/69;

#endif /* INC_MOTER_PARAMETERS_HPP_ */
