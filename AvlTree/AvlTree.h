//
// Created by xixi2 on 19-7-4.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <utility>
#include <algorithm>
#include <cmath>
#include <iostream>
#include "dsexceptions.h"

template<typename Comparable>
class AvlTree {
public:
    AvlTree() : root{nullptr} {}

    AvlTree(const AvlTree &rhs) : root{nullptr} {
        root = clone(rhs.root);
    }

    AvlTree(AvlTree &&rhs) noexcept : root{rhs.root} {
        rhs.root = nullptr;
    }

    ~AvlTree() {
        makeEmpty(root);
    }

    /**
     * 拷贝赋值运算符函数
     * 设计得十分精妙
     * @param rhs
     * @return
     */
    AvlTree &operator=(const AvlTree &rhs) {
        AvlTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    /**
     *移动赋值运算符函数
     * 设计得十分精妙
     * @param rhs
     * @return
     */
    AvlTree &operator=(AvlTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        return *this;
    }

    const Comparable &findMin() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }
        return findMin(root)->element;
    }

    const Comparable &findMax() const {
        if (isEmpty()) {
            throw UnderflowException{};
        }
        return findMax(root)->element;
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    bool contains(const Comparable &x) const {
        return contains(x, root);
    }

    void printTree() const {
        if (isEmpty()) {
            std::cout << "Empty tree" << std::endl;
        } else {
            printTree(root);
        }
    }

    void makeEmpty() {
        makeEmpty(root);
    }

    void insert(const Comparable &x) {
        insert(x, root);
    }

    void insert(Comparable &&x) {
        insert(std::move(x), root);
    }

    /**
     * 从树中移除关键字的值为x的节点,若不存在这样的节点就什么都不做
     * @param x
     */
    void remove(const Comparable &x) {
        remove(x, root);
    }

private:
    /**
     * 一棵AVL树是一棵这样的二叉查找树: 它的每个节点的左子树和右子树的高度最多差1
     * 空树的高度定义为1, 叶子节点的高度定义为0
     * 因此与普通的二叉查找树相比,AVL树的节点结构中需要保留高度信息
     */
    struct AvlNode {
        Comparable element;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const Comparable &ele, AvlNode *lt, AvlNode *rt, int h = 0)
                : element(ele), left(lt), right(rt), height(h) {}

        AvlNode(Comparable &&ele, AvlNode *lt, AvlNode *rt, int h = 0)
                : element(std::move(ele)), left(lt), right(rt), height(h) {}
    };

    AvlNode *root;
    static const int ALLOWED_IMBALANCE = 1;

    /**
     * 内部方法,用来在以t为根的子树上插入x
     * @param x: 要插入的元素
     * @param t: 将要插入x的子树
     */
    void insert(const Comparable &x, AvlNode *&t) {
        if (t == nullptr) {
            t = new AvlNode(x, nullptr, nullptr);
        } else if (x < t->element) {
            insert(x, t->left);
        } else if (x > t->element) {
            insert(x, t->right);
        }
        balance(t);
    }

    void insert(Comparable &&x, AvlNode *&t) {
        if (t == nullptr) {
            t = new AvlNode(std::move(x), nullptr, nullptr);
        } else if (std::move(x) < t->element) {
            insert(std::move(x), t->left);
        } else if (std::move(x) > t->element) {
            insert(std::move(x), t->right);
        }
        balance(t);
    }

    void remove(const Comparable &x, AvlNode *&t) {
        if (t == nullptr) {
            return;     // 没找到值为x的节点, 什么也不做
        } else if (x < t->element) {
            remove(x, t->left);
        } else if (x > t->element) {
            remove(x, t->right);
        } else if (t->left != nullptr && t->right != nullptr) {
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        } else {
            AvlNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }
        balance(t);
    }

    /**
     * 将以t为根的子树变成平衡的
     * @param t
     */
    void balance(AvlNode *&t) {
        if (t == nullptr) {
            return;
        }
        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
            // 左子树的高度比右子树的高度高了至少2,但是左儿子节点的左子树的高度比右子树高
            if (height(t->left->left) >= height(t->left->right)) {
//                std::cout << "左单旋" << std::endl;
                rotateWithLeftChild(t);
            } else {
                // 左子树的高度比右子树的高度高了至少2,其左儿子节点的左子树的高度最多和右子树一样高
//                std::cout << "左右双旋" << std::endl;
                doubleWithLeftChild(t);
            }
        } else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
            if (height(t->right->right) >= height(t->right->left)) {
//                std::cout << "右单旋" << std::endl;
                rotateWithRightChild(t);    // 右单旋
            } else {
//                std::cout << "右左双旋" << std::endl;
                doubleWithRightChild(t);    // 右左双旋
            }
        }
        t->height = std::max(height(t->left), height(t->right)) + 1;
    }

    AvlNode *findMin(AvlNode *t) const {
        if (t == nullptr) {
            return nullptr;
        }
        if (t->left == nullptr) {
            return t;
        }
        return findMin(t->left);
    }

    AvlNode *findMax(AvlNode *t) const {
        if (t != nullptr) {
            while (t->right != nullptr) {
                t = t->right;
            }
        }
        return t;
    }


    /**
     * 在以t为根的子树上存不存在元素x
     * @param x
     * @param t
     * @return
     */
    bool contains(const Comparable &x, AvlNode *t) const {
        if (t == nullptr) {
            return false;
        } else if (t->element > x) {
            return contains(x, t->left);
        } else if (t->element < x) {
            return contains(x, t->right);
        } else {
            return true;
        }
    }

    /**
     * 后序遍历, 将以t为根的子树置为空
     * @param t
     */
    void makeEmpty(AvlNode *&t) {
        if (t != nullptr) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    void printTree(AvlNode *t) const {
        if (t != nullptr) {
            printTree(t->left);
            std::cout << t->element << std::endl;
            printTree(t->right);
        }
    }

    /***
     * 内部访问,复制以t为根的子树
     * 以后序遍历的方式: 延伸问题, 如何复制一棵树
     * @param t
     * @return
     */
    AvlNode *clone(AvlNode *t) const {
        if (t == nullptr) {
            return nullptr;
        } else {
            return new AvlNode{t->element, clone(t->left), clone(t->right)};
        }
    }

    /**
     * 返回节点的高度, 空节点的高度为-1, 叶子节点的高度为0
     * @param t
     * @return
     */
    int height(AvlNode *t) const {
        return t == nullptr ? -1 : t->height;
    }

    int max(int lhs, int rhs) const {
        return lhs > rhs ? lhs : rhs;
    }


    /**
     * 左单旋
     * @param k2: 需要进行左单旋的根节点
     */
    void rotateWithLeftChild(AvlNode *&k2) {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;

        // k2的高度发生了变化
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    /**
     * 右单旋
     * @param k1: 需要进行右单旋的根节点
     */
    void rotateWithRightChild(AvlNode *&k1) {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(k1->height, height(k2->right)) + 1;
        k1 = k2;
    }

    /**
     * 左右双旋分为以k3的左孩子节点为根的右单旋和以k3为根的左单旋
     * @param k3
     */
    void doubleWithLeftChild(AvlNode *&k3) {
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }

    /**
     * 以k1为根的右左双旋, 分为两步,第一步:以k1的右子树为根的左单旋, 再以k1为根的右单旋
     * @param k1
     */
    void doubleWithRightChild(AvlNode *&k1) {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
};


#endif //AVLTREE_AVLTREE_H
