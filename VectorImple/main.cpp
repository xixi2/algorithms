#include <iostream>
#include <time.h>
#include "Vector.h"

using namespace std;

int main() {
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

    v3 = v2;        //拷贝赋值运算符函数
    cout << "令v3=v2后的v3: " << v3 << endl;


    v1 = std::move(v2);   //移动赋值运算符函数
    cout << "令v1=v2后的v1: " << v1 << endl;

    Vector<int> v4;
//    v4 = std::move(v2);   //移动赋值运算符函数
    cout << "令v4=v2后的v4: " << v4 << endl;


    // ==================================
    Vector<string> sv1;  // 默认初始化为空Vector
    sv1.push_back("an");
    sv1.push_back("about");
    sv1.push_back("anne");
    sv1.push_back("anna");
    cout << "sv1:" << sv1 << endl;

//    Vector<string> sv2 = std::move(sv1); // 调用移动构造函数, 移后源对象不能再使用
//    cout << "sv2:" << sv2 << endl;

    //=============================================
    auto begin = sv1.begin();
    cout << *begin << endl;
    auto end = sv1.end();
    cout << *end << endl;
    return 0;
}