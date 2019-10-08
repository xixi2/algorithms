//
// Created by xixi2 on 19-7-5.
//

#include "SeparateChaining.h"

/**
 * 判断一个数是否是质数
 * @param n
 * @return
 */
bool isPrime(int n) {
    if (n == 2 || n == 3) {
        return true;
    }
    if (n == 1 || n % 2 == 0) {
        return false;
    }
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

/**
 * 寻找下一个质数
 * @param n
 * @return
 */
int nextPrime(int n) {
    if (n % 2 == 0) {
        ++n;
    }
    for (; !isPrime(n); n += 2);
    return n;
}


/**
 * 给出string对象的一个哈希值
 * @param key
 * @return
 */
size_t hash(const std::string &key) {
    size_t hashVal = 0;
    for (char ch: key) {
        hashVal = 37 * hashVal + ch;
    }
    return hashVal;
}

/**
 * 整形的哈希函数
 * @param key
 * @return
 */
size_t hash(int key) {
    return key;
}



