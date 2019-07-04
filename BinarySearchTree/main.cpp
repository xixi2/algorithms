#include <iostream>
#include "BinarySearchTree.h"
#include <vector>

using namespace std;

void testBinarySearchTree1() {
    BinarySearchTree<int> t;
    int NUMS = 400000;
    const int GAP = 3711;
    int i;
    cout << "Checking...(no more output means success)" << endl;
    for (int i = GAP; i > 0; i = (i + GAP) % NUMS) {
        t.insert(i);
    }

    for (int i = 1; i < NUMS; i += 2) {
        t.remove(i);
    }
    if (NUMS < 40) {
        t.printTree();
    }
    if (t.findMin() != 2 || t.findMax() != NUMS - 2) {
        cout << "FindMin or FindMax error!" << endl;
    }

    for (int i = 2; i < NUMS; i += 2) {
        if (!t.contains(i)) {
            cout << "Find error2!" << endl;
        }
    }

    BinarySearchTree<int> t2;
    t2 = t;
    for (int i = 2; i < NUMS; i += 2) {
        if (!t2.contains(i)) {
            cout << "Find error1" << endl;
        }
    }

    for (int i = 1; i < NUMS; i += 2) {
        if (t2.contains(i)) {
            cout << "Find error2!" << endl;
        }
    }
    cout << "Finished testing" << endl;
}

void testBinarySearchTree2() {
    BinarySearchTree<int> t;
    vector<int> tmp{7, 4, 5, 2, 9, 11};
    for (int i = 0; i < tmp.size(); ++i) {
        t.insert(tmp[i]);
    }
    cout << t.findMax() << endl;
    cout << t.findMin() << endl;
    t.insert(10);
    cout << t.contains(1) << endl;
    t.remove(11);
    cout << t.findMax() << endl;
}


int main() {
//    testBinarySearchTree1();
    testBinarySearchTree2();
    return 0;
}