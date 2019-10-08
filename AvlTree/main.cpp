#include <iostream>
#include <vector>
#include "AvlTree.h"

using namespace std;

void testAvlTree1() {
    AvlTree<int> t;
    int NUMS = 20000;
    const int GAP = 37;

    cout << "Checking...(no more output means success)" << endl;

    for (int i = GAP; i != 0; i = (i + GAP) % NUMS) {
        t.insert(i);
    }
    t.remove(0);
    for (int i = 1; i < NUMS; i += 2) {
        t.remove(i);
    }
      if (NUMS < 40) {
          t.printTree();
      }
      if (t.findMin() != 2 || t.findMax() != NUMS - 2) {
          cout << "FindMin or FindMax error" << endl;
      }
      for (int i = 2; i < NUMS; i += 2) {
          if (!t.contains(i)) {
              cout << "Find error1" << endl;
          }
      }

      for (int i = 1; i < NUMS; i += 2) {
          if (t.contains(i)) {
              cout << "Find error2" << endl;
          }
      }

      AvlTree<int> t2;
      t2 = t;
      for (int i = 2; i < NUMS; i += 2) {
          if (!t.contains(i)) {
              cout << "Find error1" << endl;
          }
      }
      for (int i = 1; i < NUMS; i += 2) {
          if (t2.contains(i)) {
              cout << "Find error2" << endl;
          }
      }
      cout << "End of test" << endl;
}


void testAvlTree2() {
    AvlTree<int> t0;
    cout << "t0:" << " ";
    //左右双旋
    vector<int> tmp{2, 0, 4, 1};
    for (int i = 0; i < tmp.size(); ++i) {
        t0.insert(tmp[i]);
    }
    t0.remove(4);

    cout << "t1:" << " ";
    //右左双旋
    tmp = {2, 0, 4, 3};
    AvlTree<int> t1;
    for (int i = 0; i < tmp.size(); ++i) {
        t1.insert(tmp[i]);
    }
    t1.remove(0);

    cout << "t2:" << " ";
    // 左单旋
    tmp = {5, 4, 3};
    AvlTree<int> t2;
    for (int i = 0; i < tmp.size(); ++i) {
        t2.insert(tmp[i]);
    }

    cout << "t3:" << " ";
    // 右单旋
    tmp = {1, 4, 6};
    AvlTree<int> t3;
    for (int i = 0; i < tmp.size(); ++i) {
        t3.insert(tmp[i]);
    }


    cout << "================t==============" << endl;
    AvlTree<int> t(t0);
    tmp = {5, 6, 1, 2, 3, 0, 4, 8, 7, 9};
    t.makeEmpty();
    for (int i = 0; i < tmp.size(); ++i) {
        t.insert(tmp[i]);
    }
    cout << (t.contains(11) ? "contains 1" : "not contains 1") << endl;
    cout << "t.findmin():" << t.findMin() << endl;
    cout << "t.findMax():" << t.findMax() << endl;
}

int main() {
    testAvlTree1();
//    testAvlTree2();
    return 0;
}