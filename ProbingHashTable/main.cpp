#include <iostream>
#include "ProbingHashTable.h"
#include <vector>

using namespace std;

void testHashTable1() {
    HashTable<string> h1;
    vector<string> tmp{"about", "anne", "an", "abort", "ago", "anno"};
    for (int i = 0; i < tmp.size(); ++i) {
        h1.insert(tmp[i]);
    }

    string q;

    cout << (h1.insert("annoy") ? "成功" : "失败") << "插入annoy" << endl;
    cout << "如果要插入，请输入要插入的词,否则按q退出" << endl;
    while (cin >> q && q != "q") {
        bool flag = h1.insert(q);
        if (flag) {
            cout << "插入" << q << "成功" << endl;
        } else {
            cout << "插入" << q << "失败" << endl;
        }
        cout << "如果要继续插入，请输入要插入的词,否则按q退出" << endl;
    }


    cout << "如果要查询，请输入查询词,否则按q退出" << endl;
    while (cin >> q && q != "q") {
        bool flag = h1.contains(q);
        if (flag) {
            cout << "h contains " << q << endl;
        } else {
            cout << "h not contains " << q << endl;
        }
        cout << "如果要继续查询，请输入查询词,否则按q退出" << endl;
    }

    cout << "如果要删除，请输入要删除的词,否则按q退出" << endl;
    while (cin >> q && q != "q") {
        bool flag = h1.remove(q);
        if (flag) {
            cout << "删除" << q << "成功" << endl;
        } else {
            cout << "删除" << q << "失败" << endl;
        }
        cout << "如果要继续查询，请输入查询词,否则按q退出" << endl;
    }

    cout << "如果要查询，请输入查询词,否则按q退出" << endl;
    while (cin >> q && q != "q") {
        bool flag = h1.contains(q);
        if (flag) {
            cout << "h contains " << q << endl;
        } else {
            cout << "h not contains " << q << endl;
        }
        cout << "如果要继续查询，请输入查询词,否则按q退出" << endl;
    }
}

int main() {
    testHashTable1();
    return 0;
}