#include <bits/stdc++.h>
using namespace std;

// Basic Trie
namespace basic_trie {
    
    struct Node {
        Node* ch[26];
        bool fg = false;
        Node() {
            for(int i = 0; i < 26; i++) ch[i] = NULL;
        }
    };

    class Trie {
    private: 
        Node* root; 
    public:
        Trie() {
            root = new Node();   
        }
        
        void insert(string &word) {
            Node* node = root;
            for(char &c : word) {
                if(node->ch[c - 'a'] == NULL) {
                    node->ch[c - 'a'] = new Node();
                }
                node = node->ch[c - 'a'];
            }
            node->fg = true;
        }

        bool search(string &word) {
            Node* node = root;
            for(char &c : word) {
                if(!node->ch[c - 'a']) return false;
                node = node->ch[c - 'a'];
            }
            return node->fg;
        }

        bool startsWith(string &prefix) {
            Node* node = root;
            for(char &c : prefix) {
                if(!node->ch[c - 'a']) return false;
                node = node->ch[c - 'a'];
            }
            return true;
        }
    };

}


// Counting Trie 
struct Node {
    Node* ch[26];
    int cp = 0, freq = 0;
    Node() {
        for(int i = 0; i < 26; i++) ch[i] = NULL;
    }
};

class Trie {
private:
    Node* root;
public:
    Trie() {
        root = new Node();
    }

    void insert(string &word) {
        Node* node = root;
        for(auto &c : word) {
            if(!node->ch[c - 'a']) node->ch[c - 'a'] = new Node();
            node = node->ch[c - 'a'];
            node->cp++;
        }
        node->freq++;
    }
    
    bool erase(string &word) {
        if(countWords(word) == 0) return false;
        Node* node = root;
        for(auto &c : word) {
            node = node->ch[c - 'a'];
            node->cp--;
        }
        node->freq--;
        return true;
    }

    int countWords(string &word) {
        Node* node = root;
        for(auto &c : word) {
            if(!node->ch[c - 'a']) return 0;
            node = node->ch[c - 'a'];
        }
        return node->freq;
    }
    
    int countStartsWith(string &prefix) {
        Node* node = root;
        for(auto &c : prefix) {
            if(!node->ch[c - 'a']) return 0;
            node = node->ch[c - 'a'];
        }
        return node->cp;
    }

};
// worst case SC of above tries => O(26 * maxLenOfStr * numOfStrs)
// all functions take TC => O(lenOfWord)

namespace binary_trie {

    struct Node {
        Node* ch[2];
        int cnt;
        Node() {
            ch[0] = ch[1] = nullptr;
            cnt = 0;
        }
    };

    class Trie {
    private:
        Node* root;
        static const int LOG = 30;
    public:
        Trie() {
            root = new Node();
        }

        void insert(int num) {
            Node* node = root;
            for(int i = LOG; i >= 0; i--) {
                int b = (num >> i) & 1;
                if(!node->ch[b]) node->ch[b] = new Node();
                node = node->ch[b];
                node->cnt++;
            }
        }

        void erase(int num) {
            Node* node = root;
            for(int i = LOG; i >= 0; i--) {
                int b = (num >> i) & 1;
                Node* nxt = node->ch[b];
                if(!nxt) return;
                nxt->cnt--;
                node = nxt;
            }
        }

        int maxXor(int num) {
            Node* node = root;
            int res = 0;
            for(int i = LOG; i >= 0; i--) {
                int b = (num >> i) & 1;
                if(node->ch[1 - b] && node->ch[1 - b]->cnt > 0) {
                    res |= (1 << i);
                    node = node->ch[1 - b];
                } else {
                    node = node->ch[b];
                }
            }
            return res;
        }

        int minXor(int num) {
            Node* node = root;
            int res = 0;
            for(int i = LOG; i >= 0; i--) {
                int b = (num >> i) & 1;
                if(node->ch[b] && node->ch[b]->cnt > 0) {
                    node = node->ch[b];
                } else {
                    res |= (1 << i);
                    node = node->ch[1 - b];
                }
            }
            return res;
        }

        int countLess(int num, int K) {
            Node* node = root;
            int res = 0;

            for(int i = LOG; i >= 0; i--) {
                if(!node) break;

                int b = (num >> i) & 1;
                int k = (K >> i) & 1;

                if(k == 1) {
                    if(node->ch[b]) res += node->ch[b]->cnt;
                    node = node->ch[1 - b];
                } else {
                    node = node->ch[b];
                }
            }
            
            return res;
        }

        int countGreater(int num, int K) {
            Node* node = root;
            int res = 0;

            for(int i = LOG; i >= 0; i--) {
                if(!node) break;
                
                int b = (num >> i) & 1;
                int k = (K >> i) & 1;

                if(!k) {
                    if(node->ch[1 - b]) res += node->ch[1 - b]->cnt;
                    node = node->ch[b];
                } else {
                    node = node->ch[1 - b];
                }
            }
            
            return res;
        }

    };

}

int main() {
    
    return 0;
}