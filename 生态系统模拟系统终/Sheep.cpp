#include "Sheep.h"
Sheep::Sheep(string n, string g, int a, int h, string pos) :Organism(n, g, a, h, pos) {}//调用父类的构造函数初始化成员变量
void Sheep::move() {
	if (!isAlive())return;
	string areas[] = { "东区","西区","南区","北区","中央区" };
	position = areas[rand() % 5];//rand（）是C标准库里的随机数函数，返回一个0到RAND_MAX之间的随机整数，%5是取余数，保证返回值在0到4之间
	health -= 2;//每次活动消耗2点体力
	cout << name << "跑到了" << position << "消耗2点体力，当前体力：" << health << endl;
}
void Sheep::showStatus() {
	cout << "小羊名字:" << name << " 性别：" << gender << " 年龄:" << age << '\n' << " 所在位置:" << position << '\n' << " 健康值:" << health << endl;
	if (!isAlive()) {
		cout << "这只小羊死掉了T-T" << endl;
	}
}
//下面就是多态，羊特有的繁殖逻辑
	void Sheep::reproduce(vector<Organism*>&ecosystem) {
		if (!isAlive()||age<5||health<40)return;
		for (auto org : ecosystem) {
			Sheep* other = dynamic_cast<Sheep*>(org); //dynamic_cast是C++的运行时类型识别机制，可以判断一个基类指针是否指向某个子类对象，如果是则返回该子类指针，否则返回nullptr
				if (other && other != this && other->isAlive() && canReproduce(other)&&other->getHealth()>=50) {//this是当前对象的指针，other!=this是为了避免自己和自己繁殖
					cout << name << "和" << other->getName() << "在" << position << "繁殖了！" << endl;
					this->setHealth(health - 10);//繁殖后健康值下降10
					other->setHealth(other->getHealth() - 10);
					ecosystem.push_back(new Sheep("小羊宝宝", rand() % 2 == 0 ? "公" : "母", 0, 100, position));//新生小羊健康值为100，年龄为0，性别随机
					ecosystem.back()->showStatus();//显示新生小羊的状态
					return;
			}
		}
	}
	void Sheep::save(ofstream& out) {
		out <<"Sheep "<< name << " " << gender << " " << age << " " << health << " " << position << endl;
	}
	void Sheep::load(ifstream& in) {
		in >> name >> gender >> age >> health >> position;
	}