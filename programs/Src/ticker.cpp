/*
 * ticker.cpp
 *
 *  Created on: 2024/08/06
 *      Author: sakur
 */
#include<stm32g4xx.h>
#include<stm32g431xx.h>
#include<stm32g4xx_hal_tim.h>
#include<vector>
#include<functional>
#include"ticker.hpp"
//tickerをもつオブジェクトには共通する関数が存在するのでやはりticker基底クラスを作るべきっだったか・・・
Ticker::Ticker(TIM_HandleTypeDef* htimx,uint32_t prscl,uint32_t pd)
:period(pd),
 maxHz(float(Ticker::clock)/float((prscl+1)*(pd+1)) ),
 htimx(htimx),
 prescaler(prscl){}

void Ticker::start(){
	HAL_TIM_Base_Start_IT(this->htimx);
}


