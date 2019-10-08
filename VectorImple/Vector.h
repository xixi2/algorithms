//
// Created by xixi2 on 19-7-8.
//

#ifndef INC_0708_VECTOR_VECTOR_H
#define INC_0708_VECTOR_VECTOR_H

#include <iostream>
#include <algorithm>
#include <string>
#include <stdexcept>

template<typename Object>
class Vector;

/**
 * 友元函数：可以将另一个模板的所有实例都声明为友元函,也可以限定特定的实例为友元
 * @tparam Object
 * @param out
 * @param vec
 * @return
 */
template<typename Object>
std::ostream &operator<<(std::ostream &out, const Vector<Object> &vec);


template<typename Object>
class Vector {
    friend std::ostream &operator<<<Object>(std::ostream &out, const Vector &rhs);

public:
    explicit Vector(int initSize = 0) : theSize(initSize), theCapacity(initSize + SPARE_CAPACITY) {
        objects = new Object[theCapacity];
    }

    Vector(int initSize, const Object value) : theSize(initSize), theCapacity(initSize + SPARE_CAPACITY) {
        objects = new Object[theCapacity];
        for (int k = 0; k < initSize; ++k) {
            objects[k] = value;
        }
    }

    Vector(const Vector &rhs) : theSize(rhs.theSize), theCapacity(rhs.theCapacity), objects(nullptr) {
        std::cout << "拷贝构造函数" << std::endl;
        std::cout << std::endl;

        objects = new Object[theCapacity];
        for (int k = 0; k < theSize; ++k) {
            objects[k] = rhs.objects[k];
        }
    }

    /* Vector &operator=(const Vector &rhs) {
         std::cout << "拷贝赋值运算符函数" << std::endl;

         Vector copy = rhs;
         std::swap(copy, *this);
         return *this;
     }*/

    /**实现方法2
     * 拷贝赋值运算符
     * @param rhs
     * @return
     */
    Vector &operator=(const Vector &rhs) {
        std::cout << "拷贝赋值运算符函数" << std::endl;

        Object *lobjects = new Object[rhs.theCapacity];
        for (int k = 0; k < theSize; ++k) {
            lobjects[k] = rhs.objects[k];
        }
        delete[] objects;

        // 当本函数退出时,lobjects退出其作用域，但是其指向的内存空间是动态分配的内存不会被释放
        objects = lobjects;
        theSize = rhs.theSize;
        theCapacity = rhs.theCapacity;

        return *this;
    }

    Vector(Vector &&rhs) noexcept
            : theSize(rhs.theSize), theCapacity(rhs.theCapacity), objects(rhs.objects) {
        std::cout << "移动构造函数" << std::endl;

        // 将右侧运算对象rhs置于安全可析构的状态
        rhs.objects = nullptr;
        rhs.theCapacity = rhs.theSize = 0;
    }

    Vector &operator=(Vector &&rhs) noexcept {
        std::cout << "移动赋值运算符函数" << std::endl;

        // 检测自赋值: 通过比较对象地址来检测自赋值
        if (this != &rhs) {
            delete[]objects;
            objects = rhs.objects;
            theSize = rhs.theSize;
            theCapacity = rhs.theCapacity;

            // 将右侧运算对象rhs置于安全可析构的状态
            rhs.objects = nullptr;
            rhs.theCapacity = rhs.theSize = 0;
        }
    }

    /**实现方法2
     * 移动赋值运算符函数
     * @param rhs
     * @return
     */
/*    Vector &operator=(Vector &&rhs) noexcept {
        std::cout << "移动赋值运算符函数" << std::endl;
        std::swap(objects, rhs.objects);
        std::swap(theSize, rhs.theSize);
        std::swap(theCapacity, rhs.theCapacity);
        return *this;
    }*/

    /**
     * 改变Vector中当前元素个数
     * @param newSize
     * @return
     */
    Vector resize(int newSize) {
        if (newSize > theCapacity) {
            reserve(newSize * 2);
        }
        theSize = newSize;
    }

    /**
     * 改变Vector中当前最大可用空间个数
     * @param newCapacity
     */
    void reserve(int newCapacity) {
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
        check(index, "out of range");
        return objects[index];
    }

    const Object &operator[](int index) const {
        check(index, "out of range");
        return objects[index];
    }

    int size() const {
        return theSize;
    }

    int capacity() const {
        return theCapacity;
    }

    bool empty() const {
        return theSize == 0;
    }

    void push_back(const Object &x) {
        // resize(2*capactiy() + 1)是为了保证当capacity()==0时仍能正常分配空间
        if (theSize == theCapacity) {
            resize(2 * capacity() + 1);
        }
        objects[theSize++] = x;
    }

    void push_back(Object &&x) {
        // 以后源对象x应该在移动后不再使用
        if (theSize == theCapacity) {
            resize(2 * capacity() + 1);
        }
        objects[theSize++] = std::move(x);
    }

    void pop_back() {
        check(0, "begin on empty Vector");
        --theSize;
    }

    const Object &back() const {
        check(0, "back on empty Vector");
        return objects[theSize - 1];
    }

    Object &back() {
        check(0, "back on empty Vector");
        return objects[theSize - 1];
    }

    ~Vector() {
        delete[]objects;
    }

    typedef Object *iterator;
    typedef const Object *const_iterator;

    iterator begin() {
        check(0, "begin on empty Vector");
        return &objects[0];
    }

    const iterator begin() const {
        check(0, "begin on empty Vector");
        return &objects[0];
    }

    /**
     * 注意这里不是指向最后一个元素,而是指向最后一个元素之后的位置
     * @return
     */
    iterator end() {
        return &objects[size()];
    }

    /**
     * 注意这里不是指向最后一个元素,而是指向最后一个元素之后的位置
     * @return
     */
    const iterator end() const {
        return &objects[size()];
    }

    static const int SPARE_CAPACITY = 16;
private:
    int theSize;
    int theCapacity;

    // 数组是指向一块内存块的指针变量, 内存块无法重新调整大小,但是可以重新获得一个新的内存块
    Object *objects;

    void check(std::size_t i, const std::string &msg) const {
        // 注意这里的i是无符号数,那么如何禁止小于0的索引呢?
        if (i >= theSize) {
            throw std::out_of_range(msg);
        }
    }
};


template<typename Object>
std::ostream &operator<<(std::ostream &out, const Vector<Object> &vec) {
    std::cout << "包含元素个数为" << vec.size() << std::endl;
    for (int i = 0; i < vec.size(); ++i) {
        out << vec.objects[i] << " ";
    }
    out << std::endl;
}


#endif //INC_0708_VECTOR_VECTOR_H
