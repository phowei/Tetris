#pragma once
#include "scoreFromFile.h"
#include <iostream>
#include <string>
using namespace std;

void addScore(Score& newScore)
{
	int oriNum = 0;
	Score* oriScore = openScore(oriNum);
	int num = 1 + oriNum;
	Score* score = new Score[num];
	int index = 0;
	for (; index < oriNum; index++)
	{
		if (newScore.getScore() < oriScore[index].getScore())
		{
			score[index] = oriScore[index];
		}
		else
		{
			break;
		}
	}
	score[index] = newScore;
	index++;
	for (; index < num; index++)
	{
		score[index] = oriScore[index-1];
	}
	delete[] oriScore;
	oriScore = nullptr;

	sorting_score(score, num);

	ofstream write_to_file("score.txt");
	write_to_file << num << endl;
	for (int i = 0; i < num; i++)
	{
		write_to_file << score[i].getName() << "\t" << score[i].getScore() << endl;
	}
	write_to_file.close();
}

Score* openScore(int& num)
{
	num = 0;
	Score* score = nullptr;
	ifstream score_in_file("score.txt");
	int try_to_open = 0;
	if (score_in_file.is_open())
	{
		score_in_file >> num;
		score = new Score[num];
		string str;
		float sc = 0.0;
		for (int i = 0; i < num; i++)
		{
			score_in_file >> str >> sc;
			score[i].setData(str, sc);
		}
		score_in_file.close();
		return score;
	}
	else
	{
		while (!score_in_file.is_open())
		{
			cout << "文件打开失败，正在重试..." << endl;
			score_in_file.open("score.txt");
			try_to_open++;
			if (try_to_open > 50)
			{
				cout << "文件打开失败..." << endl;
				score_in_file.close();
				return score;
			}
		}
	}
	return score;
}

/*
* 打开score.txt文件，读取成绩
*
* 文件结构：
* == line 1：成绩记录数（整数）
* >= line 2：姓名\t成绩
*/
int showScore()
{
	int num = 0;
	Score* score = nullptr;
	ifstream score_in_file("score.txt");
	int try_to_open = 0;
	if (score_in_file.is_open())
	{
		score_in_file >> num;
		score = new Score[num];
		string str;
		float sc = 0.0;
		for (int i = 0; i < num; i++)
		{
			score_in_file >> str >> sc;
			score[i].setData(str, sc);
		}

		system("cls");
		cout << "共有 " << num << " 条记录" << endl << endl;
		cout << "名称\t成绩" << endl;

		score_in_file.close();

		for (int i = 0; i < num; i++)
		{
			score[i].showData();
		}

		system("pause");
		return num;
	}
	else
	{
		while (!score_in_file.is_open())
		{
			cout << "文件打开失败，正在重试..." << endl;
			score_in_file.open("score.txt");
			try_to_open++;
			if (try_to_open > 50)
			{
				cout << "文件打开失败..." << endl;
				score_in_file.close();
				return num;
			}
		}
	}
	return num;
}

void sorting_score(Score score[], const int num)
{
	//选择排序
	for (int i = 0; i < num; i++)
	{
		int max_index = i;
		for (int j = i + 1; j < num; j++)
		{
			//更新一轮选择中最大成绩的下标
			if (score[max_index] < score[j])
			{
				max_index = j;
			}
		}

		//交换
		Score temp = score[max_index];
		score[max_index] = score[i];
		score[max_index] = score[i];
		score[i] = temp;
	}
}

void Score::showData()
{
	cout << this->m_player << "\t" << this->m_score << endl;
}

void Score::setData(string name, float sc)
{
	this->m_player = name;
	this->m_score = sc;
}

bool Score::operator>(Score right)
{
	return (this->m_score > right.getScore()) ? true : false;
}

bool Score::operator<(Score right)
{
	return (this->m_score <right.getScore()) ? true : false;
}
