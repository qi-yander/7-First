#include <iostream>//输入输出流
#include <cstdlib>//C标准库，rand随机函数就在这里
#include <ctime>//时间库，用来放srand（time（NULL）），即拿时间当随机种子
#include<vector>//动态数组，用vector存群体
#include "wolf.h"
#include "Sheep.h"
using namespace std;
int main() {
	srand((unsigned)time(0));
	//time（0）是ctime里的函数，返回当前系统时间（从1970年到现在一共多少秒）
	//srand是设计随机数种子，为rand函数提供一个随机种子，保证它从不同的起点开始生成随机数
	//（unsigned）是强制类型转换，time（0）返回的是long型，srand需要unsigned型，所以要转换一下
	cout << "==========生态系统模拟系统==========\n" << endl;
	int numWolves, numSheeps, runTime;
	cout << "请输入狼的数量：";cin >> numWolves;
	cout << "请输入羊的数量：";cin >> numSheeps;
	vector <Wolf*>wolves;
	//vector是动态数组模板，（Wolf*）表示该数组存放的是Wolf类的指针，wolves是该数组的名字
	vector <Sheep*>sheeps;
	string areas[] = { "东区","西区","南区","北区","中央区" };
	cout << "\n----------生态系统初始化----------" << endl;
	for (int i = 0;i < numWolves;i++) {
		wolves.push_back(new Wolf(string("大灰狼") + to_string(i + 1), (rand() % 2 == 0) ? "雄性" : "雌性", rand() % 10 + 1, rand() % 100 + 1, areas[rand() % 5]));
		//以上句子就是在往wolves这个数组里增添一只新的大灰狼i+1，性别年龄血量与所在区域都是随机的
		//.push_back是vector的成员函数，表示在数组末尾添加一个元素
		//由于vector里的元素是狼的指针，所以数组里存的就是新狼的地址
		wolves.back()->showStatus();
		//.back()是vector的成员函数，表示返回数组最后一个元素的引用
	}
	for (int i = 0;i < numSheeps;i++) {
		sheeps.push_back(new Sheep(string("小羊") + to_string(i + 1), (rand() % 2 == 0) ? "雄性" : "雌性", rand() % 10 + 1, rand() % 100 + 1, areas[rand() % 5]));
		sheeps.back()->showStatus();
	}
	cout << "\n请输入模拟运行的时间（单位：天）：";cin >> runTime;
	for (int t = 1;t <= runTime;t++) {
		cout << "\n----------第" << t << "天----------" << endl;
		//移动阶段
		for (auto w : wolves)
			w->move();
		for (auto s : sheeps)
			s->move();
		//捕食阶段
		for (auto w : wolves) { //用auto逐个取出wolves数组里的每一只狼，w就是当前的狼，执行w->hunt
			if (!w->isAlive())
				continue;
			for (auto s : sheeps) {
				w->hunt(s);
			}
		}
		//以上每一只活着的狼都会尝试去捕猎每一只羊
		//繁殖阶段
		cout << "\n----------繁殖阶段----------" << endl;
		//羊繁殖
		for (size_t i = 0;i < sheeps.size();i++) {
			for (size_t j = i + 1;j < sheeps.size();j++) {
				if (sheeps[i]->canReproduce(sheeps[j])) {
					cout << sheeps[i]->getName() << "和" << sheeps[j]->getName() << "在" << sheeps[i]->getPosition() << "繁殖了！" << endl;
					sheeps[i]->setHealth(sheeps[i]->gethealth() - 10);
					sheeps[j]->setHealth(sheeps[j]->gethealth() - 10);
					sheeps.push_back(new Sheep(string("小羊") + to_string(sheeps.size() + 1), (rand() % 2 == 0) ? "雄性" : "雌性", 0, 100, sheeps[i]->getPosition()));
				}
			}
		}
		//狼繁殖
		for (size_t i = 0;i < wolves.size();i++) {
			for (size_t j = 0;j < wolves.size();j++) {
				if (wolves[i]->canReproduce(wolves[j])) {
					cout << wolves[i]->getName() << wolves[j]->getName() << "在" << wolves[i]->getPosition() << "繁殖了！" << endl;
					wolves[i]->setHealth(wolves[i]->gethealth() - 10);
					wolves[j]->setHealth(wolves[j]->gethealth() - 10);
					wolves.push_back(new Wolf(string("大灰狼") + to_string(wolves.size() + 1), (rand() % 2 == 0) ? "雄性" : "雌性", 0, 100, wolves[i]->getPosition()));
				}
			}
		}
		//以上每一只羊都会尝试与其他羊繁殖，每一只狼也会尝试与其他狼繁殖
		cout << "----------模拟结束----------" << endl;
		cout << "-----------当前生态系统状态----------" << endl;
		cout << "大灰狼群：" << endl;
		int wolfCount = 0;
		for (auto w : wolves) {
			w->showStatus();
			if (w->isAlive())
				wolfCount++;
		}
		cout << "存活数量" << wolfCount << endl;
		cout << "小羊群：" << endl;
		int sheepCount = 0;
		for (auto s : sheeps) {
			s->showStatus();
			if (s->isAlive())
				sheepCount++;
		}
		cout << "存活数量" << sheepCount << endl;
		//以上每一只狼和羊都会显示自己的状态，并统计存活数量
	}
		//释放内存
		for (auto w : wolves)
			delete w;
		for (auto s : sheeps)
			delete s;
		return 0;
}