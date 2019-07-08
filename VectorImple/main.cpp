#include <iostream>
#include "Vector.h"

using namespace std;

void testVector1() {
    Vector<int> v1;
    unsigned seed = time(0);
    srand(seed);
    for (int i = 0; i < 5; ++i) {
        int num = rand() % 100;
        v1.push_back(num);
    }
    cout << "v1: " << v1 << endl;

//=========================拷贝=================================
    Vector<int> v2 = v1;        //拷贝构造函数
    cout << "用v1初始化v2后的v2: " << v2 << endl;

    for (int i = 0; i < 5; ++i) {
        v2.pop_back();
    }
    for (int i = 0; i < 5; ++i) {
        int num = rand() % 100;
        v2.push_back(num);
    }
    cout << "重新修改v2的元素后的v2: " << v2 << endl;

    Vector<int> v3(v1);
    cout << "用v1初始化v3后的v3: " << v3 << endl;

    cout << "===========================" << endl;

    v3 = v2;        //拷贝赋值运算符函数
    cout << "令v3=v2后的v3: " << v3 << endl;
    cout << "令v3=v2后的v2: " << v2 << endl;

    v3 = v3;        //拷贝赋值运算符函数
    cout << "令v3=v3后的v3: " << v3 << endl;

    // 利用v3来初始化v4,此后v3属于移后源对象,可以重新赋值,但不能使用v3的值
    Vector<int> v4(std::move(v3));
//    cout << "令v4=v3后的v3: " << v3 << endl;
    cout << "令v4=v3后的v4: " << v4 << endl;

    cout << "v4[2]:" << v4[2] << endl;
    auto it = v4.begin();
    *it = 1022;
    cout << "改变首元素后的v4: " << v4 << endl;

    int back_value = v4.back();
    cout << "v4中最后一个元素：" << back_value << endl;
}

void testVector2() {
    Vector<string> v1(5, "hello");
    cout << "v1: " << v1 << endl;
    v1[2] = "nana";
    cout << "v1: " << v1 << endl;
//    v1[v1.size()] = "day";      // out_of_range

    // 目前无法禁止负数索引
    v1[-1] = "day";
    cout << "v1: " << v1 << endl;

    //=================常量对象====================
    const Vector<string> v2(4, "good");
    cout << "v2: " << v2 << endl;

}

int main() {
//    testVector1();
    testVector2();
    return 0;
}