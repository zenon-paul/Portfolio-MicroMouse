/*
 * maze.cpp
 *
 *  Created on: 2024/08/22
 *      Author: sakur
 */
#include"maze.hpp"

constexpr uint8_t mask[4] = { 3,12,48,192 };
XY::XY(int8_t x, int8_t y) {
	this->x = x;
	this->y = y;
}

XY::XY(const XY& xy) {
	this->x = xy.x;
	this->y = xy.y;
}

XY& XY::operator=(const XY& xy)& {
	this->x = xy.x;
	this->y = xy.y;
	return *this;
}

XY XY::operator-()const {
	XY res{ -(this->x),-(this->y) };
	return res;
}

XY& XY::operator+=(const XY& xy)& {
	this->x = this->x + xy.x;
	this->y = this->y + xy.y;
	return *this;
}

XY& XY::operator-=(const XY& xy)& {
	this->x = this->x - xy.x;
	this->y = this->y - xy.y;
	return *this;
}

bool operator==(const XY& a, const XY& b) {
	return (a.x == b.x) && (a.y == b.y);
}

bool operator!=(const XY& a, const XY& b) {
	return (a.x != b.x) || (a.y != b.y);
}

XY operator+(const XY& a, const XY& b) {
	XY res{ a.x + b.x,a.y + b.y };
	return res;
}

XY operator-(const XY& a, const XY& b) {
	XY res{ a.x - b.x,a.y - b.y };
	return res;
}
//----------------micromouse------------------------------------------------------
Maze::Maze()
: cell(new uint8_t[buffsize]()),
ver_wall(new uint8_t[buffsize]()),
hor_wall(new uint8_t[buffsize]()){
	this->set_outer_wall();
}
Maze::Maze(const Maze& a) {
	this->cell = new uint8_t[buffsize]();
	this->ver_wall = new uint8_t[buffsize]();
	this->hor_wall = new uint8_t[buffsize]();//0埋め出来ている

	size_t size = sizeof(uint8_t);
	std::memcpy(this->cell,a.cell,size*buffsize);
	std::memcpy(this->ver_wall,a.ver_wall,size*buffsize);
	std::memcpy(this->hor_wall,a.hor_wall,size*buffsize);
}
Maze::~Maze() {
	delete[] cell;
	delete[] ver_wall;
	delete[] hor_wall;
}
Maze& Maze::operator=(const Maze& a)&{
	if (this == &a) return *this;//自己代入に気を付ける
	delete[] this->cell;
	delete[] this->ver_wall;
	delete[] this->hor_wall;

	this->cell = new uint8_t[buffsize];
	this->ver_wall = new uint8_t[buffsize];
	this->hor_wall = new uint8_t[buffsize];

	size_t size = sizeof(uint8_t);
	std::memcpy(this->cell,a.cell,size*buffsize);
	std::memcpy(this->ver_wall,a.ver_wall,size*buffsize);
	std::memcpy(this->hor_wall,a.hor_wall,size*buffsize);

	return *this;
}
void Maze::set_outer_wall() {
	for (int i = 0; i < FIELDSIZE;i++) {
		set_wall_status_xyd(0, i, 2, WALL_SEEN);
	}
	for (int i = 0; i < FIELDSIZE;i++) {
		set_wall_status_xyd(i, 0, 0, WALL_SEEN);
	}
}
void Maze::ind2xy(uint8_t i,uint8_t* x,uint8_t* y) const{
	*x = i & 15;
	*y = i >> 4;
}
uint8_t Maze::xy2ind(uint8_t x,uint8_t y) const{
	return wid * y + x;
}
int8_t Maze::get_wall_status_xyd(int8_t x_,int8_t y_,uint8_t dir)const {
	if (wid <= x_) {
		return -1;
	}
	if (hig <= y_) {
		return -1;
	}
	if (x_ < 0) {
		return -1;
	}
	if (y_ < 0) {
		return -1;
	}
	uint8_t x = static_cast<uint8_t>(x_);
	uint8_t y = static_cast<uint8_t>(y_);
	if ((0 <= dir) && (dir < 2)) {//hor
		y = y + (dir & 1);
		if (y == hig) {
			return WALL_SEEN;
		}
		uint8_t ind = xy2ind(x,y);
		return (hor_wall[ind >> 2] & mask[ind & 3]) >> (ind & 3) * 2;
	}
	else if ((2 <= dir) && (dir < 4)) {//ver
		x = x + (dir & 1);
		if (x == wid) {
			return WALL_SEEN;
		}
		uint8_t ind = xy2ind(x,y);
		return (ver_wall[ind >> 2] & mask[ind & 3]) >> (ind & 3) * 2;
	}
	else {
		return 0;
	}
}
int8_t Maze::get_wall_status_xyd(XY xy, uint8_t dir)const {
	return this->get_wall_status_xyd(xy.x,xy.y,dir);
}
int8_t Maze::get_wall_status_id(uint8_t index,uint8_t dir)const {
	if (wid * hig <= index) {
		return -1;
	}
	uint8_t x = 0;
	uint8_t y = 0;
	ind2xy(index,&x,&y);
	return get_wall_status_xyd(x, y, dir);
}
int8_t Maze::get_cell_status_xy(int8_t x_,int8_t y_)const{
	if (wid <= x_) {
		return -1;
	}
	if (hig <= y_) {
		return -1;
	}
	if (x_ < 0) {
		return -1;
	}
	if (y_ < 0) {
		return -1;
	}
	uint8_t index = 0;
	uint8_t x = static_cast<uint8_t>(x_);
	uint8_t y = static_cast<uint8_t>(y_);
	index = xy2ind(x, y);
	return get_cell_status_id(index);
}
int8_t Maze::get_cell_status_xy(XY xy)const {
	return this->get_cell_status_xy(xy.x,xy.y);
}
int8_t Maze::get_cell_status_id(uint8_t index)const{
	if (wid * hig <= index) {
		return -1;
	}
	return (cell[index >> 2] & mask[index & 3]) >> (index & 3) * 2;
}
int8_t Maze::set_wall_status_xyd(int8_t x_, int8_t y_, uint8_t dir,uint8_t val) {
	if (wid <= x_) {
		return -1;
	}
	if (hig <= y_) {
		return -1;
	}
	if (x_ < 0) {
		return -1;
	}
	if (y_ < 0) {
		return -1;
	}
	uint8_t x = static_cast<uint8_t>(x_);
	uint8_t y = static_cast<uint8_t>(y_);
	if ((0 <= dir) && (dir < 2)) {//hor
		y = y + (dir & 1);
		if (y == hig) {
			return 0;
		}
		uint8_t ind = xy2ind(x,y);
		hor_wall[ind >> 2] &= ~mask[ind & 3];
		hor_wall[ind >> 2] |= (val << (ind & 3) * 2);
		return 1;
	}
	else if ((2 <= dir) && (dir < 4)) {//ver
		x = x + (dir & 1);
		if (x == wid) {
			return 0;
		}
		uint8_t ind = xy2ind(x,y);
		ver_wall[ind >> 2] &= ~mask[ind & 3];
		ver_wall[ind >> 2] |= (val << (ind & 3) * 2);
		return 1;
	}
	else {
		return 0;
	}
}
int8_t Maze::set_wall_status_xyd(XY xy, uint8_t dir, uint8_t val) {
	return this->set_wall_status_xyd(xy.x,xy.y,dir,val);
}
int8_t Maze::set_wall_status_id(uint8_t index, uint8_t dir,uint8_t val) {
	if (wid * hig <= index) {
		return -1;
	}
	uint8_t x = 0;
	uint8_t y = 0;
	ind2xy(index, &x, &y);
	return set_wall_status_xyd(x,y,dir,val);
}
int8_t Maze::set_cell_status_xy(int8_t x_, int8_t y_,uint8_t val) {
	if (wid <= x_) {
		return -1;
	}
	if (hig <= y_) {
		return -1;
	}
	if (x_ < 0) {
		return -1;
	}
	if (y_ < 0) {
		return -1;
	}

	uint8_t index = 0;
	uint8_t x = static_cast<uint8_t>(x_);
	uint8_t y = static_cast<uint8_t>(y_);
	index = xy2ind(x, y);
	return set_cell_status_id(index,val);
}
int8_t Maze::set_cell_status_xy(XY xy,uint8_t val) {
	return this->set_cell_status_xy(xy.x,xy.y,val);
}
int8_t Maze::set_cell_status_id(uint8_t index,uint8_t val) {
	if (wid * hig <= index) {
		return -1;
	}
	cell[index >> 2] &= ~mask[index & 3];
	cell[index >> 2] |= (val << (index & 3) * 2);
	return 1;
}
//--------------------------------------------------------------
uint32_t Maze::register_maze(uint32_t addr){
	uint32_t next_addr = addr;
	for(int i = 0;i<16;i++){//ver
		next_addr = write_flash_words(next_addr,
				ver_wall[4*i+0],
				ver_wall[4*i+1],
				ver_wall[4*i+2],
				ver_wall[4*i+3]);
	}
	for(int i = 0;i<16;i++){//hor
		next_addr = write_flash_words(next_addr,
				hor_wall[4*i+0],
				hor_wall[4*i+1],
				hor_wall[4*i+2],
				hor_wall[4*i+3]);
	}
	for(int i = 0;i<16;i++){//cell
		next_addr = write_flash_words(next_addr,
				cell[4*i+0],
				cell[4*i+1],
				cell[4*i+2],
				cell[4*i+3]);
	}
	return next_addr;
}

void Maze::set_zero_cell_status(){
	delete[] this->cell;
	this->cell = new uint8_t[buffsize]();
}
