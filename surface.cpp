#pragma once
using namespace std;
#include "surface.h"

void Surface::update_surface()
{
	/*for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (steady_blocks[i][j] == true)
				surface[i][j] = 1;
			if (surface[i][j] == 2)
				surface[i][j] = 0;
		}
	}*/
	int core_X = this->droping_block->get_core_X();
	int core_Y = this->droping_block->get_core_Y();
	surface[core_Y][core_X] = 2;
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)
	{
		int block_X = this->droping_block->get_block_X(i);
		int block_Y = this->droping_block->get_block_Y(i);
		surface[core_Y + block_Y][core_X + block_X] = 2;
	}
}

Surface::Surface()
{
	this->droping_block = this->_create(randnum(7), randnum(17));
	_isBottom = false;
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 20; j++)
		{

			this->steady_blocks[i][j] = false;
		}
	}
}

Surface::~Surface()
{
	this->droping_block->~Plate();
	delete this->droping_block;
	cout << "~界面已经退出..." << endl;
}

void Surface::showSurface()
{
	system("cls");
	print_pos(0, 0, "");
	this->showSteady();
	this->showDroping();
}
void Surface::showSteady() const
{
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (this->steady_blocks[i][j])
				print_pos(j * 2, i, "□");
		}
	}
}
void Surface::showDroping()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);//以黄色区分
	int core_X = this->droping_block->get_core_X();
	int core_Y = this->droping_block->get_core_Y();
	print_pos(core_X * 2, core_Y, "□");
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)
	{
		int block_X = this->droping_block->get_block_X(i);
		int block_Y = this->droping_block->get_block_Y(i);
		print_pos((block_X + core_X) * 2, block_Y + core_Y, "□");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//颜色调整回来
}

void Surface::insert_new(Plate ori_droping_block)
{
	int core_X = this->droping_block->get_core_X();
	int core_Y = this->droping_block->get_core_Y();
	if (core_Y < 0)//steady_blocks数组不存在负数索引
	{
		goto A_insert_new;
	}
	this->steady_blocks[core_Y][core_X] = true;
A_insert_new:
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)
	{
		int block_X = this->droping_block->get_block_X(i);
		int block_Y = this->droping_block->get_block_Y(i);
		if (core_Y < 0)//steady_blocks数组不存在负数索引
		{
			break;
		}
		this->steady_blocks[block_Y + core_Y][block_X + core_X] = true;
	}
}
void Surface::update_droping_block()
{
	delete this->droping_block;
	this->create();
}
bool Surface::update_steady_blocks()
{
	bool to_update = true;
	int core_X = this->droping_block->get_core_X();
	int core_Y = this->droping_block->get_core_Y();
	if (core_Y < 0 || core_Y >= 30)//steady_blocks数组不存在负数索引
	{
		goto A_update_steady_blocks;
	}
	to_update *= !(this->steady_blocks[core_Y][core_X]);

A_update_steady_blocks:
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)
	{
		int block_X = this->droping_block->get_block_X(i);
		int block_Y = this->droping_block->get_block_Y(i);
		if (core_Y + block_Y < 0 || core_Y + block_Y >= 30)//steady_blocks数组不存在负数索引
		{
			continue;
		}
		to_update *= !(this->steady_blocks[core_Y + block_Y][core_X + block_X]);
	}
	if (to_update == false)
	{
		return to_update;
	}

	cout << "***" << to_update;

	//droping_block所处位置上无方块，可写入

	if (core_Y < 0 || core_Y >= 30)//steady_blocks数组不存在负数索引
	{
		goto B_update_steady_blocks;
	}
	steady_blocks[core_Y][core_X] = true;

B_update_steady_blocks:
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)
	{
		int block_X = this->droping_block->get_block_X(i);
		int block_Y = this->droping_block->get_block_Y(i);
		if (core_Y + block_Y < 0 || core_Y + block_Y >= 30)//steady_blocks数组不存在负数索引
		{
			continue;
		}
		this->steady_blocks[core_Y + block_Y][core_X + block_X] = true;
	}
	return to_update;
}


/*
* 生成下一个出现的版块，随机生成7种版块之一，并判断生成处x坐标下是否合适
* 返回新版块的指针 —— Plate* droping_block
*/
void Surface::create()
{
	int plate_type = randnum(7);			//随机产生板块的类型
	int rand_x = 1 + randnum(17);			//随机产生板块的x坐标
	this->droping_block = nullptr;

	this->droping_block = _create(plate_type, rand_x);

	//是否与墙重合
	int move;
	if (this->in_wall(move))
	{
		delete this->droping_block;
		this->droping_block = this->_create(plate_type, rand_x - move);
	}

	//判断生成位置是否合适，左右调整
	if (this->is_dying() == false)
	{
		return;
	}
	else
	{
		//试图治疗
		bool nodead = false;
		int move2 = 0;
		//尝试左移
		for (int i = 1; i < rand_x; i++)
		{
			delete this->droping_block;
			this->droping_block = nullptr;
			this->droping_block = this->_create(plate_type, rand_x - i);
			if (this->is_dying() == false && this->in_wall() == false)
			{
				nodead = true;
				break;
			}
		}
		if (nodead == true)
		{
			return;
		}

		//尝试右移
		for (int i = rand_x + 1; i < 19; i++)
		{
			delete this->droping_block;
			this->droping_block = nullptr;
			this->droping_block = _create(plate_type, i);
			if (this->is_dying() == false
				&& this->in_wall() == false)
			{
				nodead = true;
				break;
			}
		}
		if (nodead == true)
		{
			return;
		}
		else
		{
			//救不活了
			delete this->droping_block;
			this->droping_block = nullptr;
			this->droping_block = this->_create(plate_type, rand_x - move);
			return;
		}
	}
}

//只生成版块的指针
Plate* Surface::_create(const int plate_type, const int rand_x)
{
	switch (plate_type)
	{
	case 0:
		return new Plate_l(rand_x);
		break;
	case 1:
		return new Plate_L(rand_x);
		break;
	case 2:
		return new Plate_O(rand_x);
		break;
	case 3:
		return new Plate_r(rand_x);
		break;
	case 4:
		return new Plate_S(rand_x);
		break;
	case 5:
		return new Plate_T(rand_x);
		break;
	case 6:
		return new Plate_Z(rand_x);
		break;
	default:
		return nullptr;
	}
}

bool Surface::is_dying()
{
	bool dying = false;		//判断是否会立即结束游戏
	int core_X = this->droping_block->get_core_X();
	if (this->steady_blocks[0][core_X])	//判断中心块对应纵坐标上有无方块
	{
		dying = true;
	}
	for (int i = 0; i < (*this->droping_block).get_blockNum(); i++)
		//判断其余块对应纵坐标上有无方块
	{
		int block_X = this->droping_block->get_block_X(i);
		if (this->steady_blocks[0][block_X + core_X])
		{
			dying = true;
		}
	}
	return dying;
}

//判断产生的版块是否与墙重合，并通过引用返回应该左右移动的值
bool Surface::in_wall(int& _move)
{
	bool in_wall = false;
	int move = 0;
	int core_X = (*this->droping_block).get_core_X();
	//先判断左墙
	if (core_X < 0)	//判断中心块
	{
		in_wall = true;
		move = core_X;
	}
	for (int i = 0; i < (*this->droping_block).get_blockNum(); i++)	//判断其余块
	{
		int block_X = this->droping_block->get_block_X(i);
		if (core_X + block_X < 0)
		{
			in_wall = true;
			//取右移最大值
			move = (
				(move < (core_X + block_X)) ?
				move :
				(core_X + block_X));
		}
	}
	if (move < 0)
	{
		_move = move;
		return in_wall;
	}

	//判断右墙
	in_wall = false;		//判断是否会立即结束游戏
	move = 0;
	if (core_X >= 20)	//判断中心块
	{
		in_wall = true;
		move = core_X - 19;
	}
	for (int i = 0; i < (*this->droping_block).get_blockNum(); i++)	//判断其余块
	{
		int block_X = this->droping_block->get_block_X(i);
		if (core_X + block_X >= 20)
		{
			in_wall = true;
			//取左移最大值
			move = (
				(move > (core_X + block_X - 19)) ?
				move :
				(core_X + block_X - 19));
		}
	}
	if (move > 0)
	{
		_move = move;
		return in_wall;
	}

	return in_wall;
}
//in_wall函数重载
bool Surface::in_wall()
{
	bool in_wall = false;
	int move = 0;
	int core_X = this->droping_block->get_core_X();
	//先判断左墙
	if (core_X < 0)	//判断中心块
	{
		in_wall = true;
		move = core_X;
	}
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)	//判断其余块
	{
		int block_X = this->droping_block->get_block_X(i);
		if (core_X + block_X < 0)
		{
			in_wall = true;
			//取右移最大值
			move = (
				(move < (core_X + block_X)) ?
				move :
				(core_X + block_X));
		}
	}
	if (move < 0)
	{
		return in_wall;
	}

	//判断右墙
	in_wall = false;		//判断是否会立即结束游戏
	move = 0;
	if (core_X >= 20)	//判断中心块
	{
		move = core_X - 19;
	}
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)	//判断其余块
	{
		int block_X = this->droping_block->get_block_X(i);
		if (core_X + block_X >= 20)
		{
			in_wall = true;
			//取右移最大值
			move = (
				(move > (core_X + block_X - 19)) ?
				move :
				(core_X + block_X - 19));
		}
	}
	if (move > 0)
	{
		return in_wall;
	}

	return in_wall;
}

int Surface::delete_line()
{
	int delete_line = 0;
	for (int y = 0; y < 30; y++)
	{
		bool to_delete = true;
		for (int x = 0; x < 20; x++)
		{
			to_delete *= this->steady_blocks[y][x];
		}
		if (to_delete == true)
		{
			for (int i = y; i > 0; i--)
			{
				for (int j = 0; j < 20; j++)
				{
					this->steady_blocks[i][j] = this->steady_blocks[i - 1][j];
				}
			}
			delete_line++;
			this->showSurface();
		}
	}
	return delete_line;
}

bool Surface::is_end()
{
	//若方块未到底，则未结束
	if (this->isBottom() == false &&
		this->is_doubling == false)
	{
		return false;
	}
	else
	{
		while (this->is_doubling)
		{
			this->droping_block->drop(-1);
			if (this->isBottom())
			{
				continue;
			}
		}

		if (this->droping_block->get_core_Y() - 1 < 0)
		{
			return true;
		}
		for (int i = 0; i < this->droping_block->get_blockNum(); i++)
		{
			if (this->droping_block->get_core_Y() +
				this->droping_block->get_block_Y(i) - 1 < 0)
			{
				return true;
			}
		}
	}
	return false;
}

bool Surface::isBottom()
{
	//原状态
	_isBottom = false;
	is_doubling = false;
	int core_X = this->droping_block->get_core_X();
	int core_Y = this->droping_block->get_core_Y();

	//先判断中心
	if (core_Y > 29)
	{
		_isBottom = true;
		is_doubling = true;
	}
	if (core_Y >= 0 && core_Y < 30 &&
		core_X >= 0 && core_X < 20)	//steady_blocks数组不存在负数索引
	{
		if (this->steady_blocks[core_Y][core_X] == true)
		{
			_isBottom = true;
			is_doubling = true;
		}
	}
	//判断其余方块
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)	//判断其余块
	{
		int block_X = this->droping_block->get_block_X(i);
		int block_Y = this->droping_block->get_block_Y(i);

		if (block_Y + core_Y > 29)
		{
			_isBottom = true;
			is_doubling = true;
		}
		if (core_Y + block_Y >= 0 && core_Y + block_Y < 30 &&
			core_X + block_X >= 0 && core_X + block_X < 20)	//steady_blocks数组不存在负数索引
		{
			if (steady_blocks[core_Y + block_Y][core_X + block_X] == true)
			{
				_isBottom = true;
				is_doubling = true;
			}
		}
	}
	if (_isBottom == true)
		return _isBottom;


	this->droping_block->drop(1);

	_isBottom = false;
	core_X = this->droping_block->get_core_X();
	core_Y = this->droping_block->get_core_Y();

	//先判断中心
	if (core_Y >= 30)
	{
		_isBottom = true;
		this->droping_block->drop(-1);
		return _isBottom;
	}
	if (core_Y >= 0 && core_Y < 30 &&
		core_X >= 0 && core_X < 20)	//steady_blocks数组不存在负数索引
	{
		if (this->steady_blocks[core_Y][core_X] == true)
		{
			_isBottom = true;
			this->droping_block->drop(-1);
			return _isBottom;
		}
	}
	//判断其余方块
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)	//判断其余块
	{
		int block_X = this->droping_block->get_block_X(i);
		int block_Y = this->droping_block->get_block_Y(i);

		if (block_Y + core_Y >= 30)
		{
			_isBottom = true;
			this->droping_block->drop(-1);
			return _isBottom;
		}
		if (core_Y + block_Y >= 0 && core_Y + block_Y < 30 &&
			core_X + block_X >= 0 && core_X + block_X < 20)	//steady_blocks数组不存在负数索引
		{
			if (steady_blocks[core_Y + block_Y][core_X + block_X] == true)
			{
				_isBottom = true;
				this->droping_block->drop(-1);
				return _isBottom;
			}
		}
	}

	this->droping_block->drop(-1);
	if (_isBottom == true)
		return _isBottom;
	else
		return _isBottom;
}

bool Surface::is_doubing()
{
	is_doubling = false;
	int core_X = this->droping_block->get_core_X();
	int core_Y = this->droping_block->get_core_Y();

	//先判断中心
	if (core_Y > 29)
	{
		is_doubling = true;
	}
	if (core_Y >= 0 && core_Y < 30 &&
		core_X >= 0 && core_X < 20)	//steady_blocks数组不存在负数索引
	{
		if (this->steady_blocks[core_Y][core_X] == true)
		{
			is_doubling = true;
		}
	}
	//判断其余方块
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)	//判断其余块
	{
		int block_X = this->droping_block->get_block_X(i);
		int block_Y = this->droping_block->get_block_Y(i);

		if (block_Y + core_Y > 29)
		{
			is_doubling = true;
		}
		if (core_Y + block_Y >= 0 && core_Y + block_Y < 30 &&
			core_X + block_X >= 0 && core_X + block_X < 20)	//steady_blocks数组不存在负数索引
		{
			if (steady_blocks[core_Y + block_Y][core_X + block_X] == true)
			{
				is_doubling = true;
			}
		}
	}
	return this->is_doubling;
}

int randnum(int upper_limit)
{
	int seed;
	seed = time(0);
	srand(seed);
	return rand() % upper_limit;
}

template<typename T>
void print_pos(int x, int y, T to_print)
{
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position{};		// position 是一个 COORD 结构
	position.X = x;		//设置列
	position.Y = y;		//设置行
	//将光标放在那里，然后开始打印
	SetConsoleCursorPosition(screen, position);
	cout << to_print << endl;

	position.X = 70;
	position.Y = 0;
	SetConsoleCursorPosition(screen, position);
}