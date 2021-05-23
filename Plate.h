#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>
#include "windows.h"
using namespace std;

struct Point
{
	int X;
	int Y;
};

/*
* Plate�࣬��ʾ���µķ�����
*
* core ���� �������洢���ķ���ĺ�������
* rotate ���� ��ת�������������㣩����ʱ����ת90��
* isBottom ���� �ж��Ƿ񵽴�ײ�
* drop ���� �½�һ��
*/
class Plate :public Point
{
public:
	virtual void rotate();
	void drop(int speed)
	{
		this->core.Y += speed;
	}
	void left()
	{
		this->core.X--;
	}
	void right()
	{
		this->core.X++;
	}
	Plate(int x)
	{
		core.X = x;
		core.Y = -1;
	}
	Plate()
	{
		core.X = 0;
		core.Y = -1;
	}
	~Plate()
	{
		delete[] block;
		block = nullptr;
	}

	//��ȡ���Ŀ������
	int get_core_X()const { return this->core.X; }
	int get_core_Y()const { return this->core.Y; }
	void set_core(int x, int y);

	//��ȡ�����������
	int get_block_X(int i)const { return this->block[i].X; }
	int get_block_Y(int i)const { return this->block[i].Y; }

	int get_blockNum()const { return this->blockNum; }

	/*Plate& operator=(Plate right)
	{
		this->core = right.core;

		delete this->block;
		this->block = new Point;
		for (int i = 0; i < this->get_blockNum(); i++)
		{
			this->block->X = right.get_block_X(i);
			this->block->Y = right.get_block_Y(i);
		}
		return *this;
	}*/

protected:
	Point core;
	int roMax[2][2] = { {0 , 1},
					 {-1 , 0} };//��ת����
	static const int blockNum = 3;
	Point* block = new Point[blockNum];
};

/*
* ���� �������� �İ��
*/
class Plate_l :public Plate
{
public:
	Plate_l() {}
	Plate_l(int rand_x);
};

/*		 ��
* ���� ������ �İ��
*/
class Plate_T :public Plate
{
public:
	Plate_T() {}
	Plate_T(int rand_x);
};

/*	   ����
* ����	 ���� �İ��
*/
class Plate_Z :public Plate
{
public:
	Plate_Z() {}
	Plate_Z(int rand_x);
};

/*		����
* �������	�İ��
*/
class Plate_S :public Plate
{
public:
	Plate_S() {}
	Plate_S(int rand_x);
};

/*	   ����
* ���� ���� �İ��
*/
class Plate_O :public Plate
{
public:
	Plate_O() {}
	Plate_O(int rand_x);
};

/*	   ��
* ���� ������ �İ��
*/
class Plate_r :public Plate
{
public:
	Plate_r() {}
	Plate_r(int rand_x);
};

/*		   ��
* ���� ������ �İ��
*/
class Plate_L :public Plate
{
public:
	Plate_L() {}
	Plate_L(int rand_x);
};