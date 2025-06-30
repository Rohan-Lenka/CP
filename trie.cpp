struct Node {
    Node* links[26];
    bool flag = false;
};

class Trie {
private: 
Node* root; 
public:
    Trie() {
        root = new Node();   
    }
    
    void insert(string word) {
        Node* node = root;
        for(char c : word) {
            if(node->links[c - 'a'] == NULL) {
                node->links[c - 'a'] = new Node();
            }
            node = node->links[c - 'a'];
        }
        node->flag = true;
    }
    
    bool search(string word) {
        Node* node = root;
        for(char c : word) {
            if(!node->links[c - 'a']) return false;
            node = node->links[c - 'a'];
        }
        return node->flag;
    }
    
    bool startsWith(string prefix) {
        Node* node = root;
        for(char c : prefix) {
            if(!node->links[c - 'a']) return false;
            node = node->links[c - 'a'];
        }
        return true;
    }
};