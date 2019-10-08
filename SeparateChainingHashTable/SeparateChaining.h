//
// Created by xixi2 on 19-7-5.
//

#ifndef SEPARATECHAININGHASHTABLE_SEPARATECHAINING_H
#define SEPARATECHAININGHASHTABLE_SEPARATECHAINING_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
#include <iostream>

int nextPrime(int n);

template<typename HashedObj>
class HashTable;

template<typename HashedObj>
std::ostream &operator<<(std::ostream &out, HashTable<HashedObj> &rhs);


template<typename HashedObj>
class HashTable {
    friend std::ostream &operator<<<HashedObj>(std::ostream &out, HashTable<HashedObj> &rhs);

public:
    explicit HashTable(int size = 101) : currentSize{0} {
        theLists.resize(101);
    }

    bool contains(const HashedObj &x) const {
        auto &whichList = theLists[myhash(x)];
        return find(begin(whichList), end(whichList), x) != end(whichList);
    }

    void makeEmpty() {
        for (auto &thisList: theLists) {
            thisList.clear();
        }
    }

    bool insert(const HashedObj &x) {
        auto &whichList = theLists[myhash(x)];
        if (find(begin(whichList), end(whichList), x) != end(whichList)) {
            return false;
        }
        whichList.push_back(x);

        // ++currentSize是什么意思
        if (++currentSize > theLists.size()) {
            rehash();
        }
        return true;
    }

    bool insert(HashedObj &&x) {
        auto &whichList = theLists[myhash(x)];
        if (find(begin(whichList), end(whichList), x) != end(whichList)) {
            return false;
        }
        whichList.push_back(std::move(x));

        if (++currentSize > theLists.size()) {
            rehash();
        }
        return true;
    }

    bool remove(const HashedObj &x) {
        auto &whichList = theLists[myhash(x)];
        auto itr = find(begin(whichList), end(whichList), x);
        if (itr == end(whichList)) {
            return false;
        }
        whichList.erase(itr);
        --currentSize;
        return true;
    }

private:
    std::vector<std::list<HashedObj>> theLists;       // 链表数组
    int currentSize;

    void rehash() {
        std::vector<std::list<HashedObj>> oldLists = theLists;
        theLists.resize(nextPrime(2 * theLists.size()));
        for (auto &theList : theLists) {
            theList.clear();
        }

        currentSize = 0;
        for (auto &thisList : oldLists) {
            for (auto &x : thisList) {
                insert(std::move(x));
            }
        }
    }

    size_t myhash(const HashedObj &x) const {
        /* 局部静态对象,在程序的执行路径第一次经过对象定义语句时初始化，
         * 直到程序终止时才被销毁；在此期间，即使函数所在的函数结束执行也不会对它有什么影响
         * 了解std::hash
        */
        static std::hash<HashedObj> hf;
        return hf(x) % theLists.size();
    }
};

template<typename HashedObj>
std::ostream &operator<<(std::ostream &out, HashTable<HashedObj> &rhs) {
    //为什么会出错？
    for (int i = 0; i < rhs.theLists.size(); ++i) {
        std::list<HashedObj> thisList = rhs.theLists[i];
        out << "size:" << thisList.size() << std::endl;
        if (!thisList.empty()) {
            for (auto x : thisList) {
                out << x << " ";
            }
            out << std::endl;
        }
    }
    return out;
}

#endif //SEPARATECHAININGHASHTABLE_SEPARATECHAINING_H
