#pragma once
#include "Organism.h"
#include <string>
class Sheep :public Organism {
public:
	Sheep(string n, string g, int a, int h, string pos);
	void move()override;
	void showStatus()override;
	void reproduce(vector<Organism*>& ecosystem)override;
	void save(ofstream& out) override;
	void load(ifstream& in) override;
	bool beEaten(Organism* attacker) override;
	//这个override就是在告诉编译器子类自己写函数
};