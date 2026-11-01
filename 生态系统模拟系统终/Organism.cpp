#include "Organism.h"
Organism::Organism(string n, string g, int a, int h, string pos) {//定义Organism类的构造函数，参数分别是名字、性别、年龄、健康值和位置
	name = n;
	gender = g;
	age = a;
	health = h;
	position = pos;
}