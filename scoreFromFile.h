#pragma once
#include <fstream>
#include <string>
using namespace std;

/*
* ��дscore�࣬�������ԣ�������string��m_player���ɼ���float��m_score
* 
* ������Ա������
*	void showData(void)
*	string getName(void)const
*	float getScore(void)const
*	void setData(string name, float sc);
* ��������أ�>  <
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
	bool operator>(Score right);//���������
	bool operator<(Score right);

private:
	string m_player;	//����
	float m_score;		//�ɼ�
};

void addScore(Score& newScore);
Score* openScore(int& num);
int showScore();
void sorting_score(Score score[], const int num);
