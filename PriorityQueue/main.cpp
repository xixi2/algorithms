#include <iostream>
#include <vector>
#include "BinaryHeap.h"

using namespace std;


int main() {
    vector<int> nums{12, 15, 7, 9, 11, 5, 6, 10, 11};
    BinayHeap<int> q(nums);
    cout << "最小值: " << q.findMin() << endl; //5
    q.deleteMin();  // 删除5
    q.deleteMin();  // 删除6
    cout << "最小值: " << q.findMin() << endl; // 7
    q.insert(4);            // 移动版本的insert
    cout << "最小值: " << q.findMin() << endl; // 4
    q.deleteMin();  // 删除4
    q.deleteMin();  // 删除7
    int a = 8;
    q.insert(a);    // 拷贝版本的insert
    cout << "最小值: " << q.findMin() << endl; // 8
    return 0;
}