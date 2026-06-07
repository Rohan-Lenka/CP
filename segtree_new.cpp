#include <bits/stdc++.h>
using namespace std;
#define ll long long 

// 1) without lazy propagation
// Make a Node for the Segtree
struct Node {
    // declare all vars which u will need here
    int val;
    Node(int v = 0 /* Write the identity value here */) {
        val = v;
    }
    static Node merge(const Node &a, const Node &b) {
        return Node(/* Do your operation here */);
    }
    // modify ur conversion operator
    operator int() const {
        return val;
    }
};
// Ex -> 
struct SumNode {
    ll val;
    SumNode(ll v = 0LL) : val(v) {}
    static SumNode merge(const SumNode &a, const SumNode &b) {
        return SumNode(a.val + b.val);
    }
    operator ll() const {
        return val;
    }
};
template<typename Node>
class Segtree {
private:
    int n;
    vector<Node> tree;

    Node merge(const Node& a, const Node& b) {
        return Node::merge(a, b);
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

    Node query(int v, int tl, int tr, int l, int r) {
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

    void update(int v, int tl, int tr, int pos, const Node& val) {
        if (tl == tr) {
            tree[v] = val;
            return;
        }

        int tm = (tl + tr) >> 1;

        if (pos <= tm)
            update(v << 1, tl, tm, pos, val);
        else
            update(v << 1 | 1, tm + 1, tr, pos, val);

        tree[v] = merge(tree[v << 1], tree[v << 1 | 1]);
    }

public:
    Segtree(int n) : n(n) {
        tree.assign(4 * n + 5, Node());
    }

    Segtree(const vector<Node>& arr) {
        n = arr.size();
        tree.assign(4 * n + 5, Node());
        build(1, 0, n - 1, arr);
    }

    Node query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    void update(int pos, const Node& val) {
        update(1, 0, n - 1, pos, val);
    }
};

int main() {
    // usage 
    vector<ll> a = {1, 2, 4, 100, 90};
    int n = a.size();
    
    vector<SumNode> ar;
    for(auto &e : a) ar.push_back(SumNode(e));
    
    Segtree<SumNode> st(ar); 
    
    cout << st.query(3, 4).val << '\n';
    
    st.update(2, SumNode(-100));
    
    cout << st.query(2, 4) << '\n';
    // this is also fine coz conversion operator is present
    return 0;
}