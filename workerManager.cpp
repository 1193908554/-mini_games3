#include"workerManager.h"

WorkerManager::WorkerManager()//构造函数
{
	//1.文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件
	
	if (!ifs.is_open())
	{
		//cout << "文件不存在" << endl;

		//初始化属性
		this->m_EmpNum = 0;//初始化人数

		this->m_EmpArray = NULL;//初始化数组

		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2.文件存在且数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//文件为空
		//cout << "文件为空" << endl;
		//初始化属性
		this->m_EmpNum = 0;//初始化人数

		this->m_EmpArray = NULL;//初始化数组

		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	
	//3.文件存在且有数据
	int num = this->get_EmpNum();
	//cout << "职工为" << num << endl;
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();


	//测试代码
	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "职工编号：" << this->m_EmpArray[i]->m_Id << "\t"
			<< "职工姓名：" << this->m_EmpArray[i]->m_Name << "\t"
			<< "部门编号：" << this->m_EmpArray[i]->m_DeptId << endl;
	}*/
}

void WorkerManager::show_Menu()//展示菜单
{
	cout << "*****************************************************" << endl;
	cout << "**************** 欢迎使用职工管理系统  **************" << endl;
	cout << "******************* 0.退出管理系统 ******************" << endl;
	cout << "******************* 1.增加职工信息 ******************" << endl;
	cout << "******************* 2.显示职工信息 ******************" << endl;
	cout << "******************* 3.删除职工信息 ******************" << endl; 
	cout << "******************* 4.修改职工信息 ******************" << endl; 
	cout << "******************* 5.查找职工信息 ******************" << endl;
	cout << "******************* 6.按照编号排序 ******************" << endl;
	cout << "******************* 7.清空所有文档 ******************" << endl;
	cout << "*****************************************************" << endl;
	cout << endl;
}

void WorkerManager::ExitSystem()//退出功能
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void WorkerManager::Add_Emp()//添加职工
{
	cout << "请输入添加职工的数量" << endl;

	int addNum = 0;//保存用户的输入数量
	cin >> addNum;

	if (addNum > 0)
	{
		//添加
		//计算添加新的空间大小
		int newSize = this->m_EmpNum + addNum;//新空间人数 = 原来人数 + 新来的

		//开辟
		Worker** newSpace = new Worker * [newSize];

		//将原来空间下的数据，拷贝到新空间下
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;//部门编号
			string name;//部门姓名
			int dSelect;//部门选择

			cout << "请输入第" << i + 1 << "个员工编号：" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个员工姓名：" << endl;
			cin >> name;
			cout << "请选择职工岗位：" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
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

			//将创建的职工指针，保存在数组中
			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放原有的空间
		delete[] this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newSpace;

		//更改新的职工人数
		this->m_EmpNum = newSize;

		//成功添加后保存在文件中
		this->save();

		//更新职工不为空-标志
		this->m_FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加" << addNum << "名职工!" << endl;

	}
	else
	{
		cout << "输入数据有误" << endl;
	}

	//按任意键结束
	system("pause");
	system("cls");

}

void WorkerManager::save()//保存文件
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);//以写的方式打开

	//将每个人的数据写入到文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}

	//关闭文件
	ofs.close();
}

int WorkerManager::get_EmpNum()//统计人数
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读打开文件

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

void WorkerManager::init_Emp()//初始化员工
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;

		if (dId == 1)//普通员工
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2)//经理
		{
			worker = new Manager(id, name, dId);
		}
		else//老板
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index++] = worker;
	}

	ifs.close();//关闭文件
}

void WorkerManager::Show_Emp()//显示职工成员
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();
		}
	}

	//按任意键清屏
	system("pause");
	system("cls");
}

//按照职工编号判断职工是否存在，若存在返回下标，不存在返回-1
int WorkerManager::IsExist(int id)
{
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//找到
			index = i;
			break;
		}
	}
	return index;
}

void WorkerManager::Del_Emp()//删除职工
{
	if (this->m_FileIsEmpty)
	{
		//文件不存在或者记录为空
		cout << "文件不存在或者记录为空" << endl;
	}
	else
	{
		//按照职工编号删除
		cout << "请输入想要删除的职工编号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id);

		if (index != -1)//职工存在，现在删除
		{
			//数据前移
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;//更新数组人员个数

			//同步更新到文件中
			this->save();

			cout << "删除成功!" << endl;
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
	}

	//按任意键清屏
	system("pause");
	system("cls");
}

void WorkerManager::Mod_Emp()//修改职工
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空" << endl;
	}
	else
	{
		cout << "请输入修改的员工编号：" << endl;
		int id;
		cin >> id;

		int ret = this->IsExist(id);
		if (ret != -1)
		{
			//找到此人

			delete this->m_EmpArray[ret];

			int newId = 0;
			string newName = "";
			int dSelect = 0;
			
			cout << "查到：" << id << "号职工，请输入新职工号：" << endl;
			cin >> newId;

			cout << "请输入新的姓名：" << endl;
			cin >> newName;

			cout << "请输入新的岗位" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
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

			//更新数据  到数组
			this->m_EmpArray[ret] = worker;

			cout << "修改成功" << endl;

			//保存到文件中
			this->save();
		}
		else
		{//查找不到
			cout << "查无此人，修改失败！" << endl;
		}
	}

	//按任意键清屏
	system("pause");
	system("cls");

}

void WorkerManager::Find_Emp()//查找职工
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者记录为空" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按职工姓名查找" << endl;

		int select = 0;
		cin >> select;

		if (select == 1)
		{
			//按照编号查找
			int id;
			cout << "请输入需要查找的职工编号：" << endl;
			cin >> id;

			int ret = IsExist(id);
			if (ret != -1)
			{
				//找到
				cout << "该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				//未找到
				cout << "查找失败,查无此人" << endl;
			}
		}
		else if (select == 2)
		{
			//按照姓名查找
			string name;
			cout << "请输入需要查找的职工姓名：" << endl;
			cin >> name;

			//加入判断查找标志
			bool flag = false;//f-未找到

			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功，职工编号为" << this->m_EmpArray[i]->m_Id 
						<< "的信息如下：" << endl;

					//调用显示信息接口
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "查找失败，查无此人！" << endl;
			}
		}
		else
		{
			cout << "输入选项有误" << endl;
		}
	}

	//按任意清屏
	system("pause");
	system("cls");
}

void WorkerManager::Sort_Emp()//排序职工
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按职工号升序排" << endl;
		cout << "2、按职工号降序排" << endl;

		int select = 0;//接收用户的选择
		cin >> select;
		
		for (int i = 0; i < this->m_EmpNum - 1; i++)
		{
			int minOrMax = i;//声明最小值或者最大值下标

			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)//升序
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else//降序
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}

			//找到最小值或最大的下标  与i进行对比
			if (i != minOrMax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
		cout << "排序成功！排序结果为：" << endl;

		this->save();//排序后的结果保存在文件中

		this->Show_Emp();//展示所有职工

		//在展示职工中有按任意键清屏 此处不再赘述
	}
}

void WorkerManager::Clean_File()//清空文件
{
	cout << "确认清空当前职工信息？" << endl;
	cout << "1、确定" << endl;
	cout << "2、返回" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//清空
		ofstream ofs(FILENAME, ios::trunc);//删除文件后重新创建
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//删除堆区每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}

			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}

		cout << "清空成功！" << endl;
	}
	system("pause");
	system("cls");
}

WorkerManager::~WorkerManager()//析构函数
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)//先释放数组内部
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray;
			}
		}
		//在释放数组本身
		delete this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}