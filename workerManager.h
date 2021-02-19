#pragma once     //��ֹ�ظ���ȡͷ�ļ� ����Ч��
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

	WorkerManager();//���캯��

	void show_Menu();//չʾ�˵�

	void ExitSystem();//�˳�����

	int m_EmpNum;//��¼ְ������

	Worker** m_EmpArray;//ְ������ָ��

	void Add_Emp();//���ְ��

	void save();//�����ļ�

	bool m_FileIsEmpty;//�ж��ļ��Ƿ�Ϊ��  ��־

	int get_EmpNum();//ͳ������

	void init_Emp();//��ʼ��Ա��

	void Show_Emp();//��ʾְ����Ա

	void Del_Emp();//ɾ��ְ��

	//����ְ������ж�ְ���Ƿ���ڣ������ڷ����±꣬�����ڷ���-1
	int IsExist(int id);
	
	void Mod_Emp();//�޸�ְ��

	void Find_Emp();//����ְ��

	void Sort_Emp();//����ְ��

	void Clean_File();//����ļ�

	~WorkerManager();//��������
};