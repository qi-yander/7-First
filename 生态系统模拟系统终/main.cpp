#include <iostream>//输入输出流
#include <cstdlib>//C标准库，rand随机函数就在这里
#include <ctime>//时间库，用来放srand（time（NULL）），即拿时间当随机种子
#include <vector>//动态数组，用vector存群体
#include <fstream>
#include "Organism.h"
#include "Grass.h"
#include "Wolf.h"
#include "Sheep.h"
using namespace std;
//存档函数 
void saveEco(vector<Organism*>& ecosystem)//&是引用，直接操作原来的容器
{
	ofstream fout("eco_save.txt");//创建一个输出文件流对象fout，打开文件eco_save.txt
	for(auto o:ecosystem)//遍历生态系统里的每一个生物对象o
		o->save(fout);//，调用它们的save函数，把它们的数据写入文件fout
	    fout.close();//关闭文件，保存数据
}
//读档函数
void loadEco(vector<Organism*>& ecosystem)
{
	// 先清空当前生态（释放原有内存）
	for (auto org : ecosystem)//遍历生态系统里的每一个生物对象org
	{
		delete org;//释放该对象占用的内存
	}
	ecosystem.clear();//清空生态系统容器，删除对象指针

	ifstream fin("eco_save.txt");//创建文件读取流对象fin，打开文件eco_save.txt
	if (!fin.is_open())
	{
		cout << "读档失败！存档文件不存在" << endl;
		return;
	}
	string type;
	while (fin >> type)
	{
		if (type == "Grass")
		{
			Grass* g = new Grass("", 0, "");
			g->load(fin);//调用草的load函数，从文件fin读取草的数据
			ecosystem.push_back(g);//把新创建的草对象g加入到生态系统容器ecosystem中
		}
		else if (type == "Sheep")
		{
			Sheep* s = new Sheep("", "", 0, 0, "");
			s->load(fin);
			ecosystem.push_back(s);
		}
		else if (type == "Wolf")
		{
			Wolf* w= new Wolf("", "", 0, 0, "");
			w->load(fin);
			ecosystem.push_back(w);
		}
	}
	fin.close();//关闭读文件流
	cout<< "读档成功！继续生态模拟" << endl;
}
//清理死亡的生物
void clearDeadOrg(vector<Organism*>& ecosystem)
{
	cout << "\n----------清理死亡的生物----------" << endl;
	bool hasDead = false;
	for (auto it = ecosystem.begin(); it != ecosystem.end();)
	{
		if (!(*it)->isAlive())
		{
			cout << (*it)->getName() << "已死亡，清理出生态系统。" << endl;
			hasDead = true;
			delete* it;
			it = ecosystem.erase(it);
		}
		else
		{
			++it;
		}
	}
	if (!hasDead) {
		cout << "没有死亡的生物需要清理。" << endl;
	}
}
//人工天气干预
void manualIntervene(vector<Organism*>& ecosystem) {
	cout << "\n=====人工干预=====" << endl;
	cout << "1.人工捕食  2.自然灾害" << endl;
	int choice; cin >> choice;
	string areas[] = { "东区","西区","南区","北区","中央区" };
	if (choice == 1) {
		cout << "选择区域：1.东区 2.西区 3.南区 4.北区 5.中央区" << endl;
		int a; cin >> a;
		string target = areas[a - 1];
		int killed = 0;//计算被捕杀动物的数量
		for (auto org : ecosystem) {
			if (org->isAlive() && org->getPosition() == target &&
				(dynamic_cast<Sheep*>(org) || dynamic_cast<Wolf*>(org))) {
				if (rand() % 3 == 0) {//33%捕杀成功率
					org->kill();
					cout << "人工捕杀了" << org->getName() << "（" << target << "）" << endl;
					killed++;
				}
			}
		}
		cout << "人工捕食结束，共捕杀" << killed << "只动物" << endl;
	}
	else if (choice == 2) {
		int disaster = rand() % 3;//随机降临三种灾害之一
		if (disaster == 0) {
			cout << "=====干旱降临！=====" << endl;
			for (auto org : ecosystem) {
				Grass* g = dynamic_cast<Grass*>(org);
				if (g && g->isAlive() && rand() % 2 == 0) {//存活的草有50%概率因干旱死亡
					g->kill();
					cout << "干旱导致" << g->getName() << "枯萎死亡" << endl;
				}
			}
		}
		else if (disaster == 1) {
			cout << "=====瘟疫蔓延！=====" << endl;
			for (auto org : ecosystem) {
				if (org->isAlive() && rand() % 5 == 0) {
					org->kill();
					cout << "瘟疫导致" << org->getName() << "死亡" << endl;
				}
			}
		}
		else {
			cout << "=====暴风雪来袭！=====" << endl;
			for (auto org : ecosystem) {
				if (org->isAlive() &&
					(dynamic_cast<Sheep*>(org) || dynamic_cast<Wolf*>(org)) &&
					rand() % 3 == 0) {
					org->kill();
					cout << "暴风雪冻死了" << org->getName() << endl;
				}
			}
		}
	}
	clearDeadOrg(ecosystem);
}
int main() {
	srand((unsigned)time(0));
	//time（0）是ctime里的函数，返回当前系统时间（从1970年到现在一共多少秒）
	//srand是设计随机数种子，为rand函数提供一个随机种子，保证它从不同的起点开始生成随机数
	//（unsigned）是强制类型转换，time（0）返回的是long型，srand需要unsigned型，所以要转换一下
	cout << "==========生态系统模拟系统==========\n" << endl;
	//多态实现，统一基类指针数组，存放所有生物的指针
	vector <Organism*>ecosystem;
	//vector是动态数组模板
	string areas[] = { "东区","西区","南区","北区","中央区" };
	ifstream testFile("eco_save.txt");
	bool hasSave = testFile.good();
	testFile.close();
	bool loadSuccess = false;
	if (hasSave) {
		cout << "检测到存档文件，自动加载中..." << endl;
		loadEco(ecosystem);
		loadSuccess = true;
	}
	if(!loadSuccess){//读档不成功时才重新创建对象
		int numWolves, numSheep, numGrass;
		cout << "请输入狼的数量：";cin >> numWolves;
		cout << "请输入羊的数量：";cin >> numSheep;
		cout << "请输入草的数量：";cin >> numGrass;
		cout << "\n----------生态系统初始化----------" << endl;
		for (int i = 0;i < numWolves;i++) {
			ecosystem.push_back(new Wolf(string("大灰狼") + to_string(i + 1), (rand() % 2 == 0) ? "雄性" : "雌性", rand() % 10 + 5, rand() % 100 + 1, areas[rand() % 5]));//保证开局有可以繁殖的狼，年龄范围是5-14岁，健康值范围是1-100，位置随机
			//以上句子就是在往wolves这个数组里增添一只新的大灰狼i+1，性别年龄血量与所在区域都是随机的
			//.push_back是vector的成员函数，表示在数组末尾添加一个元素
			//由于vector里的元素是狼的指针，所以数组里存的就是新狼的地址
			ecosystem.back()->showStatus();
			//.back()是vector的成员函数，表示返回数组最后一个元素的引用
		}
		for (int i = 0;i < numSheep;i++) {
			ecosystem.push_back(new Sheep(string("小羊") + to_string(i + 1), (rand() % 2 == 0) ? "雄性" : "雌性", rand() % 10 + 5, rand() % 100 + 1, areas[rand() % 5]));
			ecosystem.back()->showStatus();
		}
		for (int i = 0;i < numGrass;i++) {
			ecosystem.push_back(new Grass(string("青草") + to_string(i + 1), rand() % 10 + 1, areas[rand() % 5]));
			ecosystem.back()->showStatus();
		}
	}
	while(true){
		int runTime;
		cout << "\n请输入模拟运行的时间（单位：天）：";cin >> runTime;
		for (int t = 1;t <= runTime;t++) {
			cout << "\n----------第" << t << "天----------" << endl;
			//移动阶段
			//多态，统一调用接口，不同对象实现各自的移动方式
			for (auto org : ecosystem) {
				if (org->isAlive())
					org->move();
			}
			//捕食阶段
			//狼吃羊阶段
			for (auto w : ecosystem) { //用auto逐个取出数组里的每一个生物，w就是当前的生物，执行w->hunt
				Wolf* wolf = dynamic_cast<Wolf*>(w); //dynamic_cast是C++的运行时类型识别机制，判断当前生物是否是狼，如果是则返回该狼的指针，否则返回nullptr
				if (wolf && wolf->isAlive()) {
					if (wolf->getHealth() >= 80)//不饿不捕食
						continue;
					for (auto prey : ecosystem) {
						Sheep* sheep = dynamic_cast<Sheep*>(prey);
						//依赖倒置，Wolf：：hunt接收基类指针，可以传入任何一个子类指针
						if (sheep && sheep->isAlive()&&wolf->getPosition()==sheep->getPosition()) {
							wolf->hunt(sheep);
							if (wolf->getHealth() >= 100) {
								break; // 健康值达到上限，停止捕猎
							}
						}
					}
				}
			}
			//以上每一只活着的饥饿的狼都会尝试去捕猎每一只活着的羊
			// 羊吃草阶段
			cout << "\n----------羊吃草----------" << endl;
			for (auto s : ecosystem) {
				Sheep* sheep = dynamic_cast<Sheep*>(s);
				if (sheep && sheep->isAlive()) {
					if (sheep->getHealth() >= 80)//不饿不吃草
						continue;
					if (sheep->getHealth() <= 0) {
						sheep->kill();
					}
					for (auto g : ecosystem) {
						Grass* grass = dynamic_cast<Grass*>(g);
						if (grass && grass->isAlive() && sheep->getPosition() == grass->getPosition()) {
							grass->kill();
							sheep->setHealth(sheep->getHealth() + 40);
							cout << sheep->getName() << "在" << sheep->getPosition() << "吃掉了" << grass->getName() << endl;
							if (sheep->getHealth() > 100) {
								sheep->setHealth(100); // 健康值上限为100
							}
							break;
						}
					}
				}
			}
			//繁殖阶段
			//统一调用多态接口，只需要调用一次，万物各自繁衍
			cout << "\n----------繁殖阶段----------" << endl;
			size_t currentSize = ecosystem.size();//.size()是vector的成员函数，返回数组的大小
			for (size_t i = 0; i < currentSize; i++) {
				if (ecosystem[i]->isAlive()) {
					ecosystem[i]->reproduce(ecosystem);
				}
			}
			//以上每一只活着的生物都会尝试繁殖，繁殖函数会判断是否满足繁殖条件，如果满足就会在生态系统里增加一个新的生物
			//衰老与死亡阶段
			for (auto org : ecosystem) {//org是Organism类的指针，指向当前生物对象
				if (!org->isAlive())continue;
				org->growUp();
				if (org->getAge() > 40) {
					org->kill();
					cout << org->getName() << "因年老而死亡。" << endl;
				}
			}
			//清理死亡的生物
			cout << "\n----------清理死亡的生物----------" << endl;
			bool hasDead = false;//定义标记，记录本轮是否有死亡的生物，初始为false
			for (auto it = ecosystem.begin(); it != ecosystem.end();) {//it是迭代器，指向当前生物对象，ecosystem.begin()是vector的成员函数，返回数组的第一个元素的迭代器，ecosystem.end()是vector的成员函数，返回数组最后一个元素的下一个位置的迭代器
				if (!(*it)->isAlive()) {//*it是取出迭代器指向的元素，即Organism*
					cout << (*it)->getName() << "已死亡，清理出生态系统。" << endl;
					hasDead = true;
					delete* it; // 释放内存
					it = ecosystem.erase(it); // erase返回删除元素后下一个元素的迭代器
				}
				else {
					++it;
				}
			}
			if (!hasDead) {
				cout << "没有死亡的生物需要清理。" << endl;
			}
		}
		cout << "----------模拟结束----------" << endl;
		//最终统计
		cout << "-----------当前生态系统状态----------" << endl;
		int aliveWolves = 0, aliveSheep = 0, aliveGrass = 0;
		for (auto org : ecosystem) {
			org->showStatus();
			if (org->isAlive()) {
				if (dynamic_cast<Wolf*>(org)) aliveWolves++;
				else if (dynamic_cast<Sheep*>(org)) aliveSheep++;
				else if (dynamic_cast<Grass*>(org)) aliveGrass++;
			}
		}
		cout << "存活的狼数量：" << aliveWolves << endl;
		cout << "存活的羊数量：" << aliveSheep << endl;
		cout << "存活的草数量：" << aliveGrass << endl;
		//===== 新增交互选择，放在一轮生态更新结束之后，原有代码不动 =====
		int op;
		cout << "\n=====操作菜单=====" << endl;
		cout << "0.退出 1.继续模拟  2.存档  3.读档 4.人工环境干预" << endl;
		cin >> op;
		if (op == 2)
		{
			saveEco(ecosystem);
			cout<< "存档成功" << endl;
		}
		else if (op == 3)
		{
			loadEco(ecosystem);
		}
		else if (op == 4)
		{
			manualIntervene(ecosystem);
		}
		else if (op == 0) {
			break;
		}
	}
	//退出前自动存档
	saveEco(ecosystem);
	cout << "退出前已自动保存" << endl;
	//释放内存
	//多态体现，通过基类指针统一释放所有生物的内存，因为基类指针有虚构函数，所以不会内存泄露
	for (auto org : ecosystem)
		delete org;
	ecosystem.clear();//clear()是vector的成员函数，清空数组里的所有元素
	return 0;
}