#include <iostream>
#include "Wolf.h"
#include "Grass.h"
#include "Sheep.h"
using namespace std;
Wolf::Wolf(string n, string g, int a, int h, string pos) :Organism(n, g, a, h, pos) {}
void Wolf::move() {
    if (!isAlive())return;
    string areas[] = { "东区","西区","南区","北区","中央区" };
    position = areas[rand() % 5];
    health -= 2;//每次活动消耗2点体力
    if (health < 0)health = 0;
    cout << name << "游荡到了" << position << "消耗2点体力，当前体力：" << health << endl;
}
void Wolf::showStatus() {
    cout << "大灰狼名字：" << name << " 性别：" << gender  << " 年龄：" << age  << " 所在位置：" << position << " 健康值：" << health << endl;
    if (!isAlive())cout << "这只大灰狼饿死掉了T-T" << endl;
}
//下面就是多态，狼特有的繁殖逻辑
void Wolf::reproduce(vector<Organism*>& ecosystem) {
    static int cnt = 1;
    if (!isAlive() || age < 5 || health < 50)return;
    for (auto org : ecosystem) {
        Wolf* other = dynamic_cast<Wolf*>(org);
        if (other && other != this && other->isAlive() && canReproduce(other)&&other->getHealth()>=50) {
            cout<< name<< other->getName() << "在" << position << "繁殖了！" << endl;
            this->setHealth(this->getHealth() - 20);
            other->setHealth(other->getHealth() - 20);
            ecosystem.push_back(new Wolf("小狼宝宝" + to_string(cnt++), rand() % 2 == 0 ? "雄性" : "雌性", 0, 100, position));
            ecosystem.back()->showStatus();
            return;
        }
    }
}
bool Wolf::beEaten(Organism* attacker) {
    return false; //狼不会被吃掉
}
void Wolf::save(ofstream& out) {
    out << "Wolf "<<name << " " << gender << " " << age << " " << health << " " << position << endl;
}
void Wolf::load(ifstream& in) {
    in >> name >> gender >> age >> health >> position;
}