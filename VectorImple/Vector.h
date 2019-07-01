//
// Created by xixi2 on 19-6-26.
//

#ifndef VECTORIMPLE_VECTOR_H
#define VECTORIMPLE_VECTOR_H

#include <algorithm>
#include <string>
#include <stdexcept>
#include <iostream>

template<typename Object>
class Vector;

template<typename Object>
std::ostream &operator<<(std::ostream &os, const Vector<Object> &vec);


template<typename Object>
class Vector {
    /**
     * 每个Vector实例将访问权限授予用相同类型实例化的输出运算符
     * @param os
     * @param vec
     */
    friend std::ostream &operator<<<Object>(std::ostream &os, const Vector &vec);

public:
    explicit Vector(int initSize = 0) : theSize(initSize), theCapacity(initSize + SPARE_CAPACITY) {
        objects = new Object[theCapacity];
    }

    /**
     * TODO: 如何支持initializer_list
     * @param il
     */
//    Vector(std::initializer_list<Object> il) : theSize(il.size()), theCapacity(il.size() + SPARE_CAPACITY),
//                                               objects(il.begin()) {}

    /**
     * 拷贝构造函数,本vector和被拷贝的vector指向不同的内存
     * @param rhs
     */
    Vector(const Vector &rhs) : theSize(rhs.theSize), theCapacity(rhs.theCapacity), objects(nullptr) {
        std::cout << "拷贝构造函数" << std::endl;
        objects = new Object[theCapacity];  // new的功能:
        for (int k = 0; k < theSize; ++k) {
            objects[k] = rhs.objects[k];
        }
    }

    /** 实现方法1
     * 拷贝赋值运算符函数,必须处理自赋值问题
     * @param rhs
     * @return
     */
    Vector &operator=(const Vector &rhs) {
        std::cout << "拷贝赋值运算符函数" << std::endl;
        // 拷贝右边的数组
        Object *lobjects = new Object[rhs.theCapacity];
        for (int k = 0; k < theSize; ++k) {
            lobjects[k] = rhs.objects[k];
        }
        delete[] rhs.objects;
        objects = lobjects;
        theSize = rhs.theSize;
        theCapacity = rhs.theCapacity;
        return *this;
    }

    /**实现方法2
     * 拷贝赋值运算符
     * @param rhs
     * @return
     */
    /*Vector &operator=(const Vector &rhs) {
        Vector copy = rhs;
        std::swap(copy, *this);
        return *this;
    }*/


    ~Vector() {
        delete[] objects;
    }

    /**
     * 移动构造函数
     * @param rhs
     */
    Vector(Vector &&rhs) noexcept
            : theSize(rhs.theSize), theCapacity(rhs.theCapacity), objects(rhs.objects) {
        std::cout << "移动构造函数" << std::endl;
        // 让右侧运算对象进入可析构的状态
        rhs.objects = nullptr;
        rhs.theCapacity = rhs.theSize = 0;
    }

    /**实现方法1
     * TODO: 移动赋值运算符函数和移动构造函数还有问题
     * 移动赋值运算符函数, 为什么返回值是引用呢?
     * @param rhs
     * @return
     */

    Vector &operator=(Vector &&rhs) {
//        std::cout << "移动赋值运算符函数" << std::endl;
//        std::cout << "rhs.theSize:" << rhs.theSize << " rhs.theCapcity:" << rhs.theCapacity << std::endl;
//        for (int i = 0; i < rhs.size(); i++) {
//            std::cout << *(rhs.objects + i) << " ";
//        }
        std::cout << std::endl;
        theSize = rhs.theSize;
        theCapacity = rhs.theCapacity;
        objects = rhs.objects;
        rhs.objects = nullptr;
        rhs.theCapacity = rhs.theSize = 0;
        return *this;
    }

    /**实现方法2
     * 移动赋值运算符函数
     * @param rhs
     * @return
     */
//    Vector &operator=(Vector &&rhs) noexcept {
//        std::cout << "移动赋值运算符函数" << std::endl;
//        std::swap(objects, rhs.objects);
//        std::swap(theSize, rhs.theSize);
//        std::swap(theCapacity, rhs.theCapacity);
//        return *this;
//    }

    Vector resize(int newSize) {
        if (newSize > theCapacity) {
            reserve(newSize * 2);
        }
        theSize = newSize;
    }

    void reserve(int newCapacity) {
        // 为什么newCapacity < theSize返回
        // std::move和std::swap
        if (newCapacity < theSize) {
            return;
        }
        Object *newArray = new Object[newCapacity];
        for (int k = 0; k < theSize; ++k) {
            newArray[k] = std::move(objects[k]);
        }
        theCapacity = newCapacity;
        std::swap(objects, newArray);
        delete[]newArray;
    }

    Object &operator[](int index) {
        return objects[index];
    }


    const Object &operator[](int index) const {
        return objects[index];
    }

    int size() const {
        return theSize;
    }

    bool empty() const {
        return size() == 0;
    }

    int capacity() const {
        return theCapacity;
    }

    void push_back(const Object &x) {
        // 为什么resize(2 * theCapacity + 1)
        if (theSize == theCapacity) {
            resize(2 * theCapacity + 1);
        }
        objects[theSize++] = x;
    }

    void push_back(Object &&x) {
        if (theSize == theCapacity) {
            reserve(2 * theCapacity + 1);
        }
        objects[theSize++] = std::move(x);
    }

    void pop_back() {
        check(0, "begin on empty Vector");
        --theSize;
    }

    /**
     * 返回最后一个元素的引用
     * @return
     */
    const Object &back() const {
        check(0, "back on empty Vector");
        return objects[theSize - 1];
    }

    Object &back() {
        check(0, "back on empty Vector");
        return objects[theSize - 1];
    }

    typedef Object *iterator;
    typedef const Object *const_iterator;

    /**
     * 返回指向数组第一个元素的指针
     * @return
     */
    iterator begin() {
        // 需要检测数组是否为空
        check(0, "begin on empty Vector");
        return &objects[0];
    }

    const_iterator begin() const {
        check(0, "begin on empty Vector");
        return &objects[0];
    }

    iterator end() {
        check(0, "end on empty Vector");
        return &objects[theSize - 1];
    }

    const_iterator end() const {
        check(0, "end on empty Vector");
        return &objects[theSize - 1];
    }

    static const int SPARE_CAPACITY = 16;
private:
    int theSize;
    int theCapacity;
    Object *objects;   // 数组是指向一块内存块的指针变量, 内存块无法重新调整大小,但是可以重新获得一个新的内存块

    /**
     * check该如何写
     * @param i
     * @param msg
     */
    void check(std::size_t i, const std::string &msg) const {
        if (i >= theSize || i < 0) {
            throw std::out_of_range(msg);
        }
    }
};


template<typename Object>
std::ostream &operator<<(std::ostream &os, const Vector<Object> &vec) {
    for (int i = 0; i < vec.size(); ++i) {
        os << vec.objects[i] << " ";
    }
    os << std::endl;
}

#endif //VECTORIMPLE_VECTOR_H
