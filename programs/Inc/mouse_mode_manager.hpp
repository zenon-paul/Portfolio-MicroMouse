/*
 * mouse.hpp
 *
 *  Created on: 2024/09/16
 *      Author: sakur
 */

#ifndef INC_MOUSE_MODE_MANAGER_HPP_
#define INC_MOUSE_MODE_MANAGER_HPP_
#include"mouse_system_objects.hpp"
#include"running_parameter.hpp"
#include<functional>

template <class T,class U>
class MouseModeManager{
public:
	constexpr static uint8_t TEST_MODE_ID = 15;
	MouseModeManager(Dial* dial):dial(dial){
		this->operate_dial_callback_func =
				[this](void)->void{
					this->get_dial_input();
					if(this->dial_input == TEST_MODE_ID){
						this->test_mode_callback_func();
					}
					this->param = this->get_param(this->dial_input);
					this->running_callback_func(this->param);
				};
	}
	void set_search_func(std::function<T(U)>& f){
		this->search_callback_func = [this,&f](U)->void{this->route = f(this->param); /*this->switch_to_speed_run_mode();*/ this->operate_dial_callback_func();};
	}
	void set_speed_run_func(std::function<void(U,T)>& f){
		this->speed_run_callback_func = [this,&f](U)->void{f(this->param,route); this->operate_dial_callback_func();};
	}
	void set_test_mode_func(std::function<void(uint8_t)>& f){
		this->test_mode_callback_func = [this,&f](void)->void{this->get_dial_input(); f(this->dial_input); this->operate_dial_callback_func();};
	}
	void set_dial_func(std::function<U(uint8_t)>& f){
		this->get_param = f;
	}
	void switch_to_search_mode(){
		this->running_callback_func = this->search_callback_func;
	}
	void switch_to_speed_run_mode(){
		this->running_callback_func = this->speed_run_callback_func;
	}
	void start(){
		this->operate_dial_callback_func();
	}
private:
	void get_dial_input(){
		this->dial_input = this->dial->get_ID();
	}
	Dial* dial;
	std::function<void(U)> search_callback_func;
	std::function<void(U)> speed_run_callback_func;
	std::function<U(uint8_t)> get_param;
	std::function<void(U)> running_callback_func;
	std::function<void(void)> operate_dial_callback_func;
	std::function<void(void)> test_mode_callback_func;
	uint8_t dial_input;
	U param;
	T route;//std::vector<XY>
};



#endif /* INC_MOUSE_MODE_MANAGER_HPP_ */
