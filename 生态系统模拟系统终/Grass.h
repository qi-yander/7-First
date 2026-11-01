#pragma once
#include "Organism.h"
#include <vector>//引入C++动态数组容器vector的头文件
class Grass : public Organism {
public:
	Grass(string n, int a, string pos);
	void move() override;//override是重写的意思，告诉编译器这个函数专门覆盖基类的虚函数，多态实现
	void showStatus() override;
	//声明草的繁殖函数reproduce，传入一个Organism类的指针数组ecosystem，里面存放了所有生物的指针，方便草繁殖时把新草加入到生态系统中
	void reproduce(vector<Organism*>& ecosystem)override;//传入一个Organism类的指针数组ecosystem，里面存放了所有生物的指针，方便草繁殖时把新草加入到生态系统中
	//&是引用，直接操作原来的数组，新增小草加到整个生态系统里
	void save(ofstream& out) override;//ofstream是输出文件流，写文件（保存数据）
	void load(ifstream& in) override;//ifstream是输入文件流，读文件（加载数据）
	//&是引用，直接操作原来的文件流，方便保存和加载数据，out是输出，in是输入
};
//继承继承的是成员变量与成员函数，构造函数和析构函数不继承
//析构函数不是为了继承给子类，是专门给基类指针使用的，子类对象被销毁时会先调用子类的析构函数，再调用基类的析构函数
//如果不写虚析构函数，子类对象被销毁时只会调用基类的析构函数来析构基类，而不会调用子类的析构函数来析构子类