#pragma once
#include "welcome.h"

void welcome()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	//设置蓝色
	cout << "\t\t00  00  0  0000000   00          0000      0000    00   000  0000000 " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	//设置颜色，没有添加颜色，故为原色
	cout << "\t\t00  00 00  00        00         00  00    00  00   00   000  00      " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	//设置红色
	cout << "\t\t00  00 00  00        00         0    0   00    0   00   000  00      " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	//设置蓝色
	cout << " \t\t0 000 00  00        00        00    00  00    00  000  000  00      " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
		FOREGROUND_BLUE);//设置绿色和蓝色相加
	cout << " \t\t0 000 00  00        00        00    00  0     00  000  000  00      " << endl;
	cout << " \t\t0 0 0 00  00        00        00        0     00  000  000  00      " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	//设置红色
	cout << " \t\t0 0 0 0   0000000   00        00        0     00  0 0 0000  0000000 " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
		FOREGROUND_GREEN);//设置红色和绿色相加
	cout << " \t\t000 000   00        00        00        0     00  0 0 0 00  00      " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
		FOREGROUND_BLUE);//设置红色和蓝色相加
	cout << " \t\t000 000   00        00        00    00  0     00  0 0 0 00  00      " << endl;
	cout << " \t\t000  00   00        00        00    00  00    00  0 000 00  00      " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
		FOREGROUND_GREEN);//设置红色和绿色相加
	cout << " \t\t000  00   00        00        00    0   00    0   0  00 00  00      " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN)
		;//设置绿色
	cout << "  \t\t0   00   00        00         00  00    00  00   0  00 00  00      " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
		FOREGROUND_GREEN | FOREGROUND_BLUE);//设置三色相加
	cout << "  \t\t0   00   00000000  00000000    0000      0000    0  0  00  00000000" << endl;
	
	cout << "\n\n按回车键继续：";
	getchar();
	system("cls");

}