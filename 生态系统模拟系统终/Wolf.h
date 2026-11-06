#pragma once
#include "Organism.h"
class Wolf :public Organism {
public:
	Wolf(string n, string g, int a, int h, string pos);
	void move()override;
	void showStatus()override;
	void reproduce(vector<Organism*>& ecosystem)override;
	void save(ofstream& out) override;
	void load(ifstream& in) override;
	bool beEaten(Organism* attacker) override;
};
