//
// Created by xixi2 on 19-7-13.
//

#ifndef SPLAYTREE_SPLAYTREE_H
#define SPLAYTREE_SPLAYTREE_H

#include <iostream>
#include "dsexceptions.h"

template<typename Comparable>
class SplayTree {
public:
    SplayTree() {
        nullNode = new BinaryNode;
        nullNode->left = nullNode->right = nullNode;
        root = nullNode;
    }

    SplayTree(const SplayTree &rhs) {
        nullNode = new BinaryNode;
        nullNode->left = nullNode->right = nullNode;
        root = clone(rhs.root);
    }

    SplayTree(SplayTree &&rhs)
            : root{rhs.root}, nullNode{rhs.nullNode} {
        rhs.root = nullptr;
        rhs.nullNode = nullptr;
    }

    ~SplayTree() {
        makeEmpty();
        delete nullNode;
    }

    SplayTree &operator=(const SplayTree &rhs) {
        SplayTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    SplayTree &operator=(SplayTree &&rhs) noexcept {
        std::swap(root, rhs.root);
        std::swap(nullNode, rhs.nullNode);
        return *this;
    }

    /**
     * 寻找树中的最小节点的值
     * 如果树为空则抛出UnderflowException异常
     * @return
     */
    const Comparable &findMin() {
        if (isEmpty()) {
            throw UnderflowException{};
        }
        BinaryNode *ptr = root;
        while (ptr->left != nullNode) {
            ptr = ptr->left;
        }
        splay(ptr->element, root);
        return ptr->element;
    }

    const Comparable &findMax() {
        if (isEmpty()) {
            throw UnderflowException{};
        }
        BinaryNode *ptr = root;
        while (ptr->right != nullNode) {
            ptr = ptr->right;
        }
        splay(ptr->element, root);
        return ptr->element;
    }

    bool contains(const Comparable &x) {
        if (isEmpty()) {
            return false;
        }
        splay(x, root);
        return root->element == x;
    }

    bool isEmpty() const {
        return root == nullNode;
    }

    void printTree() const {
        if (isEmpty()) {
            std::cout << "Empty tree" << std::endl;
        } else {
            printTree(root);
        }
    }

    void makeEmpty() {
        while (!isEmpty()) {
            findMax();
            remove(root->element);
        }
    }

    void insert(const Comparable &x) {
        static BinaryNode *newNode = nullptr;
        if (newNode == nullptr) {
            newNode = new BinaryNode;
        }
        newNode->element = x;
        if (root == nullNode) {
            newNode->left = newNode->right = nullNode;
            root = newNode;
        } else {
            splay(x, root);
            if (x < root->element) {
                newNode->left = root->left;
                newNode->right = root;
                root->left = nullNode;
                root = newNode;
            } else if (root->element < x) {
                newNode->right = root->right;
                newNode->left = root;
                root->right = nullNode;
                root = newNode;
            } else {
                return;
            }
        }
        newNode = nullptr;
    }

    void remove(const Comparable &x) {
        if (!contains(x)) {
            return;
        }
        BinaryNode *newTree;
        if (root->left == nullNode) {
            newTree = root->right;
        } else {
            newTree = root->left;
            splay(x, newTree);
            newTree->right = root->right;
        }
        delete root;
        root = newTree;
    }

private:
    struct BinaryNode {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode() : left{nullptr}, right{nullptr} {}

        BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt)
                : element{theElement}, left{lt}, right{rt} {}
    };

    BinaryNode *root;
    BinaryNode *nullNode;   //使用nullNode逻辑上表示一个nullptr指针

    /**
     * 内部方法：回收子树t上的内部节点
     * 注意：这很容易耗尽栈空间
     * @param t
     */
    void reclaimMemory(BinaryNode *t) {
        if (t != t->left) {
            reclaimMemory(t->left);
            reclaimMemory(t->right);
            delete t;
        }
    }


    void printTree(BinaryNode *t) const {
        if (t != t->left) {
            printTree(t->left);
            std::cout << t->element << std::endl;
            printTree(t->right);
        }
    }

    BinaryNode *clone(BinaryNode *t) const {
        if (t == t->left)   // 不能在nullNode上测试
            return nullNode;
        else
            return new BinaryNode{t->element, clone(t->left), clone(t->right)};
    }

    void rotateWithLeftChild(BinaryNode *&k2) {
        BinaryNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2 = k1;
    }

    void rotateWithRightChild(BinaryNode *&k1) {
        BinaryNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1 = k2;
    }

    /**
     * 指向自顶向下展开的内部方法
     * 最后访问的节点成为新的根
     * 为了使用不同的展开算法，可以覆盖这个方法，不过，展开树代码依赖于所访问的通向根的项
     * @param x: x是要展开的目标项
     * @param t: t是要展开的子树的根
     */
    void splay(const Comparable &x, BinaryNode *&t) {
        BinaryNode *leftTreeMax, *rightTreeMin;
        static BinaryNode header;
        header.left = header.right = nullNode;
        leftTreeMax = rightTreeMin = &header;

        nullNode->element = x;
        for (;;) {
            if (x < t->element) {
                if (x < t->left->element) {
                    rotateWithLeftChild(t);
                }
                if (t->left == nullNode) {
                    break;
                }
                rightTreeMin->left = t;
                rightTreeMin = t;
                t = t->left;
            } else if (t->element < x) {
                if (t->right->element < x) {
                    rotateWithRightChild(t);
                }
                if (t->right == nullNode) {
                    break;
                }
                leftTreeMax->right = t;
                leftTreeMax = t;
                t = t->right;
            } else {
                break;
            }
        }
        leftTreeMax->right = t->left;
        rightTreeMin->left = t->right;
        t->left = header.right;
        t->right = header.left;
    }
};


#endif //SPLAYTREE_SPLAYTREE_H
