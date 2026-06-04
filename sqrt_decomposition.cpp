#include <bits/stdc++.h>
using namespace std;

// 1) Standard sqrt decomposition (dividing into √n blocks + lazy propagation)
 
/*
    // IMP things to remember ->
    i) blockSize = ceil(sqrt(double(n))) 
        Although both floor and ceil are fine, always use ceil
    ii) block_id of any index -> bid = i / blockSize
    iii) Starting index for any block -> bid * blockSize
    iv) Ending index for any block -> ((bid + 1) * blockSize) - 1
*/ 

// Pseudo Code -> 
/*
    // NOTE -> A, Q shld be 0 indexed
    // Q contains 2 types of queries, upd and find_ans type queries 
    solve(int A[n], int Q[m]) {

        // 1) prepare the sqrt blocks and lazy
        int blockSize = ceil(sqrt(double(n)))
        blocks[blockSize] = {}
        lazy[blockSize] = {initial_values} // most of the cases it is 0
        
        // 2) compute values for each block
        for(i = 0 to n - 1) {
            int bid = i / blockSize
            blocks[bid] = compute(blocks[bid], a[i])
        } 

        // 3) Answer the queries
        ans[] = {}
        for(auto &q : Q) {

            // Each query must contain several things -> type of query, l, r (i.e the ranges) 
            // and some extra things required for update
            
            // case1 -> upd query
            int l_bid = l / blockSize, r_bid = r / blockSize
            if(l_bid == r_bid) {
                // both lie on same block, so no need for lazy
                // hence do actual updates on both blocks and array via brute force 
                for(i = l to r) {
                    update(a[i])
                    update(blocks[l_bid])
                }
            } 
            else {
                // for partial updates, do brute force. For blocks, use lazy instead
                
                // partial upd from l to end_of(l_bid)
                for(i = l to ((l_bid + 1) * blockSize) - 1) {
                    update(a[i])
                    update(blocks[l_bid])
                }

                // partial upd from r to start_of(r_bid)
                for(i = r to r_bid * blockSize) {  // decreasing loop
                    update(a[i])
                    update(blocks[r_bid])
                }

                // update for rest of the blocks
                for(bid = l_bid + 1 to r_bid - 1) {
                    update(lazy[bid])
                } 

            }
            
            // case2 -> find_ans query
            // ans for a certain range [l, r] shld be found in a similar way too
            // 3 loops in total, 1st 2 for partial ans and last one to traverse via blocks
            // [IMP] -> While finding ans, take in the consideration of the lazy 
            //       -> To find the comtribution of each block for the ans, 
            //          computation shld be in O(1) or O(logn) (in very rare cases) 

        }
        
        return ans
    }
*/

// 2) MO's algo

// In many MO's algo qs, hashmap is used 
#define MAXN 1000001
int mp[MAXN];
class MO {
public:
    int blockSize, ans;

    void insert(int x) {
        // write logic here, upd ans for every insert fx call  
    }

    void erase(int x) {
        // write logic here, upd ans for every erase fx call  
    }

    vector<int> solve(vector<int> &A, vector<vector<int>> &_Q) {
        // Initialise the ans var
        ans = 0;
        int n = A.size(), n_Q = _Q.size();
        vector<tuple<int, int, int>> Q(n_Q);
        for(int i = 0; i < _Q.size(); i++) 
            Q[i] = {_Q[i][0], _Q[i][1], i}; 
        blockSize = ceil(sqrt((double)n));
        sort(Q.begin(), Q.end(), [&](auto &t1, auto &t2) {
            auto &[l1, r1, i1] = t1;
            auto &[l2, r2, i2] = t2;
            int bid1 = l1 / blockSize, bid2 = l2 / blockSize;
            if(bid1 == bid2) return r1 < r2;
            return bid1 < bid2;
        }); 
        int l = 0, r = -1;
        vector<int> res(n_Q);
            for(auto &[li, ri, idx] : Q) {
            while(l < li) erase(A[l++]);
            while(l > li) insert(A[--l]);
            while(r < ri) insert(A[++r]);
            while(r > ri) erase(A[r--]);
            res[idx] = ans;
        }
        return res;
    }
};
// TC1 = O(n√n + q√n + qlogq) If insert & erase fx are O(1)
// TC2 = O((n√n + q√n)*logn + qlogq) If insert & erase fx are O(logn)

// Constraints for TC1 -> n, q <= 2 * 1e5 (1.8 x 1e8 operations) 
// Constraints for TC2 -> n, q <= 3 * 1e4 (1.5 x 1e8 operations) 
// Hence only use expensive code for insert & erase fx (i.e taking logn TC)
// iff n, q <= 3 * 1e4 

// Same constraints can be applied for sqrt decomposition + lazy as well

int main() {
    
    return 0;
}