#include "Sheep.h"
#include <iostream>
using namespace std;
Sheep::Sheep(string n, string g, int a, int h, string pos) :Organism(n, g, a, h, pos) {}
void Sheep::move() {
	if (!isAlive())return;
	string areas[] = { "东区","西区","南区","北区","中央区" };
	position = areas[rand() % 5];
	cout << "小羊" << name << "跑到了" << position << endl;
}
void Sheep::showStatus() {
	cout << "小羊名字:" << name << '\n' << "年龄:" << age << '\n' << "所在位置:" << position << '\n' << "健康值:" << health << endl;
	if (!isAlive()) {
		cout << "小羊死掉了T-T" << endl;
	}
}