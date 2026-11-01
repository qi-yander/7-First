#include "Grass.h"
#include <cstdlib>
static int newGrassID = 1; // 静态变量，用于生成新草的唯一ID
Grass ::Grass(string n,int a,string pos):Organism(n,"无",a,100,pos) {}
//Grass这个类里的构造函数Grass（构造函数名字必须和类名一样，草没有性别固定写"无"）
void Grass::move(){}//草不会移动，所以move函数为空
void Grass::showStatus() {
	cout << "草名字：" << name <<"年龄：" << age << " 所在位置：" << position << " 状态：" << (isAlive() ? "存活" : "死亡") << endl;
}
//下面就是多态，草特有的繁殖逻辑
void Grass::reproduce(vector<Organism*>& ecosystem) {
	if (!isAlive() || age < 2)return;
	if (rand() % 100 >= 50)return;//有50%的几率发芽
	string babayname = "新草" + to_string(newGrassID++);
	cout << "草" << name << "在" << position << "生根发芽长出了" << babayname << "！" << endl;
	ecosystem.push_back(new Grass(babayname, 1, position));
	//在生态系统中加入新草对象，年龄为1岁，位置与母草相同
	ecosystem.back()->showStatus();
	//ecosystem是Organism类的指针vector数组，里面存放了所有生物的指针,.pushback()是vector数组的成员函数，向数组末尾添加一个元素
	//new Grass（）是先在堆上创建一个Grass对象，然后返回这个对象的地址，push_back()把这个地址加入到ecosystem数组中
}
void Grass::save(ofstream& out) {//将这株草的数据写入文件中，save就是保存函数
	out << "Grass "<<name << " " << age << " " << position<<" "<<health << endl;
}
void Grass::load(ifstream& in) {//load是读取函数，从文件读数据
	in >> name >>age>> position>>health;
	gender = "无";
}