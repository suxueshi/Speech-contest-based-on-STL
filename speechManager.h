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
	//���캯������
	SpeechManager();

	//�˵���������
	void show_Menu();

	//�˳���������
	void exitSystem();

	//����������Ա����
	void createSpeaker();

	//��ʼ����	�������̿���
	void startSpeech();

	//��ǩ��������
	void speechDraw();

	//����
	void speechContest();

	//��ʾ�������
	void shouScore();

	//�����¼
	void saveRecord();

	//��ȡ�����¼
	void loadRecord();

	//�ļ�Ϊ�յı�־
	bool fileIsEmpty;

	//��������¼������
	map<int, vector<string>> m_Record;

	//��ʾ�����¼
	void showRecord();

	//��ռ�¼
	void clearRecord();

	//������������
	~SpeechManager();

	//��ʼ����Ա���������Ժ�������
	void initSpeech();

	//��Ա����
	//�����һ�ֵı���ѡ�ֱ������
	vector<int> v1;

	//��һ�ֽ���ѡ�ֱ������
	vector<int> v2;

	//ʤ��ǰ��ѡ�ֵı������
	vector<int> vVictory;

	//��ű�ż���Ӧѡ������
	map<int, Speaker>m_Speaker;

	//��������
	int index;

private:

};


