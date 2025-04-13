/*
 * clothoid_curve.hpp
 *
 *  Created on: 2024/08/28
 *      Author: sakur
 */

#ifndef INC_DRIVING_PLAN_HPP_
#define INC_DRIVING_PLAN_HPP_
#include"drive_moters.hpp"
#include"localization.hpp"
#include"imusencer.hpp"

void navigate_to_clothoid_curve_anti(DriveMoters* mtsdriver,Localization* localization,float agl1,float agl2,float agl3,float fv,float aa,IMUSencer* bno055);
void navigate_to_clothoid_curve_clock(DriveMoters* mtsdriver,Localization* localization,float agl1,float agl2,float agl3,float fv,float aa,IMUSencer* bno055);
void navigate_with_daike_control(DriveMoters* mtsdriver,Localization* localization,float fa,float flat_fv,float end_fv,float target_mileage,IMUSencer* bno055);
void go_forward_simple(DriveMoters* mtsdriver,Localization* localization,float fv,float target_mileage,IMUSencer* bno055);
void go_forward(DriveMoters* mtsdriver,Localization* localization,float fv,float target_mileage,IMUSencer* bno055);
#endif /* INC_DRIVING_PLAN_HPP_ */
