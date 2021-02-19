#pragma once     //防止重复读取头文件 降低效率
#include<iostream>
#include<fstream>
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

#define FILENAME "empFile.txt"

using namespace std;

class WorkerManager
{
public:

	WorkerManager();//构造函数

	void show_Menu();//展示菜单

	void ExitSystem();//退出功能

	int m_EmpNum;//记录职工人数

	Worker** m_EmpArray;//职工数组指针

	void Add_Emp();//添加职工

	void save();//保存文件

	bool m_FileIsEmpty;//判断文件是否为空  标志

	int get_EmpNum();//统计人数

	void init_Emp();//初始化员工

	void Show_Emp();//显示职工成员

	void Del_Emp();//删除职工

	//按照职工编号判断职工是否存在，若存在返回下标，不存在返回-1
	int IsExist(int id);
	
	void Mod_Emp();//修改职工

	void Find_Emp();//查找职工

	void Sort_Emp();//排序职工

	void Clean_File();//清空文件

	~WorkerManager();//析构函数
};