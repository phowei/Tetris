#pragma once
#include "welcome.h"

void welcome()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	//������ɫ
	cout << "\t\t00  00  0  0000000   00          0000      0000    00   000  0000000 " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
	//������ɫ��û�������ɫ����Ϊԭɫ
	cout << "\t\t00  00 00  00        00         00  00    00  00   00   000  00      " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	//���ú�ɫ
	cout << "\t\t00  00 00  00        00         0    0   00    0   00   000  00      " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE);
	//������ɫ
	cout << " \t\t0 000 00  00        00        00    00  00    00  000  000  00      " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN |
		FOREGROUND_BLUE);//������ɫ����ɫ���
	cout << " \t\t0 000 00  00        00        00    00  0     00  000  000  00      " << endl;
	cout << " \t\t0 0 0 00  00        00        00        0     00  000  000  00      " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
	//���ú�ɫ
	cout << " \t\t0 0 0 0   0000000   00        00        0     00  0 0 0000  0000000 " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
		FOREGROUND_GREEN);//���ú�ɫ����ɫ���
	cout << " \t\t000 000   00        00        00        0     00  0 0 0 00  00      " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
		FOREGROUND_BLUE);//���ú�ɫ����ɫ���
	cout << " \t\t000 000   00        00        00    00  0     00  0 0 0 00  00      " << endl;
	cout << " \t\t000  00   00        00        00    00  00    00  0 000 00  00      " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
		FOREGROUND_GREEN);//���ú�ɫ����ɫ���
	cout << " \t\t000  00   00        00        00    0   00    0   0  00 00  00      " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN)
		;//������ɫ
	cout << "  \t\t0   00   00        00         00  00    00  00   0  00 00  00      " << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
		FOREGROUND_GREEN | FOREGROUND_BLUE);//������ɫ���
	cout << "  \t\t0   00   00000000  00000000    0000      0000    0  0  00  00000000" << endl;
	
	cout << "\n\n���س���������";
	getchar();
	system("cls");

}