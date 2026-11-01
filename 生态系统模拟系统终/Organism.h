//多态是发出同样的消息被不同的对象接收后产生不同的行为的能力
//C++多态三种形式：函数重载、运算符重载、虚函数（重点）
//依赖倒置原则：高层代码不应该直接写死子类（具体实现）（高层模块与低层模块应该依赖于抽象）
//基类指针：同一个基类指针可以指向该基类的不同的子类对象，可以减少分别写不同子类的同一行为的代码量，也可以把不同的子类放在一个数组里，方便管理
#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
class Organism {//多态基石，抽象基类，统一所有生物接口
protected:
    string name;
    string gender;
    int age;
    int health;
    string position;
public:
    Organism(string n, string g, int a, int h, string pos);
    virtual ~Organism() {}
    //虚析构函数，配合new和delete使用，防止内存泄漏(多态)
    //基类只定义接口，具体实现由子类完成
    //下面的是公共成员函数，子类可以直接使用
    bool isAlive()const {
        return health > 0;
    }
    //const成员函数，保证不会修改对象的成员变量
    void kill() {
        health = 0;
    }
    int getHealth()const {
        return health;
    }
    void setHealth(int h) {
        health = h;
    }
    string getPosition() const {
        return position;
    }
    void setPosition(string pos) {
        position = pos;
    }
    string getName()const {
        return name;
    }
    int getAge() const {
        return age;
    }
    void growUp(){
        age++;
    }
    //截至
    virtual void move() = 0;
    virtual void showStatus() = 0;
    virtual void reproduce(vector<Organism*>& ecosystem) = 0;//等于0表示纯虚函数
    virtual void save(ofstream& out) = 0;
    virtual void load(ifstream& in) = 0;
    //virtual是个纯虚函数 上面这五句话要求子类必须自己写这函数的代码，实现多态基础（多态，基类只定义接口）
    //以下是动物有性繁殖的条件
    bool canReproduce(Organism* other) {//other是基类指针，可以指向草，羊，狼等不同的子类对象，节省了分别写不同子类的同一行为的代码量，也可以把不同的子类放在一个数组里，方便管理
        if (!isAlive() || !other->isAlive()) {
            return false;
        }
        if (position != other->getPosition())return false;
        if (age < 5|| other->age <5)return false;//年龄小于5不能繁殖
        if (gender == other->gender)return false;//同性不能繁殖
        return true;
    }
};
