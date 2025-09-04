#include <bits/stdc++.h>
using namespace std;

class SparseTable {
private:
    int n;
    int maxLog; 
    vector<vector<int>> a;

    // older -> 
    // static const int MAXN = 100001;
    // static const int MAX_LOG = 17; // Since log2(1e5) ≈ 16.6
    // int n;
    // int a[MAXN][MAX_LOG];

public:
    int inline operation(int n1, int n2) {
        return ;// perform your operation here
    }

    void build(vector<int> &nums) {
        n = nums.size();
        maxLog = 32 - __builtin_clz(n);           
        a.assign(n, vector<int>(maxLog));         

        // pre-processing for power == 0 -> 
        for(int i = 0; i < n; i++) {
            a[i][0] = nums[i];
        }
        // rest pre-processing -> 
        for(int power = 1; power < maxLog; power++) {    
            for(int i = 0; i + (1 << power) <= n; i++) {  // <-- safer loop condition
                a[i][power] = operation(a[i][power - 1],
                                        a[i + (1 << (power - 1))][power - 1]);
            }
        }
    }

    int query(int l, int r) {
        int len = r - l + 1;
        int log2len = 31 - __builtin_clz(len);
        return operation(a[l][log2len],
                         a[r - (1 << log2len) + 1][log2len]);
    }

};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // NOTES -> 
    // sparse tables are used for finding range queries for those operations which are_
    // 1) idempotent - An operation f(x, x) = x is called idempotent.
    // It means applying it multiple times doesn't change the result after the first time.
    // 2) associative 
    // sparse tables are used for operations like_ min, max, gcd, AND, OR

    // pros ->
    // answers range queries in O(1) TC (which is better than segment trees)

    // cons ->
    // takes more SC
    // operation must be idempotent (sparse tables cant be applied for sum, product, etc)
    // no update possible 
    return 0;
}