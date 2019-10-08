#include <iostream>
#include "List.h"
#include <vector>

using namespace std;

/**
 * 随机产生0-n范围内的整数
 * @param n
 * @return
 */
inline int getRandomNum(int n = 100) {
    unsigned seed = time(0);
    srand(seed);
    return rand() % n;
}

void testList1() {
    List<int> l1;
    vector<int> tmp{12, 45, 6, 27, 34};
    for (int i = 0; i < tmp.size(); ++i) {
        l1.push_back(tmp[i]);   //使用左值版本push_back来添加元素
    }
    cout << "l1: " << l1 << endl;

    unsigned seed = time(0);
    srand(seed);
    List<int> l2;
    for (int i = 0; i < 4; ++i) {
        int num = rand() % 200;
        l2.push_front(std::move(num));  //使用右值版本的push_front添加元素
    }
    cout << "l2: " << l2 << endl;

    //======================使用拷贝和移动===========================
    List<int> l3 = l1;
    cout << "l1: " << l1 << endl;
    cout << "l3: " << l3 << endl;

    List<int> l4(std::move(l2));
//    cout << "l2: " << l2 << endl;     // 移动后l2的状态是否正确?
    cout << "l4: " << l4 << endl;
}

int main() {
    testList1();
    return 0;
}