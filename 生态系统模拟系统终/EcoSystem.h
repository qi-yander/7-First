#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Organism.h"

class EcoSystem
{
private:
	std::vector<Organism*> ecosystem;  // 把原来main的全局/局部容器，放进类私有成员
	std::string areas[5] = { "东区","西区","南区","北区","中央区" };

public:
	// 构造、析构
	EcoSystem();
	~EcoSystem();

	// 初始化生态：创建狼、羊、草
	void initEco(int numWolves, int numSheep, int numGrass);

	// 运行模拟 runDay天
	void runSimulation(int runDay);

	// 清理死亡生物
	void clearDeadOrg();

	// 存档读档
	void saveEco(std::ofstream& fout);
	void loadEco(std::ifstream& fin);

	// 人工干预
	void manualIntervene();

	// 打印状态 + 统计存活数量
	void showStatusAndCount(int& outWolf, int& outSheep, int& outGrass);

	// 获取容器引用（给外部极少场景使用）
	std::vector<Organism*>& getContainer();
};
