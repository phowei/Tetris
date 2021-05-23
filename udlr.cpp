#pragma once
#include "udlr.h"
#include <iostream>
#include <conio.h>
#include <chrono>

/*
* up,down,left,right
* ¶ÁÈ¡¼üÅÌÊäÈë
*/
char udlr()
{
    char udlr = '0';
    if (_kbhit())
    {
        udlr = _getch();
        udlr = _getch();
        switch (udlr)
        {
        case 72:
            return 'u';
        case 80:
            return 'd';
        case 75:
            return 'l';
        case 77:
            return 'r';
        default:
            return -1;
        }
    }
    else
    {
        return -1;
    }
}