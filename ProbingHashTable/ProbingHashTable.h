//
// Created by xixi2 on 19-7-8.
//

#ifndef PROBINGHASHTABLE_PROBINGHASHTABLE_H
#define PROBINGHASHTABLE_PROBINGHASHTABLE_H

#include <utility>
#include <vector>
#include <sys/ucontext.h>

int nextPrime(int n);

/**
 * 使用平方探测方法的散列表
 * 一次聚集,在线性探测中散列到表中的元素在该三列位置被占据时,相继探测逐个单元以查出一个空单元
 * 这样占据的位置逐渐开始形成一些连续的区块；最后导致散列到区块中的任何关键字都需要多次试选单元才能够解决冲突
 * 平方探测解决了一次聚集问题,但是散列到同一个位置上的那些元素将探测相同的备选单元，这叫做二次聚集
 * @tparam HashedObj
 */
template<typename HashedObj>
class HashTable {
public:
    explicit HashTable(int size = 101);

    bool contains(const HashedObj &x) const;

    void makeEmpty();

    bool insert(const HashedObj &x);

    bool insert(HashedObj &&x);

    bool remove(const HashedObj &x);

    enum EntryType {
        ACTIVE, EMPTY, DELETED
    };
private:
    struct HashEntry {
        HashedObj element;
        EntryType info;

        HashEntry(const HashedObj &e = HashedObj{}, EntryType i = EMPTY) : element(e), info(i) {}

        HashEntry(HashedObj &&e, EntryType i = EMPTY) : element(std::move(e)), info(i) {}
    };

    std::vector<HashEntry> array;
    int currentSize;

    bool isActive(int currentPos) const;

    int findPos(const HashedObj &x) const;

    void rehash();

    size_t myhash(const HashedObj &x) const;
};

template<typename HashedObj>
HashTable<HashedObj>::HashTable(int size): array(nextPrime(size)) {
    makeEmpty();
}

template<typename HashedObj>
void HashTable<HashedObj>::makeEmpty() {
    currentSize = 0;
    for (auto &entry : array) {
        entry.info = EMPTY;
    }
}

template<typename HashObj>
bool HashTable<HashObj>::contains(const HashObj &x) const {
    return isActive(findPos(x));
}

template<typename HashObj>
int HashTable<HashObj>::findPos(const HashObj &x) const {
    int offset = 1;
    int currentPos = myhash(x);

    // 测试顺序很重要,不能交换顺序
    while (array[currentPos].info != EMPTY && array[currentPos].element != x) {
        currentPos += offset;   // 计算第i次探测
        offset += 2;
        if (currentPos >= array.size()) {
            currentPos -= array.size();
        }
    }

    // 下面的想法需要验证
    // 如果x已经存在,且当前还是有效的,则返回x的位置;如果x不存在,则返回的是一个状态为empty的位置
    return currentPos;
}

template<typename HashObj>
bool HashTable<HashObj>::isActive(int currentPos) const {
    return array[currentPos].info == ACTIVE;
}

/**
 * 这里的探测方法避免了乘法和除法,较快
 * @tparam HashObj
 * @param x
 * @return
 */
template<typename HashObj>
bool HashTable<HashObj>::insert(const HashObj &x) {
    int currentPos = findPos(x);
    if (isActive(currentPos)) {
        return false;
    }
    array[currentPos].element = x;
    array[currentPos].info = ACTIVE;

    // 如果装填银子超过0.5,则表是满的,需要将散列表放大,即再散列
    if (++currentSize > array.size() / 2) {
        rehash();
    }

    return true;
}

template<typename HashObj>
bool HashTable<HashObj>::insert(HashObj &&x) {
    int currentPos = findPos(x);
    if (isActive(currentPos)) {
        return false;
    }
    array[currentPos].element = std::move(x);
    array[currentPos].info = ACTIVE;

    // 再散列
    if (++currentSize > array.size() / 2) {
        rehash();
    }
    return true;
}


template<typename HashObj>
bool HashTable<HashObj>::remove(const HashObj &x) {
    int currentPos = findPos(x);

    //
    if (!isActive(currentPos)) {
        return false;
    }
    array[currentPos].info = DELETED;
    return true;
}

/**
 * 平方探测法的再散列
 * @tparam HashObj
 */
template<typename HashObj>
void HashTable<HashObj>::rehash() {
    std::vector<HashEntry> oldArray = array;

    //创建新的两倍大小的空表
    array.resize(nextPrime(2 * oldArray.size()));
    for (auto &entry : array) {
        entry.info = EMPTY;
    }

    // 复制整个表
    currentSize = 0;
    for (auto &entry : oldArray) {
        if (entry.info = ACTIVE) {
            insert(std::move(entry.element));
        }
    }
}

template<typename HashObj>
size_t HashTable<HashObj>::myhash(const HashObj &x) const {
    static std::hash<HashObj> hf;
    return hf(x) % array.size();
}

#endif //PROBINGHASHTABLE_PROBINGHASHTABLE_H
