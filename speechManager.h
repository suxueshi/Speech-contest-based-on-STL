#pragma once
#include<iostream>
#include<vector>
#include<map>
#include"speaker.h"
#include<algorithm>
#include<deque>
#include<functional>
#include<numeric>
#include<ctime>
#include<fstream>
using namespace std;

class SpeechManager
{
public:
	//构造函数声明
	SpeechManager();

	//菜单功能声明
	void show_Menu();

	//退出功能声明
	void exitSystem();

	//创建比赛成员声明
	void createSpeaker();

	//开始比赛	比赛流程控制
	void startSpeech();

	//抽签函数声明
	void speechDraw();

	//比赛
	void speechContest();

	//显示比赛结果
	void shouScore();

	//保存记录
	void saveRecord();

	//读取往届记录
	void loadRecord();

	//文件为空的标志
	bool fileIsEmpty;

	//存放往届记录的容器
	map<int, vector<string>> m_Record;

	//显示往届记录
	void showRecord();

	//清空记录
	void clearRecord();

	//析构函数声明
	~SpeechManager();

	//初始化成员容器和属性函数声明
	void initSpeech();

	//成员属性
	//保存第一轮的比赛选手编号容器
	vector<int> v1;

	//第一轮晋级选手编号容器
	vector<int> v2;

	//胜出前三选手的编号容器
	vector<int> vVictory;

	//存放编号及对应选手容器
	map<int, Speaker>m_Speaker;

	//比赛轮数
	int index;

private:

};


