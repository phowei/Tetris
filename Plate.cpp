#pragma once
#include"Plate.h"


void Plate::rotate()
{
	for (int i = 0; i < this->get_blockNum(); i++)
	{
		int X = block[i].X;
		int Y = block[i].Y;
		block[i].X = X * roMax[0][0] + Y * roMax[1][0];
		block[i].Y = X * roMax[0][1] + Y * roMax[1][1];
	}
}

void Plate::set_core(int x, int y)
{
	core.X = x;
	core.Y = y;
}

Plate_l::Plate_l(int rand_x)
{
	core.X = rand_x;
	core.Y = -1;
	block[0].Y = block[1].Y = block[2].Y = 0;
	block[0].X = -1;
	block[1].X = 1;
	block[2].X = 2;
}

Plate_Z::Plate_Z(int rand_x)
{
	core.X = rand_x;	core.Y = -1;
	block[0].X = 1;		block[0].Y = 0;
	block[1].X = 0;		block[1].Y = -1;
	block[2].X = -1;	block[2].Y = -1;
}

Plate_T::Plate_T(int rand_x)
{
	core.X = rand_x;	core.Y = -1;
	block[0].X = -1;	block[0].Y = 0;
	block[1].X = 1;		block[1].Y = 0;
	block[2].X = 0;		block[2].Y = -1;
}

Plate_S::Plate_S(int rand_x)
{
	core.X = rand_x;	core.Y = -1;
	block[0].X = -1;	block[0].Y = 0;
	block[1].X = 0;		block[1].Y = -1;
	block[2].X = 1;		block[2].Y = -1;
}

Plate_O::Plate_O(int rand_x)
{
	core.X = rand_x;	core.Y = -1;
	block[0].X = 1;		block[0].Y = 0;
	block[1].X = 0;		block[1].Y = -1;
	block[2].X = 1;		block[2].Y = -1;
}

Plate_r::Plate_r(int rand_x)
{
	core.X = rand_x;	core.Y = -1;
	block[0].X = -1;	block[0].Y = -1;
	block[1].X = -1;	block[1].Y = 0;
	block[2].X = 1;		block[2].Y = 0;
}

Plate_L::Plate_L(int rand_x)
{
	core.X = rand_x;	core.Y = -1;
	block[0].X = 1;		block[0].Y = -1;
	block[1].X = 1;		block[1].Y = 0;
	block[2].X = -1;	block[2].Y = 0;
}