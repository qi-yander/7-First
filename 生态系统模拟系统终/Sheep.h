#pragma once
#include "Organism.h"
#include <string>
#include <iostream>
using namespace std;
class Sheep :public Organism {
public:
	Sheep(string n, string g, int a, int h, string pos);
	void move()override;
	void showStatus()override;
	//这个override就是在告诉编译器子类自己写这俩函数
};