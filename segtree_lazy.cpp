#include <bits/stdc++.h>
using namespace std;

// 1) Segment tree with lazy propagation 
// 2 nodes are required -> node for main tree, node for lazy tree

struct Upd {
    long long delta; 
    bool is_empty;
    Upd() {
        delta = 0; // Write your identity/default update here
        is_empty = true;
    }
    Upd(long long val) {
        delta = val;
        is_empty = false;
    }
    void combine(const Upd &nu) {
        if (nu.is_empty) return;
        if (is_empty) {
            *this = nu;
            return;
        }
        // Define how multiple updates accumulate/combine on a single node
        // delta += nu.delta; // Example: Range Add
    }
};

struct Node {
    // declare all vars which u will need here
    long long val;
    Node(long long v = 0LL /* Write the identity value here */) {
        val = v;
    }
    static Node merge(const Node &a, const Node &b) {
        return Node(/* Do your operation here */);
    }
    void apply(const Upd &u, int tl, int tr) {
        if (u.is_empty) return;
        // Define how an update modifies this node
        // val += u.delta * (tr - tl + 1); // Example: Range Sum Update
    }
    // modify ur conversion operator
    operator long long() {
        return val;
    }
};

template<typename Node, typename Update>
class SGT {
private:
    int n;
    vector<Node> tree;
    vector<Update> lazy;

    Node merge(const Node& a, const Node& b) {
        return Node::merge(a, b);
    }

    void push(int v, int tl, int tr) {
        if (!lazy[v].is_empty) {
            tree[v].apply(lazy[v], tl, tr); 
            
            if (tl != tr) {
                lazy[v << 1].combine(lazy[v]);     
                lazy[v << 1 | 1].combine(lazy[v]); 
            }
            lazy[v] = Update(); 
        }
    }

    void build(int v, int tl, int tr, const vector<Node>& arr) {
        if (tl == tr) {
            tree[v] = arr[tl];
            return;
        }

        int tm = (tl + tr) >> 1;
        build(v << 1, tl, tm, arr);
        build(v << 1 | 1, tm + 1, tr, arr);

        tree[v] = merge(tree[v << 1], tree[v << 1 | 1]);
    }

    void update(int v, int tl, int tr, int l, int r, const Update& up) {
        push(v, tl, tr); 
        
        if (tl > r || tr < l)
            return;

        if (l <= tl && tr <= r) {
            lazy[v].combine(up); 
            push(v, tl, tr);     
            return;
        }

        int tm = (tl + tr) >> 1;
        update(v << 1, tl, tm, l, r, up);
        update(v << 1 | 1, tm + 1, tr, l, r, up);

        tree[v] = merge(tree[v << 1], tree[v << 1 | 1]);
    }

    Node query(int v, int tl, int tr, int l, int r) {
        push(v, tl, tr); 
        
        if (tl > r || tr < l)
            return Node(); 

        if (l <= tl && tr <= r)
            return tree[v];

        int tm = (tl + tr) >> 1;

        return merge(
            query(v << 1, tl, tm, l, r),
            query(v << 1 | 1, tm + 1, tr, l, r)
        );
    }

public:
    SGT(int n) : n(n) {
        tree.assign(4 * n + 5, Node());
        lazy.assign(4 * n + 5, Update());
    }

    SGT(const vector<Node>& arr) {
        n = arr.size();
        tree.assign(4 * n + 5, Node());
        lazy.assign(4 * n + 5, Update());
        build(1, 0, n - 1, arr);
    }

    void update(int l, int r, const Update& up) {
        update(1, 0, n - 1, l, r, up);
    }

    Node query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

int main() {
    
    return 0;
}