#include <bits/stdc++.h>
using namespace std;


struct TNode {
    bool end;
    vector<TNode*> children;

    TNode() : end(false), children(26, nullptr) {}

   
    ~TNode() {
        for (TNode* child : children) {
            delete child;
        }
    }
};



 
class Trie {
private:
    TNode* root;

public:
    Trie() {
        root = new TNode();
    }

    ~Trie() {
        delete root;
    }

    void insert(const string& word) {
        TNode* current = root;

        for(char ch : word) {
            if (!isalpha(ch)) {
                continue;
            }

            ch = tolower(ch);
            int index = ch - 'a';

            if (current->children[index] == nullptr) {
                current->children[index] = new TNode();
            }

            current = current->children[index];
        }

        current->end = true;
    }

    bool search(const string& word) const {
        TNode* current = root;

        for(char ch : word) {
            if (!isalpha(ch)) {
                continue;
            }

            ch = tolower(ch);
            int index = ch - 'a';

            if (current->children[index] == nullptr)
                return false;

            current = current->children[index];
        }
        return current->end;
    }
};


int main() {
    Trie trie;
    ifstream file("words_eng.txt");

    if (!file.is_open()) {
        cout << "Error" << endl;
        return 1;
    }

    string word;
    int count = 0;

    while (getline(file, word)) {
        trie.insert(word);
        count++;
    }

    file.close();

    cout << count << endl;

    cout << trie.search("banana") << endl;
    cout << trie.search("robot") << endl;
    cout << trie.search("apple") << endl;
    cout << trie.search("xyz") << endl;

    return 0;
}