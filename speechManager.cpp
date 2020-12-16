#include"speechManager.h"

//���캯��ʵ��
SpeechManager::SpeechManager()
{
	//��ʼ������
	this->initSpeech();
	//������ʼ�ı���ѡ��
	this->createSpeaker();
	//��ȡ�����¼
	this->loadRecord();
}

//�˵�����ʵ��
void SpeechManager::show_Menu() {
	cout << "********************************************" << endl;
	cout << "*************  ��ӭ�μ��ݽ����� ************" << endl;
	cout << "*************  1.��ʼ�ݽ�����  *************" << endl;
	cout << "*************  2.�鿴�����¼  *************" << endl;
	cout << "*************  3.��ձ�����¼  *************" << endl;
	cout << "*************  0.�˳���������  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}

//�˳�����ʵ��
void SpeechManager::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);	//ϵͳ�˳�����
}

//��ʼ�����������Ժ���ʵ��
void SpeechManager::initSpeech() {
	//�������ÿ�
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//��ʼ������������
	this->index = 1;

	//����¼������Ҳ���
	this->m_Record.clear();
}

//����������Աʵ��
void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); ++i) {
		//��������ȡ����
		string name = "ѡ��";
		name += nameSeed[i];
		Speaker sp;
		sp.m_Name = name;
		//��ʼ�����ֵ÷�Ϊ0
		for (int j = 0; j < 2; ++j) {
			sp.m_Score[j] = 0;
		}
		//12��ѡ�ֱ��
		this->v1.push_back(i + 10001);
		//�ѱ�źͶ�Ӧ��ѡ���Զ������ʽ�ŵ�map������
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}

}

//��ʼ����	�������̿���
void SpeechManager::startSpeech() {
	//��һ�ֱ���

	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ�������
	this->shouScore();

	//�ڶ��ֱ���
	this->index++;

	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ���ս��
	this->shouScore();

	//���������¼
	this->saveRecord();

	//���ñ�������ȡ��¼
	//��ʼ������������
	this->initSpeech();
	this->createSpeaker();
	this->loadRecord();

	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");
}

//��ǩ��������ʵ��
void SpeechManager::speechDraw() {
	cout << "�� <<" << this->index << ">> �ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "----------------------------" << endl;
	cout << "��ǩ�ݽ�˳�����£� " << endl;
	if (this->index == 1) {	//�ж��ǵڼ���
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

//��������ʵ��
void SpeechManager::speechContest() {
	cout << "---------------�� <<" << this->index << ">> �ֱ�����ʼ-----------------" << endl;
	multimap<double, int, greater<int>> groupScore;	//��ʱ���������ڱ��������key��, ��ţ�value��greater<int> ��ʾ����keyֵ�ĴӴ�С���� Ҳ���Ƿ����ĴӴ�С����
	vector<int> v_Src;	//������Ա����
	int num = 0;	//���ڼ�¼��Ա����������Ϊһ��
	if (this->index == 1) {
		v_Src = v1;
	}
	else {
		v_Src = v2;
	}
	//�������в���ѡ��
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); ++it) {
		//��ί���
		deque<double> q;
		for (int i = 0; i < 10; ++i) {
			q.push_back((rand() % 401 + 600) / 10.f);	//������	.f��ʾ��С����ʽ�洢��ʾ
		}
		sort(q.begin(), q.end(), greater<double>());	//�����ڽ���������ʵ����������
		q.pop_front();	//ȥ����߷�
		q.pop_back();	//ȥ����ͷ�
		//��ƽ����
		double avg = accumulate(q.begin(), q.end(), 0)/(double)q.size();	//��������Ԫ���ۼ��ܺ�	��������������ʼ�ۼ�ֵ	�൱�����Ľ���ټӲ�����
		//�ѷ�������������
		this->m_Speaker[*it].m_Score[this->index - 1] = avg;

		//������һ�飬����ʱ��������
		num++;	//���鸨������
		groupScore.insert(make_pair(avg, *it));	//�������keyֵ�Ƿ������п���һ��������multimap��valueֵ�Ǳ��
		if (num % 6 == 0) {
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double, int, greater<int>>::iterator it = groupScore.begin(); it != groupScore.end(); ++it) {
				cout << "��ţ�" << it->second << " ������" << this->m_Speaker[it->second].m_Name << " �ɼ���" << this->m_Speaker[(*it).second].m_Score[this->index - 1] << endl;
			}
			int count = 0;	//ȡǰ������������
			//ȡǰ����
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
	cout << "--------------��" << this->index << "�ֱ������-------------------" << endl;
	system("pause");
}

//��ʾ����ʵ��
void SpeechManager::shouScore() {
	cout << "--------------��" << this->index << "�ֽ�����ѡ����Ϣ���£� -----------------" << endl;
	vector<int> v;
	if (this->index == 1) v = v2;
	else v = vVictory;
	for (auto it = v.begin(); it != v.end(); ++it) {
		cout << "ѡ�ֱ�ţ� " << *it << " ������ " << this->m_Speaker[*it].m_Name << " �÷֣� " << this->m_Speaker[*it].m_Score[this->index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();
}

//�����¼
void SpeechManager::saveRecord() {
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);	//��׷�ӵķ�ʽд�ļ�������csv��ʽ��ÿ������Ҫ��'��'����
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); ++it) {
		ofs << *it << ','
			<< this->m_Speaker[*it].m_Score[1] << ',';	//��ţ���������ţ�����
	}
	ofs << endl;	//һ��������һ����
	ofs.close();	//�ر��ļ�
	cout << "��¼�ѱ���" << endl;
	this->fileIsEmpty = false;
}

//��ȡ��¼
void SpeechManager::loadRecord() {
	ifstream ifs;
	ifs.open("speech.csv", ios::in);	//���������󣬶�ȡ�ļ�
	//�ж��ļ��Ƿ����
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	//�ж��ļ��Ƿ�Ϊ��С����
	char ch;
	ifs >> ch;	//�ȶ�һ���ַ������ֱ�Ӷ����ļ�β eof ��Ϊ��
	if (ifs.eof()) {
		//cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}
	//����������������������㣬���־λΪfalse
	this->fileIsEmpty = false;
	ifs.putback(ch);	//�Ѷ�ȡ�ĵ����ַ��Ż�ȥ
	//���ļ�
	string data;
	int num_Game = 0;
	while (ifs >> data)
	{
		//cout << data << endl;
		//10010,86.375,10009,81,10002,78,
		vector<string> v;
		int pos = -1;	//��¼���ŵ�λ��
		int start = 0;	
		while (true)
		{
			pos = data.find(",", start);	//��0λ�ÿ�ʼ����","
			if (pos == -1) {
				break;
			}
			string temp = data.substr(start, pos - start);	//�ҵ��˶��žͽ��зָ����1Ϊ��ʼλ�ã�����2Ϊ��ȡ����
			v.push_back(temp);
			start = pos + 1;
		}
		
		this->m_Record.insert(make_pair(num_Game, v));
		num_Game++;
	}
	ifs.close();
	//for (auto it = m_Record.begin(); it != m_Record.end(); ++it) {
	//	cout << it->first << "�ھ���ţ� " << it->second[0] << endl;
	//}
}

//չʾ���������¼
void SpeechManager::showRecord() {
	if (this->fileIsEmpty) {
		cout << "�ļ�Ϊ�ջ����ļ������ڣ�" << endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); ++i) { //�� int i �ĳ�: map<int, vector<string>>::size_type ��һ��
			cout << "��" << i + 1 << "�� " <<
				"�ھ���ţ�" << this->m_Record[i][0] << " �÷֣�" << this->m_Record[i][1] << " "
				"�Ǿ���ţ�" << this->m_Record[i][2] << " �÷֣�" << this->m_Record[i][3] << " "
				"������ţ�" << this->m_Record[i][4] << " �÷֣�" << this->m_Record[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}

void SpeechManager::clearRecord() {
	cout << "�Ƿ�ȷ������ļ�" << endl;
	cout << "1����" << endl;
	cout << "2����" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs("speech.csv", ios::trunc);	//��ģʽios::trunc ������ڲ�ɾ���ļ����´���
		ofs.close();

		//��ʼ������ ��Ϊ������Щ�����ڹ��캯������� ����ʼ��ʱ��ֻ�����һ�� Ҫ���µ��� 
		this->initSpeech();

		//����ѡ��
		this->createSpeaker();

		//��ȡ�����¼
		this->loadRecord();

		cout << "����ɹ�" << endl;
	}
	system("pause");
	system("cls");
}

//��������ʵ��
SpeechManager::~SpeechManager()
{
}

