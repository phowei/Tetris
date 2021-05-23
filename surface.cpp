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
	cout << "~�����Ѿ��˳�..." << endl;
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
				print_pos(j * 2, i, "��");
		}
	}
}
void Surface::showDroping()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);//�Ի�ɫ����
	int core_X = this->droping_block->get_core_X();
	int core_Y = this->droping_block->get_core_Y();
	print_pos(core_X * 2, core_Y, "��");
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)
	{
		int block_X = this->droping_block->get_block_X(i);
		int block_Y = this->droping_block->get_block_Y(i);
		print_pos((block_X + core_X) * 2, block_Y + core_Y, "��");
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);//��ɫ��������
}

void Surface::insert_new(Plate ori_droping_block)
{
	int core_X = this->droping_block->get_core_X();
	int core_Y = this->droping_block->get_core_Y();
	if (core_Y < 0)//steady_blocks���鲻���ڸ�������
	{
		goto A_insert_new;
	}
	this->steady_blocks[core_Y][core_X] = true;
A_insert_new:
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)
	{
		int block_X = this->droping_block->get_block_X(i);
		int block_Y = this->droping_block->get_block_Y(i);
		if (core_Y < 0)//steady_blocks���鲻���ڸ�������
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
	if (core_Y < 0 || core_Y >= 30)//steady_blocks���鲻���ڸ�������
	{
		goto A_update_steady_blocks;
	}
	to_update *= !(this->steady_blocks[core_Y][core_X]);

A_update_steady_blocks:
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)
	{
		int block_X = this->droping_block->get_block_X(i);
		int block_Y = this->droping_block->get_block_Y(i);
		if (core_Y + block_Y < 0 || core_Y + block_Y >= 30)//steady_blocks���鲻���ڸ�������
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

	//droping_block����λ�����޷��飬��д��

	if (core_Y < 0 || core_Y >= 30)//steady_blocks���鲻���ڸ�������
	{
		goto B_update_steady_blocks;
	}
	steady_blocks[core_Y][core_X] = true;

B_update_steady_blocks:
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)
	{
		int block_X = this->droping_block->get_block_X(i);
		int block_Y = this->droping_block->get_block_Y(i);
		if (core_Y + block_Y < 0 || core_Y + block_Y >= 30)//steady_blocks���鲻���ڸ�������
		{
			continue;
		}
		this->steady_blocks[core_Y + block_Y][core_X + block_X] = true;
	}
	return to_update;
}


/*
* ������һ�����ֵİ�飬�������7�ְ��֮һ�����ж����ɴ�x�������Ƿ����
* �����°���ָ�� ���� Plate* droping_block
*/
void Surface::create()
{
	int plate_type = randnum(7);			//���������������
	int rand_x = 1 + randnum(17);			//�����������x����
	this->droping_block = nullptr;

	this->droping_block = _create(plate_type, rand_x);

	//�Ƿ���ǽ�غ�
	int move;
	if (this->in_wall(move))
	{
		delete this->droping_block;
		this->droping_block = this->_create(plate_type, rand_x - move);
	}

	//�ж�����λ���Ƿ���ʣ����ҵ���
	if (this->is_dying() == false)
	{
		return;
	}
	else
	{
		//��ͼ����
		bool nodead = false;
		int move2 = 0;
		//��������
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

		//��������
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
			//�Ȳ�����
			delete this->droping_block;
			this->droping_block = nullptr;
			this->droping_block = this->_create(plate_type, rand_x - move);
			return;
		}
	}
}

//ֻ���ɰ���ָ��
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
	bool dying = false;		//�ж��Ƿ������������Ϸ
	int core_X = this->droping_block->get_core_X();
	if (this->steady_blocks[0][core_X])	//�ж����Ŀ��Ӧ�����������޷���
	{
		dying = true;
	}
	for (int i = 0; i < (*this->droping_block).get_blockNum(); i++)
		//�ж�������Ӧ�����������޷���
	{
		int block_X = this->droping_block->get_block_X(i);
		if (this->steady_blocks[0][block_X + core_X])
		{
			dying = true;
		}
	}
	return dying;
}

//�жϲ����İ���Ƿ���ǽ�غϣ���ͨ�����÷���Ӧ�������ƶ���ֵ
bool Surface::in_wall(int& _move)
{
	bool in_wall = false;
	int move = 0;
	int core_X = (*this->droping_block).get_core_X();
	//���ж���ǽ
	if (core_X < 0)	//�ж����Ŀ�
	{
		in_wall = true;
		move = core_X;
	}
	for (int i = 0; i < (*this->droping_block).get_blockNum(); i++)	//�ж������
	{
		int block_X = this->droping_block->get_block_X(i);
		if (core_X + block_X < 0)
		{
			in_wall = true;
			//ȡ�������ֵ
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

	//�ж���ǽ
	in_wall = false;		//�ж��Ƿ������������Ϸ
	move = 0;
	if (core_X >= 20)	//�ж����Ŀ�
	{
		in_wall = true;
		move = core_X - 19;
	}
	for (int i = 0; i < (*this->droping_block).get_blockNum(); i++)	//�ж������
	{
		int block_X = this->droping_block->get_block_X(i);
		if (core_X + block_X >= 20)
		{
			in_wall = true;
			//ȡ�������ֵ
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
//in_wall��������
bool Surface::in_wall()
{
	bool in_wall = false;
	int move = 0;
	int core_X = this->droping_block->get_core_X();
	//���ж���ǽ
	if (core_X < 0)	//�ж����Ŀ�
	{
		in_wall = true;
		move = core_X;
	}
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)	//�ж������
	{
		int block_X = this->droping_block->get_block_X(i);
		if (core_X + block_X < 0)
		{
			in_wall = true;
			//ȡ�������ֵ
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

	//�ж���ǽ
	in_wall = false;		//�ж��Ƿ������������Ϸ
	move = 0;
	if (core_X >= 20)	//�ж����Ŀ�
	{
		move = core_X - 19;
	}
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)	//�ж������
	{
		int block_X = this->droping_block->get_block_X(i);
		if (core_X + block_X >= 20)
		{
			in_wall = true;
			//ȡ�������ֵ
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
	//������δ���ף���δ����
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
	//ԭ״̬
	_isBottom = false;
	is_doubling = false;
	int core_X = this->droping_block->get_core_X();
	int core_Y = this->droping_block->get_core_Y();

	//���ж�����
	if (core_Y > 29)
	{
		_isBottom = true;
		is_doubling = true;
	}
	if (core_Y >= 0 && core_Y < 30 &&
		core_X >= 0 && core_X < 20)	//steady_blocks���鲻���ڸ�������
	{
		if (this->steady_blocks[core_Y][core_X] == true)
		{
			_isBottom = true;
			is_doubling = true;
		}
	}
	//�ж����෽��
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)	//�ж������
	{
		int block_X = this->droping_block->get_block_X(i);
		int block_Y = this->droping_block->get_block_Y(i);

		if (block_Y + core_Y > 29)
		{
			_isBottom = true;
			is_doubling = true;
		}
		if (core_Y + block_Y >= 0 && core_Y + block_Y < 30 &&
			core_X + block_X >= 0 && core_X + block_X < 20)	//steady_blocks���鲻���ڸ�������
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

	//���ж�����
	if (core_Y >= 30)
	{
		_isBottom = true;
		this->droping_block->drop(-1);
		return _isBottom;
	}
	if (core_Y >= 0 && core_Y < 30 &&
		core_X >= 0 && core_X < 20)	//steady_blocks���鲻���ڸ�������
	{
		if (this->steady_blocks[core_Y][core_X] == true)
		{
			_isBottom = true;
			this->droping_block->drop(-1);
			return _isBottom;
		}
	}
	//�ж����෽��
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)	//�ж������
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
			core_X + block_X >= 0 && core_X + block_X < 20)	//steady_blocks���鲻���ڸ�������
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

	//���ж�����
	if (core_Y > 29)
	{
		is_doubling = true;
	}
	if (core_Y >= 0 && core_Y < 30 &&
		core_X >= 0 && core_X < 20)	//steady_blocks���鲻���ڸ�������
	{
		if (this->steady_blocks[core_Y][core_X] == true)
		{
			is_doubling = true;
		}
	}
	//�ж����෽��
	for (int i = 0; i < this->droping_block->get_blockNum(); i++)	//�ж������
	{
		int block_X = this->droping_block->get_block_X(i);
		int block_Y = this->droping_block->get_block_Y(i);

		if (block_Y + core_Y > 29)
		{
			is_doubling = true;
		}
		if (core_Y + block_Y >= 0 && core_Y + block_Y < 30 &&
			core_X + block_X >= 0 && core_X + block_X < 20)	//steady_blocks���鲻���ڸ�������
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
	COORD position{};		// position ��һ�� COORD �ṹ
	position.X = x;		//������
	position.Y = y;		//������
	//�����������Ȼ��ʼ��ӡ
	SetConsoleCursorPosition(screen, position);
	cout << to_print << endl;

	position.X = 70;
	position.Y = 0;
	SetConsoleCursorPosition(screen, position);
}