/*
 * mouse_system_initialize.cpp
 *
 *  Created on: 2024/09/10
 *      Author: sakur
 */
#include"mouse_system_objects.hpp"
#include"wallsencer_measurement.hpp"
#include"indicator_utility.hpp"
void mouse_basic_system_initialize(){
	  //--------general setting-----------
	  GpioPin::all_gpio_init();
	  InterruptIn::all_extipin_init();
	  init_cs_list();
	  //----------indicators setting--------------
	  ind1.configure(GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_LOW,0);
	  ind2.configure(GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_LOW,0);
	  ind3.configure(GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_LOW,0);
	  ind4.configure(GPIO_MODE_OUTPUT_PP,GPIO_NOPULL,GPIO_SPEED_FREQ_LOW,0);
	  //----moter setting-----
	  mt1.start();
	  mt2.start();
	  //----encoder setting----
	  encA.start();
	  encB.start();
	  //-----dma setting---------
	  sencer_dma.dma_start();
	  pwr_dma.dma_start();
	  //-----wall sencer setting------
	  sencer1.set_filter_t_(0.000398);
	  sencer2.set_filter_t_(0.000398);
	  sencer3.set_filter_t_(0.000398);
	  sencer4.set_filter_t_(0.000398);
	  //------------------------------
	  sencer1.start();
	  sencer2.start();
	  sencer3.start();
	  sencer4.start();
	  //----wallsencers setting-------------
	  wallinfo.load_threshold(THRESHOLDS_ADDR);
	  wallinfo.set_factor(0.195f,0.2f,0.3f,0.72f);//(20240904)0.6f,0.1f,0.3f,0.4f(10140904)0.61f,0.08f,0.3f,0.38f
	  sencer1.set_factor3(0.45);//half
	  sencer4.set_factor3(0.70f);//half
	  sencer1.set_factor2(0.28);//full
	  sencer4.set_factor2(0.88);//full
	  //-------------------------------------
	  load_forward_threshold_full_grid();
	  load_forward_threshold_half_grid();
	  //-------------------------------------
	  //-----imu sencer setting-----------
	  bno055.start(OPERATION_MODE_IMUPLUS);
	  //------ticker setting------------
	  basic_cycle.start();
	  HAL_Delay(10);
	  start_func();
}

void mouse_driving_system_initialize(){
	  //-----displacement meter setting----
	  encA_.start(0.01f);
	  encB_.start(0.01f);
	  //---wallctrl setting------------------
	  //wallctrl.set_gain(0.000004,0.0f,0.000001f);
	  wallctrl.set_gain(0.0000008,0.0f,0.0f);//slow
	  wallctrl.set_period(0.001f);
	  wallctrl.set_filter_parameter(0.000796);
	  wallctrl.set_factor(1.2f,1.2f);
	  //-------------------------------------
	  //---imuctrl setting-------------------
	  //p = 0.01 i = 0.0001
	  //imusnccontroller.set_gain(0.014,0.0f,0.00014f);//0.012,0.0001f,0.0f
	  imusnccontroller.set_gain(0.00008,0.000005f,0.000002f);//slow0.0003
	  imusnccontroller.set_period(0.001f);
	  imusnccontroller.set_filter_parameter(0.000796);
	  imusnccontroller.set_target(0.0f);
	  //-------------------------------------
	  //---odm setting----------
	  localization.set_filter(1.0f,1.0f,1.0f,1.0f,2.0f);
	  localization.set_robot_parameters(BodyParameters::HALF_WHEEL_DIST,BodyParameters::WHEEL_RADIUS);
	  localization.start(0.0f,0.0f,0.0f,0.01f);
	  //-----------------
	  //---mt_ctrl setting-------------
	  //left_ctrl.set_gain(0.0009f,0.000008f,0.0003f);
	  left_ctrl.set_gain(0.027f,0.00025f,0.0f);
	  left_ctrl.set_gain(0.0015*0.6f,0.00098f,0.0f);//i gain upup!
	  left_ctrl.mode(true);//ffmode on
	  left_ctrl.set_target(0);
	  left_ctrl.start(0.001f);


	  //right_ctrl.set_gain(0.0008f,0.000005f,0.0001f);
	  right_ctrl.set_gain(0.027f,0.00025f,0.0f);
	  right_ctrl.set_gain(0.00148*0.5f,0.00098f,0.0f);//i gain upup!
	  right_ctrl.mode(true);//ffmode on
	  right_ctrl.set_target(0);
	  right_ctrl.start(0.001f);
	  //------------------
	  //-----mts controller setting----------
	  mtsdriver.start(0.01f);
	  //-------------------------------------
	////////////////////////////
	  start_func();
	////////////////////////////
}

void activate_driving_system(){
	  //=========activate====================
	  encA_.activate();
	  encB_.activate();
	  localization.activate();
	  left_ctrl.activate();
	  right_ctrl.activate();
	  mtsdriver.activate();
	  //=====================================
}

void set_running_parameters(){
	  RunningParameter param{0.16,1.0,8.0*M_PI,0.0};
	  RunningParameter param2{0.2,1.0,10*M_PI,0.0};
	  RunningParameter param3{0.2,1.0,12*M_PI,0.0};
	  RunningParameter param4{0.23,1.0,12*M_PI,0.0};
	  RunningParameter param5{0.24,1.0,12*M_PI,0.0};
	  erase_flash(61);
	  running_parameters_list.register_parameter(param);
	  running_parameters_list.register_parameter(param2);
	  running_parameters_list.register_parameter(param3);
	  running_parameters_list.register_parameter(param4);
	  running_parameters_list.register_parameter(param5);
}


