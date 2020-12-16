#include"speechManager.h"

//构造函数实现
SpeechManager::SpeechManager()
{
	//初始化容器
	this->initSpeech();
	//创建初始的比赛选手
	this->createSpeaker();
	//读取往届记录
	this->loadRecord();
}

//菜单功能实现
void SpeechManager::show_Menu() {
	cout << "********************************************" << endl;
	cout << "*************  欢迎参加演讲比赛 ************" << endl;
	cout << "*************  1.开始演讲比赛  *************" << endl;
	cout << "*************  2.查看往届记录  *************" << endl;
	cout << "*************  3.清空比赛记录  *************" << endl;
	cout << "*************  0.退出比赛程序  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//退出功能实现
void SpeechManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);	//系统退出函数
}

//初始化容器和属性函数实现
void SpeechManager::initSpeech() {
	//将容器置空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//初始化比赛的轮数
	this->index = 1;

	//将记录的容器也清空
	this->m_Record.clear();
}

//创建比赛成员实现
void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); ++i) {
		//姓名种子取名字
		string name = "选手";
		name += nameSeed[i];
		Speaker sp;
		sp.m_Name = name;
		//初始化两轮得分为0
		for (int j = 0; j < 2; ++j) {
			sp.m_Score[j] = 0;
		}
		//12名选手编号
		this->v1.push_back(i + 10001);
		//把编号和对应的选手以对组的形式放到map容器中
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}

}

//开始比赛	比赛流程控制
void SpeechManager::startSpeech() {
	//第一轮比赛

	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示晋级结果
	this->shouScore();

	//第二轮比赛
	this->index++;

	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示最终结果
	this->shouScore();

	//保存比赛记录
	this->saveRecord();

	//重置比赛，获取记录
	//初始化容器和属性
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();

	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}

//抽签函数具体实现
void SpeechManager::speechDraw() {
	cout << "第 <<" << this->index << ">> 轮比赛选手正在抽签" << endl;
	cout << "----------------------------" << endl;
	cout << "抽签演讲顺序如下： " << endl;
	if (this->index == 1) {	//判断是第几轮
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); ++it) {
			cout << *it << " ";
		}
	}
	else {
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); ++it) {
			cout << *it << " ";
		}
	}
	cout << "--------------------------" << endl;
	system("pause");
	cout << endl;
}

//比赛具体实现
void SpeechManager::speechContest() {
	cout << "---------------第 <<" << this->index << ">> 轮比赛开始-----------------" << endl;
	multimap<double, int, greater<int>> groupScore;	//临时容器，用于保存分数（key）, 编号（value）greater<int> 表示按照key值的从大到小排列 也就是分数的从大到小排列
	vector<int> v_Src;	//比赛人员容器
	int num = 0;	//用于记录人员数，六个人为一组
	if (this->index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}
	//遍历所有参赛选手
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); ++it) {
		//评委打分
		deque<double> q;
		for (int i = 0; i < 10; ++i) {
			q.push_back((rand() % 401 + 600) / 10.f);	//随机打分	.f表示以小数形式存储表示
		}
		sort(q.begin(), q.end(), greater<double>());	//利用内建函数对象实现升序排列
		q.pop_front();	//去掉最高分
		q.pop_back();	//去掉最低分
		//求平均分
		double avg = accumulate(q.begin(), q.end(), 0)/(double)q.size();	//计算容器元素累加总和	第三个参数是起始累加值	相当于最后的结果再加参数三
		//把分数放入容器中
		this->m_Speaker[*it].m_Score[this->index - 1] = avg;

		//六个人一组，用临时容器保存
		num++;	//分组辅助记数
		groupScore.insert(make_pair(avg, *it));	//这个容器key值是分数，有可能一样所以用multimap，value值是编号
		if (num % 6 == 0) {
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end(); ++it) {
				cout << "编号：" << it->second << " 姓名：" << this->m_Speaker[it->second].m_Name << " 成绩：" << this->m_Speaker[(*it).second].m_Score[this->index - 1] << endl;
			}
			int count = 0;	//取前三名辅助记数
			//取前三名
			for (auto it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++) {
				if (this->index == 1) {
					v2.push_back((*it).second);
				}
				else {
					vVictory.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "--------------第" << this->index << "轮比赛完毕-------------------" << endl;
	system("pause");
}

//显示分数实现
void SpeechManager::shouScore() {
	cout << "--------------第" << this->index << "轮晋级的选手信息如下： -----------------" << endl;
	vector<int> v;
	if (this->index == 1) v = v2;
	else v = vVictory;
	for (auto it = v.begin(); it != v.end(); ++it) {
		cout << "选手编号： " << *it << " 姓名： " << this->m_Speaker[*it].m_Name << " 得分： " << this->m_Speaker[*it].m_Score[this->index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

//保存记录
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);	//以追加的方式写文件，其中csv格式的每条数据要用'，'隔开
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); ++it) {
		ofs << *it << ','
			<< this->m_Speaker[*it].m_Score[1] << ',';	//编号，分数，编号，分数
	}
	ofs << endl;	//一场比赛换一次行
	ofs.close();	//关闭文件
	cout << "记录已保存" << endl;
	this->fileIsEmpty = false;
}

//读取记录
void SpeechManager::loadRecord() {
	ifstream ifs;
	ifs.open("speech.csv", ios::in);	//输入流对象，读取文件
	//判断文件是否存在
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	//判断文件是否为空小技巧
	char ch;
	ifs >> ch;	//先读一个字符，如果直接读到文件尾 eof 则为空
	if (ifs.eof()) {
		//cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//如果上述两个条件都不满足，则标志位为false
	this->fileIsEmpty = false;
	ifs.putback(ch);	//把读取的单个字符放回去
	//读文件
	string data;
	int num_Game = 0;
	while (ifs >> data)
	{
		//cout << data << endl;
		//10010,86.375,10009,81,10002,78,
		vector<string> v;
		int pos = -1;	//记录逗号的位置
		int start = 0;	
		while (true)
		{
			pos = data.find(",", start);	//从0位置开始查找","
			if (pos == -1) {
				break;
			}
			string temp = data.substr(start, pos - start);	//找到了逗号就进行分割，参数1为起始位置，参数2为截取长度
			v.push_back(temp);
			start = pos + 1;
		}
		
		this->m_Record.insert(make_pair(num_Game, v));
		num_Game++;
	}
	ifs.close();
	//for (auto it = m_Record.begin(); it != m_Record.end(); ++it) {
	//	cout << it->first << "冠军编号： " << it->second[0] << endl;
	//}
}

//展示往届比赛记录
void SpeechManager::showRecord() {
	if (this->fileIsEmpty) {
		cout << "文件为空或者文件不存在！" << endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); ++i) { //把 int i 改成: map<int, vector<string>>::size_type 试一试
			cout << "第" << i + 1 << "届 " <<
				"冠军编号：" << this->m_Record[i][0] << " 得分：" << this->m_Record[i][1] << " "
				"亚军编号：" << this->m_Record[i][2] << " 得分：" << this->m_Record[i][3] << " "
				"季军编号：" << this->m_Record[i][4] << " 得分：" << this->m_Record[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord() {
	cout << "是否确定清空文件" << endl;
	cout << "1、是" << endl;
	cout << "2、否" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs("speech.csv", ios::trunc);	//打开模式ios::trunc 如果存在并删除文件重新创建
		ofs.close();

		//初始化属性 因为下面这些都是在构造函数里面的 程序开始的时候只会调用一次 要重新调用 
		this->initSpeech();

		//创建选手
		this->createSpeaker();

		//获取往届记录
		this->loadRecord();

		cout << "清楚成功" << endl;
	}
	system("pause");
	system("cls");
}

//析构函数实现
SpeechManager::~SpeechManager()
{
}

