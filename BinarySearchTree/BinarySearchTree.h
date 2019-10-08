//
// Created by xixi2 on 19-7-3.
//

#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H

#include <utility>
#include <iostream>
#include "dsexceptions.h"

template<typename Comparable>
class BinarySearchTree {
public:
    BinarySearchTree();

    BinarySearchTree(const BinarySearchTree &rhs);

    BinarySearchTree(BinarySearchTree &&rhs) noexcept;

    ~BinarySearchTree();

    const Comparable &findMin() const;

    const Comparable &findMax() const;

    bool contains(const Comparable &x) const;

    bool isEmpty() const;

    void printTree(std::ostream &out = std::cout) const;

    void makeEmpty();

    void insert(const Comparable &x);

    void insert(Comparable &&x);

    void remove(const Comparable &x);

    BinarySearchTree &operator=(const BinarySearchTree &rhs);

    BinarySearchTree &operator=(BinarySearchTree &&rhs) noexcept;

private:
    struct BinaryNode {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
                : element(theElement), left(lt), right(rt) {}

        BinaryNode(Comparable &&theElement, BinaryNode *lt, BinaryNode *rt)
                : element(std::move(theElement)), left(lt), right(rt) {}
    };

    BinaryNode *root;

    /**
     * @param x
     * @param t: 指针t是对实参指针的引用,因此在insert中改变了指针t即改变了实参指针
     */
    void insert(const Comparable &x, BinaryNode *&t);

    void insert(Comparable &&x, BinaryNode *&t);

    void remove(const Comparable &x, BinaryNode *&t);

    BinaryNode *findMin(BinaryNode *t) const;

    BinaryNode *findMax(BinaryNode *t) const;

    bool contains(const Comparable &x, BinaryNode *t) const;

    bool makeEmpty(BinaryNode *&t);

    void printTree(BinaryNode *t, std::ostream &out) const;

    BinaryNode *clone(BinaryNode *t) const;
};


//==========================private方法===========================
/**
 * 测试一项是否在子树上的内部方法
 * 注意测试的顺序, 首先应该对是否是空树进行测试,因为否则会产生一个试图通过nullptr指针来访问数据成员的运行时错误
 * 剩下的测试 **使得最不可能的情况安排在最后进行**
 * @tparam Comparable
 * @param x: 要查找的项
 * @param t: 作为该子树的根的节点
 * @return
 */
template<typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable &x, BinarySearchTree<Comparable>::BinaryNode *t) const {
    if (t == nullptr) {
        return false;
    }
    if (x < t->element) {
        return contains(x, t->left);
    } else if (x > t->element) {
        return contains(x, t->right);
    } else {
        return true;
    }
}


/**
 * 返回指向树中最小元素所在节点的指针, 递归实现
 * @tparam Comparable
 * @return
 */
template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findMin(
        BinarySearchTree<Comparable>::BinaryNode *t) const {
    if (t == nullptr) {
        return nullptr;
    }
    if (t->left == nullptr) {
        return t;
    }
    return findMin(t->left);
}

/**
 * 返回指向树中最大元素的所在节点的指针, 非递归实现
 * @tparam Comparable
 * @param t
 * @return
 */
template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::findMax(
        BinarySearchTree<Comparable>::BinaryNode *t) const {
    if (t != nullptr) {
        while (t->right != nullptr) {
            t = t->right;
        }
    }
    return t;
}


/**
 * 将x插入到树中,可以沿着树查找, 若找到x,则什么都不做,否则将x插入到所遍历的路径的最后一点上
 * @tparam Comparable
 * @param x
 */
template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x, BinarySearchTree<Comparable>::BinaryNode *&t) {
    if (t == nullptr) {
        t = new BinaryNode(x, nullptr, nullptr);
    } else if (t->element > x) {
        insert(x, t->left);
    } else if (t->element < x) {
        insert(x, t->right);
    } else {
        // 重复元素, 什么也不做
        return;
    }
}

/**
 * 向子树插入元素的内部方法
 * @tparam Comparable
 * @param x: 通过移动实现要插入的项
 * @param t: 置子树的新根
 */
template<typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable &&x, BinarySearchTree<Comparable>::BinaryNode *&t) {
    if (t == nullptr) {
        t = new BinaryNode(std::move(x), nullptr, nullptr);
    } else if (t->element > x) {
        insert(std::move(x), t->left);
    } else if (t->element < x) {
        insert(std::move(x), t->right);
    } else {
        // 重复元素,什么也不做
        return;
    }
}


/**
 * 从一棵子树删除一项的内部方法
 * @tparam Comparable
 * @param x: 要被删除的项
 * @param t: 置子树的新根
 */
template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x, BinarySearchTree<Comparable>::BinaryNode *&t) {
    if (t == nullptr) {
        return;
    }
    if (x < t->element) {
        remove(x, t->left);
    } else if (x > t->element) {
        remove(x, t->right);
    } else if (t->left != nullptr && t->right != nullptr) {     // 节点t有两个儿子
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    } else {
        BinaryNode *oldNode = t;    // 指针oldNode和指针t指向同一个对象
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode;
    }
}

/**
 * 使子树为空的内部方法
 * @tparam Comparable
 * @param t
 * @return
 */
template<typename Comparable>
bool BinarySearchTree<Comparable>::makeEmpty(BinarySearchTree<Comparable>::BinaryNode *&t) {
    if (t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

template<typename Comparable>
typename BinarySearchTree<Comparable>::BinaryNode *BinarySearchTree<Comparable>::clone(
        BinarySearchTree<Comparable>::BinaryNode *t) const {
    if (t == nullptr) {
        return nullptr;
    }
    return new BinaryNode(t->element, clone(t->left), clone(t->right));
}

template<typename Comparable>
void BinarySearchTree<Comparable>::printTree(BinarySearchTree<Comparable>::BinaryNode *t, std::ostream &out) const {
    if (t != nullptr) {
        printTree(t->left, out);
        out << t->element << std::endl;
        printTree(t->right, out);
    }
}

//=======================public方法=========================
/**
 * 析构函数: 销毁树中每一个节点,回收内存
 * @tparam Comparable
 */
template<typename Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree() {
    makeEmpty();
}

template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree()
        :root(nullptr) {}

/**
 * 拷贝构造函数
 * @tparam Comparable
 * @param rhs
 */
template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree &rhs)
        :root(nullptr) {
    root = clone(rhs.root);
}

/**
 * 直接将rhs指针指向的树的根节点的资源转移给当前树的根节点
 * 但是在退出移动构造函数前不要忘记将rhs置于一个可析构的安全状态,即将rhs.root置空,否则, rhs离开作用域时会调用析构函数, 释放内存
 * @tparam Comparable
 * @param rhs
 */
template<typename Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(BinarySearchTree &&rhs) noexcept:root(rhs.root) {
    rhs.root = nullptr;
}

/**
 * 拷贝赋值运算符函数
 * @tparam Comparable
 * @param rhs
 * @return
 */
template<typename Comparable>
BinarySearchTree<Comparable> &BinarySearchTree<Comparable>::operator=(const BinarySearchTree &rhs) {
    BinarySearchTree copy = rhs;
    std::swap(copy, *this);
    return *this;
}

/**
 * 如何处理自赋值问题的?
 * @tparam Comparable
 * @param rhs
 * @return
 */
template<typename Comparable>
BinarySearchTree<Comparable> &BinarySearchTree<Comparable>::operator=(BinarySearchTree &&rhs) noexcept {
    std::swap(root, rhs.root);
    return *this;
}


template<typename Comparable>
const Comparable &BinarySearchTree<Comparable>::findMax() const {
    if (isEmpty()) {
        throw UnderflowException{};
    }
    return findMax(root)->element;
}


template<typename Comparable>
const Comparable &BinarySearchTree<Comparable>::findMin() const {
    if (isEmpty()) {
        throw UnderflowException{};
    }
    return findMin(root)->element;
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const {
    return root == nullptr;
}

template<typename Comparable>
bool BinarySearchTree<Comparable>::contains(const Comparable &x) const {
    return contains(x, root);
}


template<typename Comparable>
void BinarySearchTree<Comparable>::printTree(std::ostream &out) const {
    if (isEmpty()) {
        out << "Empty tree" << std::endl;
    } else {
        printTree(root, out);
    }
}

template<typename Comparable>
void BinarySearchTree<Comparable>::insert(const Comparable &x) {
    insert(x, root);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::insert(Comparable &&x) {
    insert(std::move(x), root);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::remove(const Comparable &x) {
    remove(x, root);
}

template<typename Comparable>
void BinarySearchTree<Comparable>::makeEmpty() {
    makeEmpty(root);
}


#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H
