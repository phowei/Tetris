// Tetris.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "welcome.h"
#include "bgm.h"
#include "menu.h"
#include "scoreFromFile.h"
#include "play.h"
#include "surface.h"
using namespace std;

int main()
{
	playm();
	welcome();
	while(true)
	{
		int order = showMenu();
		cout << endl;

		switch (order)
		{
		case 1:
			start_new_play();
			break;
		case 2:
			showScore();
			break;
		case 3:
			exit();
		}
		system("cls");
	}
	
	return 0;
}


//						佛祖保佑~yo
// 
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               佛祖保佑         永无BUG
//
///////////////////////////////////////////////////////////