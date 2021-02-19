#include"workerManager.h"

WorkerManager::WorkerManager()//���캯��
{
	//1.�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�
	
	if (!ifs.is_open())
	{
		//cout << "�ļ�������" << endl;

		//��ʼ������
		this->m_EmpNum = 0;//��ʼ������

		this->m_EmpArray = NULL;//��ʼ������

		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2.�ļ�����������Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//�ļ�Ϊ��
		//cout << "�ļ�Ϊ��" << endl;
		//��ʼ������
		this->m_EmpNum = 0;//��ʼ������

		this->m_EmpArray = NULL;//��ʼ������

		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	
	//3.�ļ�������������
	int num = this->get_EmpNum();
	//cout << "ְ��Ϊ" << num << endl;
	this->m_EmpNum = num;

	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();


	//���Դ���
	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "ְ����ţ�" << this->m_EmpArray[i]->m_Id << "\t"
			<< "ְ��������" << this->m_EmpArray[i]->m_Name << "\t"
			<< "���ű�ţ�" << this->m_EmpArray[i]->m_DeptId << endl;
	}*/
}

void WorkerManager::show_Menu()//չʾ�˵�
{
	cout << "*****************************************************" << endl;
	cout << "**************** ��ӭʹ��ְ������ϵͳ  **************" << endl;
	cout << "******************* 0.�˳�����ϵͳ ******************" << endl;
	cout << "******************* 1.����ְ����Ϣ ******************" << endl;
	cout << "******************* 2.��ʾְ����Ϣ ******************" << endl;
	cout << "******************* 3.ɾ��ְ����Ϣ ******************" << endl; 
	cout << "******************* 4.�޸�ְ����Ϣ ******************" << endl; 
	cout << "******************* 5.����ְ����Ϣ ******************" << endl;
	cout << "******************* 6.���ձ������ ******************" << endl;
	cout << "******************* 7.��������ĵ� ******************" << endl;
	cout << "*****************************************************" << endl;
	cout << endl;
}

void WorkerManager::ExitSystem()//�˳�����
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::Add_Emp()//���ְ��
{
	cout << "���������ְ��������" << endl;

	int addNum = 0;//�����û�����������
	cin >> addNum;

	if (addNum > 0)
	{
		//���
		//��������µĿռ��С
		int newSize = this->m_EmpNum + addNum;//�¿ռ����� = ԭ������ + ������

		//����
		Worker** newSpace = new Worker * [newSize];

		//��ԭ���ռ��µ����ݣ��������¿ռ���
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//���������
		for (int i = 0; i < addNum; i++)
		{
			int id;//���ű��
			string name;//��������
			int dSelect;//����ѡ��

			cout << "�������" << i + 1 << "��Ա����ţ�" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "��Ա��������" << endl;
			cin >> name;
			cout << "��ѡ��ְ����λ��" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			//��������ְ��ָ�룬������������
			newSpace[this->m_EmpNum + i] = worker;
		}

		//�ͷ�ԭ�еĿռ�
		delete[] this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		//�����µ�ְ������
		this->m_EmpNum = newSize;

		//�ɹ���Ӻ󱣴����ļ���
		this->save();

		//����ְ����Ϊ��-��־
		this->m_FileIsEmpty = false;

		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "��ְ��!" << endl;

	}
	else
	{
		cout << "������������" << endl;
	}

	//�����������
	system("pause");
	system("cls");

}

void WorkerManager::save()//�����ļ�
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//��д�ķ�ʽ��

	//��ÿ���˵�����д�뵽�ļ���
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	//�ر��ļ�
	ofs.close();
}

int WorkerManager::get_EmpNum()//ͳ������
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//�����ļ�

	int id;
	string name;
	int dId;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}

	return num;
}

void WorkerManager::init_Emp()//��ʼ��Ա��
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;

		if (dId == 1)//��ͨԱ��
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)//����
		{
			worker = new Manager(id, name, dId);
		}
		else//�ϰ�
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index++] = worker;
	}

	ifs.close();//�ر��ļ�
}

void WorkerManager::Show_Emp()//��ʾְ����Ա
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}

	//�����������
	system("pause");
	system("cls");
}

//����ְ������ж�ְ���Ƿ���ڣ������ڷ����±꣬�����ڷ���-1
int WorkerManager::IsExist(int id)
{
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//�ҵ�
			index = i;
			break;
		}
	}
	return index;
}

void WorkerManager::Del_Emp()//ɾ��ְ��
{
	if (this->m_FileIsEmpty)
	{
		//�ļ������ڻ��߼�¼Ϊ��
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else
	{
		//����ְ�����ɾ��
		cout << "��������Ҫɾ����ְ����ţ�" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1)//ְ�����ڣ�����ɾ��
		{
			//����ǰ��
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//����������Ա����

			//ͬ�����µ��ļ���
			this->save();

			cout << "ɾ���ɹ�!" << endl;
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}

	//�����������
	system("pause");
	system("cls");
}

void WorkerManager::Mod_Emp()//�޸�ְ��
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else
	{
		cout << "�������޸ĵ�Ա����ţ�" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//�ҵ�����

			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;
			
			cout << "�鵽��" << id << "��ְ������������ְ���ţ�" << endl;
			cin >> newId;

			cout << "�������µ�������" << endl;
			cin >> newName;

			cout << "�������µĸ�λ" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;
			 
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, 1);
				break;
			case 2:
				worker = new Manager(newId, newName, 2);
				break;
			case 3:
				worker = new Boss(newId, newName, 3);
				break;
			default:
				break;
			}

			//��������  ������
			this->m_EmpArray[ret] = worker;

			cout << "�޸ĳɹ�" << endl;

			//���浽�ļ���
			this->save();
		}
		else
		{//���Ҳ���
			cout << "���޴��ˣ��޸�ʧ�ܣ�" << endl;
		}
	}

	//�����������
	system("pause");
	system("cls");

}

void WorkerManager::Find_Emp()//����ְ��
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2����ְ����������" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			//���ձ�Ų���
			int id;
			cout << "��������Ҫ���ҵ�ְ����ţ�" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				//�ҵ�
				cout << "��ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				//δ�ҵ�
				cout << "����ʧ��,���޴���" << endl;
			}
		}
		else if (select == 2)
		{
			//������������
			string name;
			cout << "��������Ҫ���ҵ�ְ��������" << endl;
			cin >> name;

			//�����жϲ��ұ�־
			bool flag = false;//f-δ�ҵ�

			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ" << this->m_EmpArray[i]->m_Id 
						<< "����Ϣ���£�" << endl;

					//������ʾ��Ϣ�ӿ�
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "����ʧ�ܣ����޴��ˣ�" << endl;
			}
		}
		else
		{
			cout << "����ѡ������" << endl;
		}
	}

	//����������
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp()//����ְ��
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1����ְ����������" << endl;
		cout << "2����ְ���Ž�����" << endl;

		int select = 0;//�����û���ѡ��
		cin >> select;
		
		for (int i = 0; i < this->m_EmpNum - 1; i++)
		{
			int minOrMax = i;//������Сֵ�������ֵ�±�

			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//����
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else//����
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}

			//�ҵ���Сֵ�������±�  ��i���жԱ�
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "����ɹ���������Ϊ��" << endl;

		this->save();//�����Ľ���������ļ���

		this->Show_Emp();//չʾ����ְ��

		//��չʾְ�����а���������� �˴�����׸��
	}
}

void WorkerManager::Clean_File()//����ļ�
{
	cout << "ȷ����յ�ǰְ����Ϣ��" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2������" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//���
		ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ������´���
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//ɾ������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}

			//ɾ����������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}

		cout << "��ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager()//��������
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)//���ͷ������ڲ�
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray;
			}
		}
		//���ͷ����鱾��
		delete this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}