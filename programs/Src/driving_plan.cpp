/*
 * clothoid_curve.cpp
 *
 *  Created on: 2024/08/28
 *      Author: sakur
 */
#include"gpio.hpp"
#include"driving_plan.hpp"
extern GpioPin ind1;
extern GpioPin ind2;
extern GpioPin ind3;
extern GpioPin ind4;

//ブロッキングな関数であることに注意
void navigate_to_clothoid_curve_anti(DriveMoters* mtsdriver,Localization* localization,float agl0,float agl1,float agl2,float fv,float aa,IMUSencer* bno055){
	if((agl0 < 0.0f) || (agl1 < 0.0f) || (agl2 < 0.0f) || (fv < 0) || (aa < 0)){
		return;
	}
	uint8_t stage = 0;
	mtsdriver->set_target_forward_velocity(fv);
	mtsdriver->set_target_angular_velocity(0.0);
	mtsdriver->set_target_forward_acceleration(0.0);
	mtsdriver->set_target_angular_acceleration(aa);
	float initial_rad = localization->approx_rot;
	float a0 = agl0;
	float a1 = a0 + agl1;
	float a2 = a1 + agl2;
	//------------------------------
	while(1){
		bno055->read_eul_heading(false);

		if((stage == 0) && ((localization->approx_rot-initial_rad) > a0)){
			stage = 1;
			mtsdriver->set_target_forward_velocity(fv);
			mtsdriver->set_target_angular_acceleration(0.0f);
		}
		if((stage == 1) && ((localization->approx_rot-initial_rad) > a1)){
			stage = 2;
			mtsdriver->set_target_forward_velocity(fv);
			mtsdriver->set_target_angular_acceleration(-aa);
		}
		if((stage == 2) && ((localization->approx_rot-initial_rad) > a2)){
			break;
		}
		if((stage == 2) && (localization->angular_velocity < 0)){
			break;
		}
	}
	mtsdriver->set_target_angular_acceleration(0.0);
	mtsdriver->set_target_angular_velocity(0.0);
	mtsdriver->set_target_forward_velocity(fv);
}

void navigate_to_clothoid_curve_clock(DriveMoters* mtsdriver,Localization* localization,float agl0,float agl1,float agl2,float fv,float aa,IMUSencer* bno055){
	if((agl0 < 0.0f) || (agl1 < 0.0f) || (agl2 < 0.0f) || (fv < 0) || (aa < 0)){
		return;
	}
	uint8_t stage = 0;
	mtsdriver->set_target_forward_velocity(fv);
	mtsdriver->set_target_angular_velocity(0.0);
	mtsdriver->set_target_forward_acceleration(0.0);
	mtsdriver->set_target_angular_acceleration(-aa);
	float initial_rad = localization->approx_rot;
	float a0 = -agl0;
	float a1 = a0 - agl1;
	float a2 = a1 - agl2;
	//------------------------------
	while(1){
		bno055->read_eul_heading(false);
		if((stage == 0) && ((localization->approx_rot-initial_rad) < a0)){
			stage = 1;
			mtsdriver->set_target_forward_velocity(fv);
			mtsdriver->set_target_angular_acceleration(0.0f);
		}
		if((stage == 1) && ((localization->approx_rot-initial_rad) < a1)){
			stage = 2;
			mtsdriver->set_target_forward_velocity(fv);
			mtsdriver->set_target_angular_acceleration(aa);
		}
		if((stage == 2) && ((localization->approx_rot-initial_rad) < a2)){
			break;
		}
		if((stage == 2) && (localization->angular_velocity > 0)){
			break;
		}
	}
	mtsdriver->set_target_angular_acceleration(0.0);
	mtsdriver->set_target_angular_velocity(0.0);
	mtsdriver->set_target_forward_velocity(fv);
}

void navigate_with_daike_control(DriveMoters* mtsdriver,Localization* localization,float fa,float flat_fv,float end_fv,float target_mileage,IMUSencer* bno055){
	uint8_t stage = 0;
	float start_fv = localization->forward_velocity;
	float t0 = abs(start_fv-flat_fv)/fa;//s
	float t2 = abs(flat_fv-end_fv)/fa;//s
	float mileage0 = 0.5*(start_fv+flat_fv)*t0;
	float mileage2 = 0.5*(flat_fv+end_fv)*t2;
	float mileage1 = target_mileage - mileage0 - mileage2;
	if(mileage1 < 0){
		float fv_ =  pow((2.0*fa*target_mileage + pow(start_fv,2.0) + pow(end_fv,2.0))/2.0,0.5);
		t0 = abs(fv_-start_fv)/fa;
		t2 = abs(fv_-end_fv)/fa;
		mileage0 = 0.5*(start_fv+fv_)*t0;
		mileage1 = 0;
		mileage2 = 0.5*(fv_+end_fv)*t2;
	}
	mtsdriver->set_target_angular_velocity(0.0);
	mtsdriver->set_target_forward_acceleration(fa);
	mtsdriver->set_target_angular_acceleration(0.0);
	float m0 = mileage0;
	float m1 = m0 + mileage1;
	float m2 = m1 + mileage2;
	//---------------------------------
	float initial_mileage = localization->mileage;//mm
	while(1){
		bno055->read_eul_heading(false);
		if((stage == 0) && ((localization->mileage-initial_mileage) > m0*1000.0)){
			stage = 1;
			mtsdriver->set_target_forward_acceleration(0.0f);
		}
		if((stage == 1) && ((localization->mileage-initial_mileage) > m1*1000.0)){
			stage = 2;
			mtsdriver->set_target_forward_acceleration(-fa);
		}
		if((stage == 2) && ((localization->mileage-initial_mileage) > m2*1000.0)){
			break;
		}
		if((stage == 2) && (localization->forward_velocity < end_fv)){
			break;
		}
	}
	mtsdriver->set_target_forward_acceleration(0.0);
	mtsdriver->set_target_forward_velocity(end_fv);
}

void go_forward_simple(DriveMoters* mtsdriver,Localization* localization,float fv,float target_mileage,IMUSencer* bno055){
	mtsdriver->set_target_angular_acceleration(0.0);
	mtsdriver->set_target_angular_velocity(0.0);
	mtsdriver->set_target_forward_acceleration(0.0);
	mtsdriver->set_target_forward_velocity(0.0);
	float initial_mileage = localization->mileage;
	while((localization->mileage - initial_mileage) < target_mileage*1000.0){
		bno055->read_eul_heading(false);
		mtsdriver->set_target_forward_velocity(fv);
	}
	mtsdriver->set_target_angular_acceleration(0.0);
	mtsdriver->set_target_angular_velocity(0.0);
	mtsdriver->set_target_forward_acceleration(0.0);
	mtsdriver->set_target_forward_velocity(0.0);
}

void go_forward(DriveMoters* mtsdriver,Localization* localization,float fv,float target_mileage,IMUSencer* bno055){
	mtsdriver->set_target_angular_acceleration(0.0);
	mtsdriver->set_target_angular_velocity(0.0);
	mtsdriver->set_target_forward_acceleration(0.0);
	mtsdriver->set_target_forward_velocity(fv);
	float initial_mileage = localization->mileage;
	while((localization->mileage - initial_mileage) < target_mileage*1000.0){
		bno055->read_eul_heading(false);
	}
}


