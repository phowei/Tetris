#pragma once
using namespace std;
#include "play.h"
#include "Plate.h"

class Surface		//����Ļ����ʾ������
{
public:
	Plate* droping_block;
	bool steady_blocks[30][20];		//�Ѿ���صİ��
	int surface[30][20];

	void update_surface();
	 
	bool _isBottom;
	bool is_doubling;
	bool to_update;

	Surface();
	~Surface();

	void showSurface();
	void showSteady()const;
	void showDroping();

	void insert_new(Plate ori_droping_block);

	void update_droping_block();
	bool update_steady_blocks();

	void create();
	Plate* _create(const int plate_type, const int rand_x);

	bool is_dying();
	bool in_wall();
	bool in_wall(int& _move);
	int delete_line();
	bool is_end();
	bool isBottom();
	bool is_doubing();
};

//��������randnum����� 
int randnum(int upper_limit);

template<typename T>
void print_pos(int x, int y, T to_print);