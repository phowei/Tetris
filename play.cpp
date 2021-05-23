#pragma once
#include "play.h"
using namespace std;

/*
* ��Ϸ��ʼ���
*/
void start_new_play(void)
{
	system("cls");
	print_pos(0, 0, "start...");
	std::this_thread::sleep_for(std::chrono::seconds(1));

	//����Ļ����ʾ�����ݣ�������Surface���У����� �Ѿ���ص� �Լ� �ɲٿصķ���
	Surface _surface;

	float score = 0;		//������Ϸ�ܷ�
	int speed = 1;			//�����ٶȣ��ƻ��ɵ���

	//�ж���Ϸ�Ƿ������������������̣�ִ�в���
	while (false == _surface.is_end())		//һ����Ϸ��ʼ����ѭ����ֱ������ѵ���
	{
		if (_surface.is_end())
		{
			end_the_game(score);
			return;
		}
	new_block:

		//���ð�����������ʱ����������C++ 11 chrono��
			//һ�����俪ʼ��ʱ����ʱ������������
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
				case 'u':	//�ϼ�˳ʱ����ת90��
				{
					_surface.droping_block->rotate();
					//��������У���λ
					if (_surface.in_wall())
					{
						_surface.droping_block->rotate();
						_surface.droping_block->rotate();
						_surface.droping_block->rotate();
					}
					break;
				}
				case 'd':	//�¼��½�����
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
				case 'l':	//�������һ��
				{
					_surface.droping_block->left();
					if (_surface.in_wall() ||					_surface.isBottom())
					{
						_surface.droping_block->right();
					}
					break;
				}
				case 'r':	//�Ҽ�����һ��
				{
					_surface.droping_block->right();
					if (_surface.in_wall() ||					_surface.isBottom())
					{
						_surface.droping_block->left();
					}
					break;
				}
				}

				//�������������Ļ
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

		//ʱ�䵽�����ж��Ƿ��Ѿ����ף��½�speed��
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

			//�ж���Ϸ�Ƿ��Ѿ�����
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
		//δ����
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

	cout << "**************** ��Ϸ���� ******************" << endl;

	cout << "�����γɼ�Ϊ��" << score << endl;
	cout << "����������������";
	string name;
	cin >> name;
	Score newScore;
	newScore.setData(name, score);
	addScore(newScore);

	cout << "��ӭ�ٴ���ˣ��" << endl;
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
