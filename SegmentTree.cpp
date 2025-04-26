#include <bits/stdc++.h>
using namespace std;

// without lazy propagation, for range sum query
class SegTree {
public:
    int len;
	vector<int> t;
	
	SegTree(int l){
		len = l;
		t.resize(4 * len);
	}

    // Build Segment Tree -- build(a, 1, 0, len-1); 
    void build(vector<int>& a, int v, int tl, int tr){
		if(tl == tr){
			t[v] = a[tl];
			return;
		}
		int tm = (tl + tr)/2; // can do tm = (tl + tr) >> 1; for bit faster
		build(a, 2*v, tl, tm);
		build(a, 2*v+1, tm+1, tr);
		t[v] = t[2*v] + t[2*v+1];
	}

    // range query 
    // Query input question is = [l, r] included -- query(1, 0, len-1, l, r)
    int query(int v, int tl, int tr, int l, int r){
        if(tl > r || tr < l) return 0;  // no overlap
		if(l <= tl && tr <= r) return t[v]; // Full overlap
		// Partial Overlap
		int tm = (tl + tr)/2;
		int leftAns = query(2*v, tl, tm, l, r);
		int rightAns = query(2*v+1, tm+1, tr, l, r);
		return leftAns + rightAns;
	}
    
    // point update 
    // Update at index id of nums to a value val (assign/override/set) -- update(1, 0, len-1, id, val) 
	void update(int v, int tl, int tr, int id, int val){
		// reached leaf node
		if(tl == id && tr == id){
			t[v] = val;
			return;
		}
		if(id > tr || id < tl) return;
		
		int tm = (tl + tr)/2;  
		update(2*v, tl, tm, id, val);
		update(2*v+1, tm+1, tr, id, val);
		t[v] = t[2*v] + t[2*v+1];
	}

    //over-ridden functions
	void build(vector<int>& a){
		build(a, 1, 0, len-1);
	}
	
	int query(int l, int r){
		return query(1, 0, len-1, l, r);
	}
	
	void update(int id, int val){
		update(1, 0, len-1, id, val);
	}
};

// with lazy propagation, for range sum query and range update
class Segtree {
    public:
    int len;
	vector<int> t, lazy;
	
	Segtree(int l){
		len = l;
		t.resize(4 * len);
		lazy.resize(4 * len);
	}

    // Build Segment Tree -- build(a, 1, 0, len-1); 
    void build(vector<int>& a, int v, int tl, int tr){
		if(tl == tr){
			t[v] = a[tl];
			return;
		}
		int tm = (tl + tr)/2; // can do tm = (tl + tr) >> 1; for bit faster
		build(a, 2*v, tl, tm);
		build(a, 2*v+1, tm+1, tr);
		t[v] = t[2*v] + t[2*v+1];
	}

    // range query 
    // Query input question is = [l, r] included -- query(1, 0, len-1, l, r)
    int query(int v, int tl, int tr, int l, int r){

        if(lazy[v] != 0) {
            int pending = lazy[v];
            lazy[v] = 0;
            t[v] += (tr - tl + 1) * pending;
            if(tl != tr) {  // not a leaf node
                lazy[2 * v] += pending;
                lazy[2 * v + 1] += pending;
            }
        }

        if(tl > r || tr < l) return 0;  // no overlap
		if(l <= tl && tr <= r) return t[v]; // Full overlap
		// Partial Overlap
		int tm = (tl + tr)/2;
		int leftAns = query(2*v, tl, tm, l, r);
		int rightAns = query(2*v+1, tm+1, tr, l, r);
		return leftAns + rightAns;
	}
    
    // range update 
    // update from a range l to r with a inc or dec with val 
    void update(int v, int tl, int tr, int l, int r, int val) {
        if(lazy[v] != 0) {
            int pending = lazy[v];
            lazy[v] = 0;
            t[v] += (tr - tl + 1) * pending;
            if(tl != tr) {  // not a leaf node
                lazy[2 * v] += pending;
                lazy[2 * v + 1] += pending;
            }
        }
    
        if(l > tr || r < tl) return;  // No overlap
        if(l <= tl && tr <= r) {      // Full overlap
            t[v] += (tr - tl + 1) * val;
            if(tl != tr) {  // not a leaf node
                lazy[2 * v] += val;
                lazy[2 * v + 1] += val;
            }
            return;
        }
    
        // Partial overlap
        int tm = (tl + tr) / 2;
        update(2 * v, tl, tm, l, r, val);
        update(2 * v + 1, tm + 1, tr, l, r, val);
        t[v] = t[2 * v] + t[2 * v + 1];
    }
    

    //over-ridden functions
	void build(vector<int>& a){
		build(a, 1, 0, len-1);
	}
	
	int query(int l, int r){
		return query(1, 0, len-1, l, r);
	}
	
	void update(int l, int r, int val){
		update(1, 0, len-1, l, r, val);
	}
};

int main() {
    
    return 0;
}