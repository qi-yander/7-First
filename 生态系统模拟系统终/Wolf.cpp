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
    cout << "大灰狼名字：" << name << '\n' << "性别：" << gender << '\n' << "年龄：" << age << '\n' << "所在位置：" << position << '\n' << "健康值：" << health << endl;
    if (!isAlive())cout << "这只大灰狼饿死掉了T-T" << endl;
}
//下面就是多态，狼特有的繁殖逻辑
void Wolf::reproduce(vector<Organism*>& ecosystem) {
    if (!isAlive() || age < 5 || health < 50)return;
    for (auto org : ecosystem) {
        Wolf* other = dynamic_cast<Wolf*>(org);
        if (other && other != this && other->isAlive() && canReproduce(other)) {
            cout<< name<< other->getName() << "在" << position << "繁殖了！" << endl;
            setHealth(getHealth() - 20);
            other->setHealth(other->getHealth() - 20);
            ecosystem.push_back(new Wolf("小狼宝宝", rand() % 2 == 0 ? "雄性" : "雌性", 0, 100, position));
            ecosystem.back()->showStatus();
            return;
        }
    }
}
void Wolf::hunt(Organism* prey) {//依赖倒置原则体现在这里，基类指针可以指向不同的子类对象，体现了对抽象接口的依赖
    if (!isAlive() || prey == nullptr || !prey->isAlive() || position != prey->getPosition()||health>=80)return;//不饿不吃
    if (dynamic_cast<Grass*>(prey) != nullptr||dynamic_cast<Wolf*>(prey) != nullptr)return; // 狼不吃草，dynamic_cast用于安全地将基类指针转换为子类指针<Grass*>,如果prey不是Grass类型，则返回nullptr
   //dynamic_cast是C++关键字，用于在继承体系中进行安全的类型转换。它可以将基类指针或引用转换为派生类指针或引用，如果转换不合法，则返回nullptr（对于指针）或抛出异常（对于引用）
   //要用dynamic_cast，必须保证基类有虚函数virtual
    if (rand() % 100 >= 60) {
        setHealth(health - 3);//每次捕猎消耗3点体力
        cout<< name << "在" << position << "捕猎" << prey->getName() << "失败了！" << endl;
        return;
    }
        setHealth(health - 3);//每次捕猎消耗3点体力
        cout<< name << "在" << position << "捕猎到了" << prey->getName() << "！" << endl;
        prey->kill();
        health += 60;
        if (health > 100)health = 100;
        cout << name << "吃掉了" << prey->getName() << "恢复了60点体力，当前体力：" << health << endl;
    }
void Wolf::save(ofstream& out) {
    out << "Wolf "<<name << " " << gender << " " << age << " " << health << " " << position << endl;
}
void Wolf::load(ifstream& in) {
    in >> name >> gender >> age >> health >> position;
}