#include <iostream>
#include "Wolf.h"
using namespace std;
Wolf::Wolf(string n, string g, int a, int h, string pos) :Organism(n, g, a, h, pos) {}
void Wolf::move() {
    if (!isAlive())return;
    string areas[] = { "东区","西区","南区","北区","中央区" };
    position = areas[rand() % 5];
    health -= 2;//每次活动消耗两点体力
    if (health < 0)health = 0;
    cout << "大灰狼" << name << "游荡到了" << position << "消耗2点体力，当前体力：" << health << endl;
}
void Wolf::showStatus() {
    cout << "大灰狼名字：" << name << '\n' << "性别：" << gender << '\n' << "年龄：" << age << '\n' << "所在位置：" << position << '\n' << "健康值：" << health << endl;
    if (!isAlive())cout << "大灰狼死掉了T-T" << endl;
}
void Wolf::hunt(Organism* prey) {
    if (!isAlive() || prey == nullptr || !prey->isAlive() || position != prey->getPosition() || health < prey->gethealth())return;
    if (position == prey->getPosition()) {
        cout << "大灰狼" << name << "在" << position << "捕猎到了" << prey->getName() << "！" << endl;
        prey->kill();
        health += 20;
        if (health > 100)health = 100;
        cout << "大灰狼" << name << "吃掉了" << prey->getName() << "恢复了20点体力，当前体力：" << health << endl;
    }
}