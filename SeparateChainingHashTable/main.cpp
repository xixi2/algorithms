#include <iostream>
#include "SeparateChaining.h"

using namespace std;

void testHashTable1() {
    HashTable<int> h1;
    HashTable<int> h2;

//    const int NUMS = 400000;
    const int NUMS = 400;
    const int GAP = 37;
    cout << "Checking... (no more output means success)" << endl;
    for (int i = GAP; i != 0; i = (i + GAP) % NUMS) {
//        cout << i << " ";
        h1.insert(i);
    }
//    cout << endl;
    cout << h1 << endl;

    h2 = h1;
    for (int i = 1; i < NUMS; i += 2) {
        h2.remove(i);
    }

    for (int i = 2; i < NUMS; i += 2) {
        if (!h2.contains(i)) {
            cout << "Contains fails" << i << endl;
        }
    }

    for (int i = 1; i < NUMS; i += 2) {
        if (h2.contains(i))
            cout << "OOPS!!! " << i << endl;
    }
}

int main() {
    testHashTable1();
    return 0;
}