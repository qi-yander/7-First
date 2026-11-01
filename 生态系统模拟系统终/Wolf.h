#pragma once
#include "Organism.h"
class Wolf :public Organism {
public:
	Wolf(string n, string g, int a, int h, string pos);
	void move()override;
	void showStatus()override;
	void reproduce(vector<Organism*>& ecosystem)override;
	void hunt(Organism* prey);//捕食方法传入一个基类指针，指向被捕食的对象，方便扩展（狼可以吃的对象不止羊，也可以是其他动物）
	//依赖倒置原则体现在这里，基类指针可以指向不同的子类对象
	//Wolf类只依赖于抽象Organism类，而不依赖于具体类
	void save(ofstream& out) override;
	void load(ifstream& in) override;
};
