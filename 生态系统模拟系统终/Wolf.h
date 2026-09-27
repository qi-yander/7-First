#pragma once
#include "Organism.h"
#include <string>
#include <iostream>
using namespace std;
class Wolf :public Organism {
public:
	Wolf(string n, string g, int a, int h, string pos);
	void move()override;
	void showStatus()override;
	void hunt(Organism* prey);
};
