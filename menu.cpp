#pragma once
#include "menu.h"

int showMenu()
{
	cout << "***********************************************" << endl;
	cout << "**************** 1、蝕兵嗄老 ******************" << endl;
	cout << "**************** 2、?塋廠票? ******************" << endl;
	cout << "**************** 3、曜竃嗄老 ******************" << endl;
	cout << "***********************************************" << endl;

	return getOrder();
}

int getOrder()
{
	char order = '0';
	while (1)
	{
		cout << "\n**************** 萩補秘會催?? *****************" << endl;
		cin.clear();
		cin >> order;
		if ('1' <= order && order <= '3')
			return order - '0';
		else
		{
			order = '0';
			cout << "會催嗤列??萩嶷仟補秘??" << endl;
		}
	}
}

void exit()
{
	system("cls");
	system("mode con cols=300 lines=15");
	cout << endl;
	cout << "      999999　　9999　　　99　　　　99　　9999999999　　　99　　　　99　　　　99　　　　99　　　9999999999　　　　99　　　9999　　99999999　　　　　99　　　　99　99999999　　　999999　　" << endl;
	cout << "  9999　　　　　9999　　　99　　　　99　9999　　　　9999　99　　　　99　　　　99　　　　99　　9999　　　　9999　　99　　　9999　99　　　99　　　　　99　　　　99　99　　　　9999" << endl;
	cout << "  99　　　　　　999999　　99　　　　99　99　　　　　　99　99　　　　99　　　　99　　　　99　　99　　　　　　99　　99　　　9999　99　　　99　　　　　99　　　　99　9999　　　　99　　" << endl;
	cout << "9999　　　　　　99　99　　99　　　　999999　　　　　　99999999　　　99　　　　9999　　　99　9999　　　　　　9999　99　　　9999　99　　　99　　　　　99　　　　99　9999　　　9999　" << endl;
	cout << "999999999999　　99　9999　99　　　　999999　　　　　　9999　99999999　　　　　　99999999　　9999　　　　　　9999　99　　　9999　9999999999　　　　　99　　　　99　9999999999999999999999" << endl;
	cout << "9999　　　　　　99　　99　99　　　　999999　　　　　　9999　　9999　　　　　　　　9999　　　9999　　　　　　9999　99　　　9999　99　　　99　　　　　99　　　　99　9999　　　9999" << endl;
	cout << "  99　　　　　　99　　999999　　　　99　99　　　　　　99　　　　99　　　　　　　　　99　　　　99　　　　　　99　　99　　　9999　99　　　9999　　　　99　　　　99　9999　　　　99" << endl;
	cout << "  9999　　　　　99　　　9999　　　99　　9999　　　　9999　　　　99　　　　　　　　　99　　　　9999　　　　9999　　99　　　99　　99　　　9999　　　　9999　　　99　9999　　　　9999" << endl;
	cout << "      999999　　99　　　9999　999999　　　　99999999　　　　　　99　　　　　　　　　99　　　　　　99999999　　　　　999999　　　99　　　9999　　　　　999999　99　9999　　　　　　999999" << endl;


	cout << endl;
	system("pause");
	exit(0);
}