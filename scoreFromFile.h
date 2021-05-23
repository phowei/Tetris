#pragma once
#include <fstream>
#include <string>
using namespace std;

/*
* 编写score类，包含属性：姓名（string）m_player、成绩（float）m_score
* 
* 公共成员函数：
*	void showData(void)
*	string getName(void)const
*	float getScore(void)const
*	void setData(string name, float sc);
* 运算符重载：>  <
*/
class Score
{
public:
	Score(void) 
	{
		this->m_player = ""; 
		this->m_score = 0.0;
	}
	/*Score(string name = "", float sc = 0)
	{
		this->m_player = name;
		this->m_score = sc;
	}*/
	void showData(void);
	string getName(void)const { return this->m_player; }
	float getScore(void)const { return this->m_score; }
	void setData(string name, float sc);
	bool operator>(Score right);//运算符重载
	bool operator<(Score right);

private:
	string m_player;	//姓名
	float m_score;		//成绩
};

void addScore(Score& newScore);
Score* openScore(int& num);
int showScore();
void sorting_score(Score score[], const int num);
