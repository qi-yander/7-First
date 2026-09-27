#pragma once
#include <string>
#include <iostream>
using namespace std;
class Organism {
protected:
    string name;
    string gender;
    int age;
    int health;
    string position;
public:
    Organism(string n, string g, int a, int h, string pos);
    virtual ~Organism() {}
    bool isAlive() {
        return health > 0;
    }
    void kill() {
        health = 0;
    }
    int gethealth() {
        return health;
    }
    void setHealth(int h) {
        health = h;
    }
    string getPosition() {
        return position;
    }
    void setPosition(string pos) {
        position = pos;
    }
    string getName() {
        return name;
    }
    virtual void move() = 0;
    virtual void showStatus() = 0;
    //virtual是个纯虚函数 上面这句话要求子类必须自己写这俩函数的代码
    bool canReproduce(Organism* other) {
        if (!isAlive() || other->isAlive()) {
            return false;
        }
        if (position != other->getPosition())return false;
        if (age < 2 || other->age < 2)return false;
        if (gender == other->gender)return false;
        return true;
    }
};
