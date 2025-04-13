/*
 * mouse_system_objects.hpp
 *
 *  Created on: 2024/09/10
 *      Author: sakur
 */

#ifndef INC_MOUSE_SYSTEM_OBJECTS_HPP_
#define INC_MOUSE_SYSTEM_OBJECTS_HPP_
#include"adachi_search.hpp"
#include"analogin.hpp"
#include"battery.hpp"
#include"BNO055.hpp"
#include"body_parameters.hpp"
#include"conversion_from_wallinfo_to_mazeinfo.hpp"
#include"dial.hpp"
#include"displacement_meter.hpp"
#include"dma_adc.hpp"
#include"drive_moters.hpp"
#include"driving_plan.hpp"
#include"encoder.hpp"
#include"ffcontroller.hpp"
#include"filter.hpp"
#include"gpio.hpp"
#include"grid_size.hpp"
#include"i2c.hpp"
#include"imusencer.hpp"
#include"imusencercontroller.hpp"
#include"indicators.hpp"
#include"interruptin.hpp"
#include"localization.hpp"
#include"maze_location.hpp"
#include"maze_route.hpp"
#include"maze.hpp"
#include"moter_parameters.hpp"
#include"moter.hpp"
#include"motercontroller.hpp"
#include"mouse_mode_manager.hpp"
#include"pidcontroller.hpp"
#include"pwmout.hpp"
#include"running_parameter.hpp"
#include"stepmap.hpp"
#include"ticker.hpp"
#include"turn_angle_parameters.hpp"
#include"wallcontroller.hpp"
#include"wallinformation.hpp"
#include"wallsencer.hpp"

extern GpioPin ind1;
extern GpioPin ind2;
extern GpioPin ind3;
extern GpioPin ind4;
extern Indicators indicators;
extern DmaAdc sencer_dma;
extern DmaAdc pwr_dma;
extern Battery pwr_source;
extern Ticker basic_cycle;
extern WallSencer sencer1;
extern WallSencer sencer2;
extern WallSencer sencer3;
extern WallSencer sencer4;
extern WallInformation wallinfo;
extern WallController wallctrl;
extern Encoder encA;
extern Encoder encB;
extern DisplacementMeter encA_;
extern DisplacementMeter encB_;
extern Moter mt1;
extern Moter mt2;
extern IMUSencer bno055;
extern IMUSNCController imusnccontroller;
extern Localization localization;
extern FFController ffcontroller;
extern MoterController left_ctrl;
extern MoterController right_ctrl;
extern XY Start;
extern XY goal1;
extern XY goal2;
extern XY goal3;
extern XY goal4;
extern XY goal_representative;
extern XY Goals[4];
extern Maze maze;//迷路情報そのもの
extern MazeLocation maze_location;//この時点で(0,0,3)に設定される　迷路内のマウスの位置向き情報
extern DriveMoters mtsdriver;
extern RunningParameterList running_parameters_list;
extern Dial dial;
//extern MouseModeManager mouse_mode_manager;

float deg_rad(float deg);

#endif /* INC_MOUSE_SYSTEM_OBJECTS_HPP_ */
