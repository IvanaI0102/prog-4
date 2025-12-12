#include <bits/stdc++.h> 
using namespace std;

string process_word(const string& word) {
    string processed;
    for (char ch : word) {
        if (isalpha(ch)) {
            processed += tolower(ch);
        }
    }
    return processed;
}

struct TNode {
    string key; 
    bool end;
    vector<TNode*> children;

    TNode(const string& k = "") 
        : key(k), end(false), children(26, nullptr) {}

    ~TNode() {
        for (TNode* child : children) {
            delete child;
        }
    }
};

class Trie {
private:
    TNode* root;

    int get_index(char ch) const {
        return ch - 'a';
    }

    int common_prefix_length(const string& s1, const string& s2) const {
        int i = 0;
        while (i < s1.length() && i < s2.length() && s1[i] == s2[i]) {
            i++;
        }
        return i;
    }

public:
    Trie() {
        root = new TNode();
    }

    ~Trie() {
        delete root; 
    }

    void insert(const string& word) {
        string processed_word = process_word(word);
        if (processed_word.empty()) return;

        TNode* current = root;
        string suffix = processed_word;

        while (!suffix.empty()) {
            int index = get_index(suffix[0]);
            TNode* next_node = current->children[index];

            if (next_node == nullptr) {
                current->children[index] = new TNode(suffix);
                current->children[index]->end = true;
                return;
            }

            int prefix_len = common_prefix_length(suffix, next_node->key);

            if (prefix_len == next_node->key.length()) {
                suffix = suffix.substr(prefix_len);
                current = next_node;
            } else {
                string common_prefix = next_node->key.substr(0, prefix_len);
                TNode* split_node = new TNode(common_prefix);
                
                string old_node_suffix = next_node->key.substr(prefix_len);
                int old_node_index = get_index(old_node_suffix[0]);
                next_node->key = old_node_suffix;
                split_node->children[old_node_index] = next_node;
                
                string new_node_suffix = suffix.substr(prefix_len);
                
                if (new_node_suffix.empty()) {
                    split_node->end = true;
                } else {
                    int new_node_index = get_index(new_node_suffix[0]);
                    TNode* new_node = new TNode(new_node_suffix);
                    new_node->end = true;
                    split_node->children[new_node_index] = new_node;
                }

                current->children[index] = split_node;
                return;
            }
        }

        current->end = true;
    }

    
    bool search(const string& word) const {
        string processed_word = process_word(word);
        if (processed_word.empty()) return false;

        TNode* current = root;
        string suffix = processed_word;

        while (!suffix.empty()) {
            int index = get_index(suffix[0]);
            TNode* next_node = current->children[index];

            if (next_node == nullptr) {
                return false;
            }

            int prefix_len = common_prefix_length(suffix, next_node->key);

            if (prefix_len < suffix.length() && prefix_len < next_node->key.length()) {
                return false;
            }

            if (prefix_len == next_node->key.length()) {
                suffix = suffix.substr(prefix_len);
                current = next_node;
            } else if (prefix_len == suffix.length()) {
                return true; 
            } else {
                 return false;
            }
        }
        
        return current->end;
    }
};


int main() {
    Trie trie;
    ifstream file("words_eng.txt");
    int count = 0;

    if (!file.is_open()) {
        cout << "Error." << endl;
        
         
    } else {
        string word;
        
        
        while (getline(file, word)) {
            trie.insert(word);
            count++;
        }
        file.close();

        
    }

    cout << count << endl;
    cout << trie.search("in") << endl;
    cout << trie.search("insert") << endl;
    cout << trie.search("robot") << endl;
    cout << trie.search("apple") << endl;
    cout << trie.search("xyz") << endl;
    cout << trie.search("TRIE") << endl;

    return 0;
}