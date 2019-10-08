//
// Created by xixi2 on 19-7-8.
//

#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <utility>

template<typename Object>
class List;


template<typename Object>
std::ostream &operator<<(std::ostream &out, const List<Object> &rhs);

template<typename Object>
class List {
    friend std::ostream &operator<<<Object>(std::ostream &out, const List &rhs);
    // Node类的声明在前, const_iterator的声明在后
private:
    struct Node {
        Object data;
        Node *prev;
        Node *next;

        Node(const Object &d = Object{}, Node *p = nullptr, Node *n = nullptr) :
                data(d), prev(p), next(n) {}

        Node(Object &&d, Node *p = nullptr, Node *n = nullptr) :
                data(std::move(d)), prev(p), next(n) {}
    };

public:
    // 对位置的抽象
    class const_iterator {
    public:
        const_iterator() : current{nullptr} {}

        const Object &operator*() const {
            return retrieve();
        }

        /**
         * 前置++运算符
         * @return
         */
        const_iterator &operator++() {
            current = current->next;
            return *this;
        }

        /**
         * 后置++运算符,返回旧对象的拷贝
         * 共调用几次拷贝构造函数呢?
         * @return
         */
        const_iterator operator++(int) {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        bool operator==(const const_iterator &rhs) const {
            return current == rhs.current;
        }

        bool operator!=(const const_iterator &rhs) const {
            return !(*this == rhs);
        }

    protected:
        Node *current;

        /**
         * 返回对current所指向元素的引用,current不能变,但是可以改变current所指向的元素
         * @return
         */
        Object &retrieve() const { return current->data; }

        const_iterator(Node *p) : current(p) {}

        friend class List<Object>;
    };

    class iterator : public const_iterator {
    public:
        iterator() {}

        Object &operator*() { return const_iterator::retrieve(); }

        const Object &operator*() const { return const_iterator::operator*(); }

        iterator &operator++() {
            this->current = this->current->next;
            return *this;
        }

        iterator &operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }

    protected:
        iterator(Node *p) : const_iterator(p) {}

        friend class List<Object>;
    };

public:
    List() { init(); }

    List(const List &rhs);

    ~List();

    List &operator=(const List &rhs);

    List(List &&rhs) noexcept;

    List &operator=(List &&rhs) noexcept;

    iterator begin() { return head->next; }

    const_iterator begin() const { return head->next; }

    iterator end() { return tail; }

    const_iterator end() const { return tail; }

    int size() const { return theSize; }

    bool empty() const { return size() == 0; }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    /**
     * 返回首元素的引用
     * @return
     */
    Object &front() { return *begin(); }

    const Object &front() const { return *begin(); }

    Object &back() { return *(--end()); }

    const Object &back() const { return *(--end()); }

    iterator insert(iterator itr, const Object &x);

    iterator insert(iterator itr, Object &&x);

    iterator erase(iterator itr);

    iterator erase(iterator from, iterator to);


    void push_front(const Object &x) {
        insert(begin(), x);
    }

    void push_front(Object &&x) {
        insert(begin(), std::move(x));
    }

    void push_back(const Object &x) {
        insert(end(), x);
    }

    void push_back(Object &&x) {
        insert(end(), std::move(x));
    }

    void pop_front() {
        erase(begin());
    }

    void pop_back() {
        erase(--end());
    }


private:
    int theSize;
    Node *head;
    Node *tail;

    void init() {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};


/**
 * 在itr前插入x
 * @tparam Object
 * @param itr
 * @param x
 * @return
 */
template<typename Object>
typename List<Object>::iterator List<Object>::insert(List<Object>::iterator itr, const Object &x) {
    Node *p = itr.current;
    theSize++;
    Node *node = new Node(x, p->prev, p);
    p->prev = p->prev->next = node;
    return node;
}

template<typename Object>
typename List<Object>::iterator List<Object>::insert(List<Object>::iterator itr, Object &&x) {
    Node *p = itr.current;
    theSize++;
    Node *node = new Node(std::move(x), p->prev, p);
    p->prev = p->prev->next = node;
    return node;
}


/**
 * 从双向链表中删除itr指向的节点
 * @tparam Object
 * @param itr：返回被删除元素之后元素的迭代器
 * @return
 */
template<typename Object>
typename List<Object>::iterator List<Object>::erase(List<Object>::iterator itr) {
    Node *p = itr.current;
    iterator retVal{p->next};
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    theSize--;
    return retVal;
}


template<typename Object>
typename List<Object>::iterator List<Object>::erase(List<Object>::iterator from, List<Object>::iterator to) {
    for (iterator itr = from; itr != to;) {
        itr = erase(itr);
    }
    return to;
}


template<typename Object>
List<Object>::~List() {
    clear();
    delete head;
    delete tail;
}

/**
 * 拷贝构造函数
 * @tparam Object
 * @param rhs
 */
template<typename Object>
List<Object>::List(const List &rhs) {
    std::cout << "拷贝构造函数" << std::endl;

    init();

    // 这里的List是如何支持for循环的
    for (auto &x : rhs) {
        push_back(x);
    }
}

template<typename Object>
List<Object> &List<Object>::operator=(const List &rhs) {
    std::cout << "拷贝赋值运算符函数" << std::endl;

    List copy = rhs;
    std::swap(this, copy);
    return *this;
}

template<typename Object>
List<Object>::List(List &&rhs) noexcept
        :theSize(rhs.theSize), head(rhs.head), tail(rhs.tail) {
    std::cout << "移动构造函数" << std::endl;

    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

template<typename Object>
List<Object> &List<Object>::operator=(List &&rhs) noexcept {
    std::cout << "移动赋值运算符函数" << std::endl;

    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    return *this;
}

template<typename Object>
std::ostream &operator<<(std::ostream &out, const List<Object> &rhs) {
    std::cout << "包含" << rhs.size() << "个元素" << std::endl;
    for (auto itr = rhs.begin(); itr != rhs.end(); ++itr) {
        std::cout << *itr << " ";
    }
    std::cout << std::endl;
}

#endif //LIST_LIST_H
