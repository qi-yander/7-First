#include "EcoSystem.h"
#include "Wolf.h"
#include "Sheep.h"
#include "Grass.h"
#include <iostream>
#include <cstdlib>
using namespace std;

EcoSystem::EcoSystem()
{
}

EcoSystem::~EcoSystem()
{
	//析构释放全部生物内存
	for (auto org : ecosystem)
	{
		delete org;
	}
	ecosystem.clear();
}

std::vector<Organism*>& EcoSystem::getContainer()
{
	return ecosystem;
}

void EcoSystem::initEco(int numWolves, int numSheep, int numGrass)
{
	cout << "\n----------生态系统初始化----------" << endl;
	for (int i = 0; i < numWolves; i++)
	{
		ecosystem.push_back(new Wolf(string("大灰狼") + to_string(i + 1),
			(rand() % 2 == 0) ? "雄性" : "雌性",
			rand() % 10 + 5,
			rand() % 100 + 1,
			areas[rand() % 5]));
		ecosystem.back()->showStatus();
	}
	for (int i = 0; i < numSheep; i++)
	{
		ecosystem.push_back(new Sheep(string("小羊") + to_string(i + 1),
			(rand() % 2 == 0) ? "雄性" : "雌性",
			rand() % 10 + 5,
			rand() % 100 + 1,
			areas[rand() % 5]));
		ecosystem.back()->showStatus();
	}
	for (int i = 0; i < numGrass; i++)
	{
		ecosystem.push_back(new Grass(string("青草") + to_string(i + 1),
			rand() % 10 + 1,
			areas[rand() % 5]));
		ecosystem.back()->showStatus();
	}
}

void EcoSystem::clearDeadOrg()
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

void EcoSystem::manualIntervene()
{
	cout << "\n=====人工干预=====" << endl;
	cout << "1.人工捕食  2.自然灾害" << endl;
	int choice; cin >> choice;
	if (choice == 1) {
		cout << "选择区域：1.东区 2.西区 3.南区 4.北区 5.中央区" << endl;
		int a; cin >> a;
		string target = areas[a - 1];
		int killed = 0;
		for (auto org : ecosystem) {
			if (org->isAlive() && org->getPosition() == target &&
				(dynamic_cast<Sheep*>(org) || dynamic_cast<Wolf*>(org))) {
				if (rand() % 3 == 0) {
					org->kill();
					cout << "人工捕杀了" << org->getName() << "（" << target << "）" << endl;
					killed++;
				}
			}
		}
		cout << "人工捕食结束，共捕杀" << killed << "只动物" << endl;
	}
	else if (choice == 2) {
		int disaster = rand() % 3;
		if (disaster == 0) {
			cout << "=====干旱降临！=====" << endl;
			for (auto org : ecosystem) {
				Grass* g = dynamic_cast<Grass*>(org);
				if (g && g->isAlive() && rand() % 2 == 0) {
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
	clearDeadOrg();
}

void EcoSystem::saveEco(ofstream& fout)
{
	for (auto o : ecosystem)
		o->save(fout);
}

void EcoSystem::loadEco(ifstream& fin)
{
	//清空旧生态
	for (auto org : ecosystem)
	{
		delete org;
	}
	ecosystem.clear();

	string type;
	while (fin >> type)
	{
		if (type == "Grass")
		{
			Grass* g = new Grass("", 0, "");
			g->load(fin);
			ecosystem.push_back(g);
		}
		else if (type == "Sheep")
		{
			Sheep* s = new Sheep("", "", 0, 0, "");
			s->load(fin);
			ecosystem.push_back(s);
		}
		else if (type == "Wolf")
		{
			Wolf* w = new Wolf("", "", 0, 0, "");
			w->load(fin);
			ecosystem.push_back(w);
		}
	}
	cout << "读档成功！继续生态模拟" << endl;
}

void EcoSystem::runSimulation(int runDay)
{
	for (int t = 1; t <= runDay; t++)
	{
		cout << "\n----------第" << t << "天----------" << endl;
		//移动阶段
		for (auto org : ecosystem) {
			if (org->isAlive())
				org->move();
		}
		//狼捕食羊
		for (auto w : ecosystem)
		{
			Wolf* wolf = dynamic_cast<Wolf*>(w);
			if (!wolf || !wolf->isAlive()) continue;
			if (wolf->getHealth() >= 80) continue;

			for (auto prey : ecosystem)
			{
				if (!prey->isAlive()) continue;
				if (wolf->getPosition() != prey->getPosition()) continue;

				if (prey->beEaten(wolf))
				{
					wolf->setHealth(wolf->getHealth() - 3);
					if (rand() % 100 < 60)
					{
						cout << wolf->getName() << " 在 " << wolf->getPosition()
							<< " 捕猎到 " << prey->getName() << "！\n";
						prey->kill();
						wolf->setHealth(std::min(wolf->getHealth() + 60, 100));
					}
					else
					{
						cout << wolf->getName() << " 捕猎 " << prey->getName() << " 失败！\n";
					}
					if (wolf->getHealth() >= 100) break;
				}
			}
		}
		//羊吃草
		for (auto s : ecosystem)
		{
			Sheep* sheep = dynamic_cast<Sheep*>(s);
			if (!sheep || !sheep->isAlive()) continue;
			if (sheep->getHealth() >= 90) continue;

			for (auto g : ecosystem)
			{
				if (!g->isAlive()) continue;
				if (sheep->getPosition() != g->getPosition()) continue;

				if (g->beEaten(sheep))
				{
					g->kill();
					sheep->setHealth(std::min(sheep->getHealth() + 40, 100));
					cout << sheep->getName() << " 在 " << sheep->getPosition()
						<< " 吃掉了 " << g->getName() << "\n";
					break;
				}
			}
		}
		//繁殖阶段
		cout << "\n----------繁殖阶段----------" << endl;
		size_t currentSize = ecosystem.size();
		for (size_t i = 0; i < currentSize; i++)
		{
			if (ecosystem[i]->isAlive())
			{
				ecosystem[i]->reproduce(ecosystem);
			}
		}
		//衰老死亡
		for (auto org : ecosystem)
		{
			if (!org->isAlive()) continue;
			org->growUp();
			if (org->getAge() > 40)
			{
				org->kill();
				cout << org->getName() << "因年老而死亡。" << endl;
			}
		}
		//清理死亡
		clearDeadOrg();
	}
}

void EcoSystem::showStatusAndCount(int& outWolf, int& outSheep, int& outGrass)
{
	outWolf = 0;
	outSheep = 0;
	outGrass = 0;
	cout << "-----------当前生态系统状态----------" << endl;
	for (auto org : ecosystem)
	{
		org->showStatus();
		if (org->isAlive())
		{
			if (dynamic_cast<Wolf*>(org)) outWolf++;
			else if (dynamic_cast<Sheep*>(org)) outSheep++;
			else if (dynamic_cast<Grass*>(org)) outGrass++;
		}
	}
	cout << "存活的狼数量：" << outWolf << endl;
	cout << "存活的羊数量：" << outSheep << endl;
	cout << "存活的草数量：" << outGrass << endl;
}