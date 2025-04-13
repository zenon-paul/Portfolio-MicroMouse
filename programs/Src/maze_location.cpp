/*
 * maze_location.cpp
 *
 *  Created on: 2024/08/22
 *      Author: sakur
 */
#include"maze_location.hpp"

constexpr static uint8_t convert_lcl2glb_table[4][4] = {
	{2,3,1,0},
	{3,2,0,1},
	{1,0,3,2},
	{0,1,2,3}
};
constexpr static uint8_t convert_glb2lcl_table[4][4] = {
	{3,2,0,1},
	{2,3,1,0},
	{1,0,3,2},
	{0,1,2,3}
};


MazeLocation::MazeLocation()
:glb_forward_dir(3),
glb_mylocation(0, 0) {}

MazeLocation::MazeLocation(XY start,uint8_t f_dir)
:glb_forward_dir(f_dir),
 glb_mylocation(start){}

uint8_t MazeLocation::convert_dir_lcl2lglb(uint8_t lcl) const {//glb_foward_dirの更新
	return convert_lcl2glb_table[this->glb_forward_dir][lcl];
}

uint8_t MazeLocation::convert_dir_glb2lcl(uint8_t glb) const {
	return convert_glb2lcl_table[this->glb_forward_dir][glb];
}
void MazeLocation::go_to_left() {
	this->glb_forward_dir = this->convert_dir_lcl2lglb(0);
	this->glb_mylocation += directions[this->glb_forward_dir];
}
void MazeLocation::go_to_right() {
	this->glb_forward_dir = this->convert_dir_lcl2lglb(1);
	this->glb_mylocation += directions[this->glb_forward_dir];
}
void MazeLocation::back() {
	this->glb_forward_dir = this->convert_dir_lcl2lglb(2);
	this->glb_mylocation += directions[this->glb_forward_dir];
}
void MazeLocation::go_forward() {
	this->glb_mylocation += directions[this->glb_forward_dir];
}
void MazeLocation::go_to(uint8_t dir) {
	if (dir >= 4) {
		return;
	}
	this->glb_forward_dir = this->convert_dir_lcl2lglb(dir);
	this->glb_mylocation += directions[this->glb_forward_dir];
}

/*帰ってきた座標と現在の座標からgo left rightを決定する*/
uint8_t MazeLocation::detect_next_motion(XY neiborhood) const {//引き算で決定
	if(neiborhood == glb_mylocation){
		return 4;//stop
	}
	XY glb_dir_vec = neiborhood - glb_mylocation;//命名則...
	uint8_t lcl_dir = 0;
	for (int i = 0; i < 4; i++) {
		if (directions[i] == glb_dir_vec) {
			lcl_dir = convert_dir_glb2lcl(i);
			return lcl_dir;
		}
	}
	return 5;//none
}

uint32_t MazeLocation::register_maze_location(uint32_t addr,uint8_t extra_word){
	return write_flash_words(addr,uint8_t(this->glb_mylocation.x),uint8_t(this->glb_mylocation.y),this->glb_forward_dir,extra_word);
}

uint32_t MazeLocation::read_maze_location(uint32_t addr,uint8_t* x,uint8_t* y,uint8_t* glb_fdir,uint8_t* extra){
	return read_flash_words(addr,x,y,glb_fdir,extra);
}
