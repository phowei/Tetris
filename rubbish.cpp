
/*for (int i = 0; i < 30; i++)
{
	for (int j = 0; j < 30; j++)
	{
		if (surface[i][j]==0 && steady_blocks[i][j] == true)
		{
			surface[i][j] = 1;
			print_pos(j * 2, i, "□");
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
	start = std::chrono::system_clock::now();	//一次下落开始计时，计时结束，即下落

	Plate ori_droping_block = *_surface.droping_block;

	//计时间隔内，不断读取用户键盘操作
	while (!is_time_up(start, 2.0))
	{
		char operation = udlr();
		switch (operation)
		{
		case 'u':	//上键逆时针旋转90°
		{
			_surface.droping_block->rotate();
			//如果不可行，归位
			if (_surface.in_wall())
			{
				*_surface.droping_block = ori_droping_block;
			}
			break;
		}
		case 'd':	//下键下降一格
		{
			_surface.droping_block->drop(speed);
			while (_surface.isBottom() == true)
				//防止速度过快，调整回来
			{
				_surface.droping_block->drop(-1);
			}
			break;
		}
		case 'l':	//左键向左一格
		{
			_surface.droping_block->left();
			if (_surface.in_wall() || _surface.isBottom())
			{
				_surface.droping_block->right();
			}
			break;
		}
		case 'r':	//右键向右一格
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

		//将操作输出到屏幕
		system("cls");
		_surface.showSurface();
	}
*/

/*
			float score = 0;
			int speed = 1;
			//控制板块下降
			while (droping_block->isBottom(_surface.steady_blocks) == false)
			{
				droping_block->drop(speed);
			}

			while (droping_block->isBottom(_surface.steady_blocks) == true)
				//防止速度过快，调整回来
			{
				droping_block->drop(-1);
			}
		*/

		//bool ori_condition = _surface.isBottom();
					//while (_surface.isBottom())		//防止速度过快，调整回来
					//{
					//	_surface.droping_block->drop(-1);
					//	bool now_condition = _surface.isBottom();
					//	if (ori_condition == true && now_condition == false)
					//	{
					//		_surface.droping_block->drop(1);
					//		break;
					//	}
					//}
