/*
 * test.cpp
 *
 *  Created on: 2024/09/21
 *      Author: sakur
 */
#include"wallsencer_test.hpp"
#include"wallcontrol_test.hpp"
#include"imucontrol_test.hpp"
#include"imusencer_test.hpp"
#include"wall_adjustment.hpp"
#include"running_parameter.hpp"
#include<math.h>
#include<stdint.h>

void test(uint8_t id){
	RunningParameter p{0.2,1.0,10*M_PI,8.0};
	switch(id){
	case 0:
		test_wall_rigidly_exist();
		break;
	case 1:
		test_wall_exist();
		break;
	case 2:
		test_wall_exist2();
		break;
	case 3:
		test_wall_exist3();
		break;
	case 4:
		test_wallcontrol();
		break;
	case 5:
		test_rad();
		break;
	case 6:
		test_continuous_rad();
		break;
	case 7:
		test_original_rad();
		break;
	case 8:
		test_imucontrol(0.0);
		break;
	case 9:
		test_imucontrol(M_PI);
		break;
	case 10:
		test_imucontrol_anti(0.45f);
		break;
	case 11:
		test_imucontrol_clock(0.45f);
		break;
	case 12:
		adjust_with_wallsencer_non_back(p);
		break;
	case 13:
		break;
	case 14:
		break;
	case 15:
		break;
	default:
		break;
	}
}


