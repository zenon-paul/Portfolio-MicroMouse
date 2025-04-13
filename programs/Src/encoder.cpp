/*
 * encoder.cpp
 *
 *  Created on: 2024/08/06
 *      Author: sakur
 */
#include"encoder.hpp"

Encoder::Encoder(GPIO_TypeDef* A_GPIOx,GpioPin::PinName A_Pin,GPIO_TypeDef* B_GPIOx,GpioPin::PinName B_Pin,int32_t resolution)
:count(0),
 resolution(resolution),
 Apin(A_GPIOx,A_Pin),
 A_GPIO_Pin(A_Pin),
 Bpin(B_GPIOx,B_Pin),
 B_GPIO_Pin(B_Pin){}

void Encoder::start(){
	this->Apin.start();
	this->Bpin.start();
}

void Encoder::calculate(uint32_t GPIO_Pin){
	GPIO_PinState a_enc_val = Apin.readpin();
	GPIO_PinState b_enc_val = Bpin.readpin();

	if (GPIO_Pin == this->A_GPIO_Pin){
    	if(a_enc_val == GPIO_PIN_SET){//rising
    		if(b_enc_val ==GPIO_PIN_SET){
    			this->count++;
    		}
    		else{
    			this->count--;
    		}
    	}
    	else{//falling
    		if(b_enc_val == GPIO_PIN_SET){
    			this->count--;
    		}
    		else{
    			this->count++;
    		}
    	}
	}
	if (GPIO_Pin == this->B_GPIO_Pin){
    	if(b_enc_val == GPIO_PIN_SET){//rising
    		if(a_enc_val == GPIO_PIN_SET){
    			this->count--;
    		}
    		else{
    			this->count++;
    		}
    	}
    	else{//falling
    		if(a_enc_val == GPIO_PIN_SET){
    			this->count++;
    		}
    		else{
    			this->count--;
    		}
    	}
	}
}

void Encoder::set_count_zero(){
	this->count = 0;
}
