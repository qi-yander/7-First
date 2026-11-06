#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include "EcoSystem.h"
#include "Organism.h"
#include "Grass.h"
#include "Wolf.h"
#include "Sheep.h"
using namespace std;

int main() {
	srand((unsigned)time(0));
	cout << "==========生态系统模拟系统==========\n" << endl;

	EcoSystem eco; // 创建生态系统驱动对象，所有数据都封装在这个对象内部

	//检测旧存档
	ifstream testFile("eco_save.txt");
	bool hasSave = testFile.good();
	testFile.close();
	bool loadSuccess = false;

	if (hasSave)
	{
		cout << "检测到存档文件，自动加载中..." << endl;
		ifstream fin("eco_save.txt");
		eco.loadEco(fin);
		fin.close();
		loadSuccess = true;
	}

	if (!loadSuccess)
	{
		int numWolves, numSheep, numGrass;
		cout << "请输入狼的数量："; cin >> numWolves;
		cout << "请输入羊的数量："; cin >> numSheep;
		cout << "请输入草的数量："; cin >> numGrass;
		eco.initEco(numWolves, numSheep, numGrass);
	}

	while (true)
	{
		int runTime;
		cout << "\n请输入模拟运行的时间（单位：天）："; cin >> runTime;

		//调用类方法执行模拟，main不再写模拟业务
		eco.runSimulation(runTime);

		cout << "----------模拟结束----------" << endl;
		int w, s, g;
		eco.showStatusAndCount(w, s, g);

		int op;
		cout << "\n=====操作菜单=====" << endl;
		cout << "0.退出 1.继续模拟  2.存档  3.读档 4.人工环境干预" << endl;
		cin >> op;
		if (op == 2)
		{
			ofstream fout("eco_save.txt");
			eco.saveEco(fout);
			fout.close();
			cout << "存档成功" << endl;
		}
		else if (op == 3)
		{
			ifstream fin("eco_save.txt");
			if (!fin.is_open())
			{
				cout << "读档失败！存档文件不存在" << endl;
			}
			else
			{
				eco.loadEco(fin);
			}
			fin.close();
		}
		else if (op == 4)
		{
			eco.manualIntervene();
		}
		else if (op == 0) {
			break;
		}
	}

	//退出自动存档
	ofstream fout("eco_save.txt");
	eco.saveEco(fout);
	fout.close();
	cout << "退出前已自动保存" << endl;

	//EcoSystem析构函数自动释放内存，main不用再手动delete全部生物
	return 0;
}