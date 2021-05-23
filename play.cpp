#pragma once
#include "play.h"
using namespace std;

/*
* 游戏开始入口
*/
void start_new_play(void)
{
	system("cls");
	print_pos(0, 0, "start...");
	std::this_thread::sleep_for(std::chrono::seconds(1));

	//在屏幕上显示的内容，包含在Surface类中，包括 已经落地的 以及 可操控的方块
	Surface _surface;

	float score = 0;		//本局游戏总分
	int speed = 1;			//下落速度，计划可调节

	//判断游戏是否结束，否则继续读键盘，执行操作
	while (false == _surface.is_end())		//一局游戏开始，将循环，直到方块堆到顶
	{
		if (_surface.is_end())
		{
			end_the_game(score);
			return;
		}
	new_block:

		//设置板块两次下落的时间间隔，利用C++ 11 chrono库
			//一次下落开始计时，计时结束，即下落
		std::chrono::time_point<std::chrono::system_clock> 
			start = std::chrono::system_clock::now();	
		char operation = '0';
		do
		{
			operation = udlr();
			if (operation != -1)
			{
				switch (operation)
				{
				case 'u':	//上键顺时针旋转90°
				{
					_surface.droping_block->rotate();
					//如果不可行，归位
					if (_surface.in_wall())
					{
						_surface.droping_block->rotate();
						_surface.droping_block->rotate();
						_surface.droping_block->rotate();
					}
					break;
				}
				case 'd':	//下键下降到底
				{
					int count = 0;
					while (!_surface.isBottom())
					{
						_surface.droping_block->drop(1);
						count++;
						if (count % 7 == 0) 
						{
							_surface.showSurface();
						}
					}

					if(_surface.is_doubing())
						_surface.droping_block->drop(-1);

					if (_surface.is_end())
					{
						end_the_game(score);
						return;
					}

					_surface.update_steady_blocks();
					_surface.update_droping_block();
					score += 20 * _surface.delete_line();					goto new_block;
				}
				case 'l':	//左键向左一格
				{
					_surface.droping_block->left();
					if (_surface.in_wall() ||					_surface.isBottom())
					{
						_surface.droping_block->right();
					}
					break;
				}
				case 'r':	//右键向右一格
				{
					_surface.droping_block->right();
					if (_surface.in_wall() ||					_surface.isBottom())
					{
						_surface.droping_block->left();
					}
					break;
				}
				}

				//将操作输出到屏幕
				_surface.showSurface();
			}

			if (is_time_up(start, 0.3))
				break;

		} while (true);

		if (_surface.is_end())
		{
			end_the_game(score);
			return;
		}

		//时间到，先判断是否已经到底，下降speed格
		if (_surface.isBottom())
		{
			if (_surface.is_doubing() == false)
			{
				_surface.update_steady_blocks();
				_surface.showSurface();
				_surface.update_droping_block();

				score += 20 * _surface.delete_line();
			}
			else
			{
				_surface.droping_block->drop(-1);
				_surface.update_steady_blocks();
				_surface.showSurface();
				_surface.update_droping_block();

				score += 20 * _surface.delete_line();
			}

			//判断游戏是否已经结束
			if (_surface.is_end())
			{
				end_the_game(score);
				return;
			}
			else
			{
				_surface.update_droping_block();

				score += 20 * _surface.delete_line();
				continue;
			}
		}
		//未到底
		else
		{
			_surface.droping_block->drop(speed);
			if (_surface.isBottom())
			{
				if (_surface.is_end())
				{
					end_the_game(score);
					return;
				}

				if (_surface.is_doubing() == false)
				{
					_surface.update_steady_blocks();
 					_surface.showSurface();
					_surface.update_droping_block();

					score += 20 * _surface.delete_line();
				}
				else
				{
					_surface.droping_block->drop(-1);
					_surface.update_steady_blocks();
					_surface.showSurface();
					_surface.update_droping_block();

					score += 20 * _surface.delete_line();
				}


				_surface.droping_block->drop(-1);
				_surface.update_steady_blocks();
				_surface.showSurface();
				_surface.update_droping_block();

				score += 20 * _surface.delete_line();
			}
			_surface.showSurface();
		}

	}


	score += 20 * _surface.delete_line();
	if (_surface.is_end())
	{
		end_the_game(score);
		return;
	}
}

void end_the_game(float score)
{
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position{};
	position.X = 0;
	position.Y = 32;
	SetConsoleCursorPosition(screen, position);

	cout << "**************** 游戏结束 ******************" << endl;

	cout << "您本次成绩为：" << score << endl;
	cout << "请输入您的姓名：";
	string name;
	cin >> name;
	Score newScore;
	newScore.setData(name, score);
	addScore(newScore);

	cout << "欢迎再次玩耍！" << endl;
	system("pause");
}

bool is_time_up(std::chrono::time_point<std::chrono::system_clock> start, float _elapsed)
{
	std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();;
	std::chrono::duration<double> elapsed = end - start;
	//cout << endl << elapsed.count() << endl;
	if (elapsed.count() < _elapsed)
		return false;
	else
		return true;
}
