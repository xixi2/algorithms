#include <iostream>
#include <string>
#include <vector>
#include "Trie.h"

using namespace std;

int main() {

    vector<string> vs{
            "acb", "abc", "adf", "abcd", "dbga", "addgd", "good", "no"
    };
    vector<string> words{"baidu", "no", "qq"};
    Trie t;
    for (int i = 0; i < vs.size(); ++i) {
        t.insert(vs[i]);
    }

    for (int i = 0; i < words.size(); ++i) {
        cout << (t.search(words[i]) ? "exists" : "not exist") << endl;
    }
    t.deleteTrieNode("no");
    cout << (t.search("no") ? "exists" : "not exist") << endl;

    return 0;
}