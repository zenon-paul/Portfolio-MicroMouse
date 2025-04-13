/*
 * dial.cpp
 *
 *  Created on: 2024/09/16
 *      Author: sakur
 */
#include"encoder.hpp"
#include"dial.hpp"

Dial::Dial(Encoder* e,Encoder* s,int32_t count,int32_t enter_count,Indicators* inds)
:enter_dial(e),
 selection_dial(s),
 count_up_num(count),
 enter_dial_threshold(enter_count),
 inds(inds){};

uint16_t Dial::get_ID(){
	inds->turn_off_all();
	int32_t initial_selection_dial = this->selection_dial->count;
	int32_t initial_enter_dial = this->enter_dial->count;
	uint16_t tmpID = 0;
	int32_t diff = this->selection_dial->count - initial_selection_dial;
	int32_t diff_ = this->enter_dial->count - initial_enter_dial;
	while(diff_ < this->enter_dial_threshold){
		tmpID = (diff/this->count_up_num)&(0x000F);
		diff = this->selection_dial->count - initial_selection_dial;
		diff_ = this->enter_dial->count - initial_enter_dial;
		this->inds->display_number(tmpID);
	}

	this->inds->turn_off_all();
	HAL_Delay(3000);

	for(int i = 0;i<4;i++){
		this->inds->turn_on_all();
		HAL_Delay(100);
		this->inds->turn_off_all();
		HAL_Delay(100);
	}

	return tmpID;
}
