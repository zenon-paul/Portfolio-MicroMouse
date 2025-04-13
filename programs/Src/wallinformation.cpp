/*
 * wallinformation.cpp
 *
 *  Created on: Aug 20, 2024
 *      Author: sakur
 */
#include"wallinformation.hpp"

WallInformation::WallInformation(WallSencer* s1,WallSencer* s2,WallSencer* s3,WallSencer* s4)
:snc1_forward(s1),
 snc2_left(s2),
 snc3_right(s3),
 snc4_forward(s4){}

void WallInformation::set_factor(float f1,float f2,float f3,float f4){
	this->snc1_forward->set_factor(f1);
	this->snc2_left->set_factor(f2);
	this->snc3_right->set_factor(f3);
	this->snc4_forward->set_factor(f4);
}

uint32_t WallInformation::register_threshold(uint32_t addr)const{
	//erase_flash(63);///ここでフラッシュしていたが分離させmain内で実行させるようにする
	uint32_t next_addr = write_flash_float(addr,this->snc1_forward->threshold,this->snc2_left->threshold);
	return write_flash_float(next_addr,this->snc3_right->threshold,this->snc4_forward->threshold);
}

void WallInformation::load_threshold(uint32_t addr){
	float t1,t2,t3,t4;
	uint32_t next_addr = read_flash_float(addr,&t1,&t2);
	read_flash_float(next_addr,&t3,&t4);
	this->snc1_forward->threshold = t1;
	this->snc2_left->threshold = t2;
	this->snc3_right->threshold = t3;
	this->snc4_forward->threshold = t4;
}

bool WallInformation::operator[](uint8_t i)const{
	switch(i){
	case 1:
		return this->snc1_forward->get_status();
	case 2:
		return this->snc2_left->get_status();
	case 3:
		return this->snc3_right->get_status();
	case 4:
		return this->snc4_forward->get_status();
	default:
		return true;
	}
}

bool WallInformation::get_status(uint8_t i)const{
	switch(i){
	case 1:
		return this->snc1_forward->get_status();
	case 2:
		return this->snc2_left->get_status();
	case 3:
		return this->snc3_right->get_status();
	case 4:
		return this->snc4_forward->get_status();
	default:
		return true;
	}
}

void WallInformation::calculate_threshold(int sample_num){
	this->snc1_forward->calculate_threshold(sample_num);
	this->snc2_left->calculate_threshold(sample_num);
	this->snc3_right->calculate_threshold(sample_num);
	this->snc4_forward->calculate_threshold(sample_num);
}

void WallInformation::calculate_side_threshold(int sample_num){
	this->snc2_left->calculate_threshold(sample_num);
	this->snc3_right->calculate_threshold(sample_num);
}

void WallInformation::calculate_forward_threshold(int sample_num){
	this->snc1_forward->calculate_threshold(sample_num);
	this->snc4_forward->calculate_threshold(sample_num);
}



