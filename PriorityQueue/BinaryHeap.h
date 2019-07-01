//
// Created by xixi2 on 19-7-1.
//

#ifndef PRIORITYQUEUE_BINARYHEAP_H
#define PRIORITYQUEUE_BINARYHEAP_H

#include <vector>
#include "dsexceptions.h"

/**
 * 优化队列:元素越小优先级越高
 * @tparam Comparable
 */
template<typename Comparable>
class BinayHeap {
public:
    explicit BinayHeap(int capacity = 100) : array(capacity + 1), currentSize(0) {}

    explicit BinayHeap(const std::vector<Comparable> &items);

    bool isEmpty() const { return currentSize == 0; }

    const Comparable &findMin() const;

    void insert(const Comparable &x);

    void insert(Comparable &&x);

    //删除最小元素
    void deleteMin();

    void deleteMin(Comparable &minItem);

    void makeEmpty() {
        currentSize = 0;
        array.clear();
    }

private:
    int currentSize;        // 堆中元素的个数
    std::vector<Comparable> array;      //堆的数组

    void buildHeap();

    void percolateDown(int hole);   // 下滤: 将堆顶元素删除, 用左右子树上的元素来代替堆顶元素
};


template<typename Comparable>
BinayHeap<Comparable>::BinayHeap(const std::vector<Comparable> &items)
        :array(items.size() + 10), currentSize(items.size()) {
    for (int i = 0; i < items.size(); i++) {
        array[i + 1] = items[i];      // 堆中元素索引从1开始
    }
    buildHeap();
}

/***
 * 在堆中进行过滤的内部方法
 * 空穴是下滤开始的下标
 * @tparam Comparable
 */
template<typename Comparable>
void BinayHeap<Comparable>::buildHeap() {
    for (int i = currentSize / 2; i > 0; --i) {
        percolateDown(i);
    }
}

template<typename Comparable>
void BinayHeap<Comparable>::percolateDown(int hole) {
    int child;
    Comparable tmp = std::move(array[hole]);

    for (; hole * 2 <= currentSize; hole = child) {
        child = 2 * hole;
        if (child + 1 < currentSize && array[child + 1] < array[child]) {
            child = child + 1;
        }
        if (array[child] < tmp) {
            array[hole] = std::move(array[child]);
        } else {
            break;
        }
    }
    array[hole] = std::move(tmp);
}

template<typename Comparable>
const Comparable &BinayHeap<Comparable>::findMin() const {
    if (isEmpty()) {
        throw UnderflowException{};
    }
    return array[1];
}

/**
 * 将项x插入,允许重复元
 * @tparam Comparable
 * @param x
 */
template<typename Comparable>
void BinayHeap<Comparable>::insert(const Comparable &x) {
    if (currentSize == array.size() - 1) {
        array.resize(array.size() * 2);
    }

    int hole = ++currentSize;

    // 上滤
//    array[0] = std::move(x);        // 不能直接移动x,因为x是不可变的
    Comparable tmp = x;             // 复制一份x
    array[0] = std::move(x);
    for (; array[hole / 2] > x; hole /= 2) {
        array[hole] = std::move(array[hole / 2]);
    }
    array[hole] = std::move(array[0]);
}

template<typename Comparable>
void BinayHeap<Comparable>::insert(Comparable &&x) {
    if (currentSize == array.size() - 1) {
        array.resize(array.size() * 2);
    }
    int hole = ++currentSize;
    for (; hole > 1 && array[hole / 2] > x; hole /= 2) {
        array[hole] = std::move(array[hole / 2]);
    }
    array[hole] = std::move(x);
}


template<typename Comparable>
void BinayHeap<Comparable>::deleteMin() {
    if (isEmpty()) {
        throw UnderflowException{};
    }
    array[1] = std::move(array[currentSize--]);
    percolateDown(1);
}


/**
 * 删除最小项并将其放在minItem处
 * 若为空,则抛出UnderflowException异常
 * @tparam Comparable
 * @param minItem
 */
template<typename Comparable>
void BinayHeap<Comparable>::deleteMin(Comparable &minItem) {
    if (isEmpty()) {
        throw UnderflowException{};
    }
    minItem = std::move(array[1]);
    array[1] = std::move(array[currentSize--]);
    percolateDown(1);
}

#endif //PRIORITYQUEUE_BINARYHEAP_H
