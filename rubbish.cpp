
/*for (int i = 0; i < 30; i++)
{
	for (int j = 0; j < 30; j++)
	{
		if (surface[i][j]==0 && steady_blocks[i][j] == true)
		{
			surface[i][j] = 1;
			print_pos(j * 2, i, "��");
		}

		if (surface[i][j] == 2)
		{
			print_pos(j * 2, i, "  ");
		}
	}
}


this->showDroping();
this->update_surface();*/
/*
	start = std::chrono::system_clock::now();	//һ�����俪ʼ��ʱ����ʱ������������

	Plate ori_droping_block = *_surface.droping_block;

	//��ʱ����ڣ����϶�ȡ�û����̲���
	while (!is_time_up(start, 2.0))
	{
		char operation = udlr();
		switch (operation)
		{
		case 'u':	//�ϼ���ʱ����ת90��
		{
			_surface.droping_block->rotate();
			//��������У���λ
			if (_surface.in_wall())
			{
				*_surface.droping_block = ori_droping_block;
			}
			break;
		}
		case 'd':	//�¼��½�һ��
		{
			_surface.droping_block->drop(speed);
			while (_surface.isBottom() == true)
				//��ֹ�ٶȹ��죬��������
			{
				_surface.droping_block->drop(-1);
			}
			break;
		}
		case 'l':	//�������һ��
		{
			_surface.droping_block->left();
			if (_surface.in_wall() || _surface.isBottom())
			{
				_surface.droping_block->right();
			}
			break;
		}
		case 'r':	//�Ҽ�����һ��
		{
			_surface.droping_block->right();
			if (_surface.in_wall() || _surface.isBottom())
			{
				_surface.droping_block->left();
			}
			break;
		}
		default:
			break;
		}

		//�������������Ļ
		system("cls");
		_surface.showSurface();
	}
*/

/*
			float score = 0;
			int speed = 1;
			//���ư���½�
			while (droping_block->isBottom(_surface.steady_blocks) == false)
			{
				droping_block->drop(speed);
			}

			while (droping_block->isBottom(_surface.steady_blocks) == true)
				//��ֹ�ٶȹ��죬��������
			{
				droping_block->drop(-1);
			}
		*/

		//bool ori_condition = _surface.isBottom();
					//while (_surface.isBottom())		//��ֹ�ٶȹ��죬��������
					//{
					//	_surface.droping_block->drop(-1);
					//	bool now_condition = _surface.isBottom();
					//	if (ori_condition == true && now_condition == false)
					//	{
					//		_surface.droping_block->drop(1);
					//		break;
					//	}
					//}
