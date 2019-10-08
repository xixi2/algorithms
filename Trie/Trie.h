//
// Created by xixi2 on 19-7-12.
//

#ifndef TRIE_TRIE_H
#define TRIE_TRIE_H

#include <string>
#include <cstring>
#include <iostream>

const int size = 26;


class TrieNode {
public:
    int path;   //有多少个单词共用这个节点
    int end;    // 有多少个单词以这个节点结尾

    // map是一个哈希表，key表示该节点的一条字符路径，value表示字符路径指向的节点
    TrieNode *child[26];  // 这里map是一个指向TrieNode类型的指针

    // 如何创建一个TrieNode类型的数组，且这个数组中数据元素的类型为TrieNode类型
    TrieNode() : path(0), end(0) {
        memset(child, 0, sizeof(child));
    }
};

class Trie {
private:
    TrieNode *root; // 根节点
public:
    Trie() : root(new TrieNode()) {}

    /**
     * 从左到右遍历word中的每个字符，并依次从头结点开始根据每一个word[i]找到下一个节点,
     * 如果找的过程中节点不存在，就建立新节点，记为a，并令a.path=1.如果节点存在，记为b，令b.path++
     * 通过最后一个字符，找到最后一个节点时记为e，令e.path++,e.end++
     * @param word
     */
    void insert(std::string word) {
        if (word.empty()) {
            return;
        }
        TrieNode *node = root;
        ++node->path;
        for (int i = 0; i < word.size(); ++i) {
            int index = word[i] - 'a';
            if (node->child[index] == nullptr) {
                node->child[index] = new TrieNode();
            }
            node = node->child[index];
            node->path++;
        }
        node->end++;
    }


    bool search(std::string word) {
        if (word.empty()) {
            return false;
        }
        TrieNode *node = root;
        int index = 0;
        for (int i = 0; i < word.size(); ++i) {
            index = word[i] - 'a';
            if (node->child[index] == nullptr) {
                return false;
            }
            node = node->child[index];
        }
        //例如输入过abcd，但是abc却不存在
        return node->end != 0;
    }

    /**
     * 先调用search，查看word是否在Trie树中，若在，继续执行后面的过程，否则直接返回．
     * 从左到右遍历word中的每个字符，并依次从头结点开始根据每一个word[i]找到下一个节点．
     * 在找的过程中，把遍历过每一个节点的path减去１．如果发现下一个节点的path值减完之后已经为0,直接从当前节点的map中删除后续的所有路径，并返回即可
     * 如果遍历到最后一个节点，记为e，令e.path--,e.end--
     * 这里需要考虑内存回收与释放
     * @param word
     */
    void deleteTrieNode(std::string word) {
        if (!search(word)) {
            return;
        }
        TrieNode *&node = root;
        for (int i = 0; i < word.size(); ++i) {
            int index = word[i] - 'a';
            if (node->child[index]->path-- == 1) {
                TrieNode *tmp = node->child[index]; // 令tmp接管node->child[index]的内存
                node->child[index] = nullptr;       // 将node->child[index]置为nullptr

                // 删除某个字符串的时候，会不会造成内存泄露呢？
                if (i < word.size() - 1) {      // 若当前节点不是最后一个节点
                    int nextIndex = word[i + 1] - 'a';
                    TrieNode *next = tmp->child[nextIndex];
                    int j = i + 2;
                    while (next != nullptr) {
                        delete tmp;

                        tmp = next;
                        nextIndex = word[j++] - 'a';
                        next = tmp->child[nextIndex];
                    }
                    delete tmp;
                    tmp = nullptr;
                    next = nullptr;
                } else {
                    delete tmp;
                    tmp = nullptr;
                }
                return;
            }
            node = node->child[index];
            --node->end;
        }
    }


    /**
     * 返回字典树中以字符串pre为前缀的字符串个数
     * 和查找操作同理，根据pre不断找到节点，假设最后的节点记为e，返回e.path
     * @param pre
     * @return
     */
    int prefixNumber(std::string pre) {
        if (pre.empty()) {
            return 0;
        }
        TrieNode *node = root;
        int index = 0;
        for (int i = 0; i < pre.size(); ++i) {
            int index = pre[i] - 'a';
            if (node->child[index] == nullptr) {
                return 0;
            }
            node = node->child[index];
        }
        return node->path;
    }
};


#endif //TRIE_TRIE_H
