#include <bits/stdc++.h>
using namespace std;

// for range sum query and point updates
class FenwickTree {
public:
    vector<int> bit;
    int n;
    FenwickTree(int len) {  // len is input array size
        n = len + 1;
        bit.resize(n);
    }
    int query(int id) {
        int ans = 0;
        while(id > 0) {
            ans += bit[id];
            id -= (id & -id);
        }
        return ans;
    }
    void update(int id, int val) { // val means inc or dec from prev value 
        while(id < n) {
            bit[id] += val;
            id += (id & -id);
        }   
    }
    void build(vector<int> &nums) {
        for(int ind = 0; ind < nums.size(); ind++) {
            update(ind + 1, nums[ind]);
        }
    }
    int rangeQuery(int l, int r) {
        return query(r + 1) - query(l);
    }
};

int main() {
    
    return 0;
}