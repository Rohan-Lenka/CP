#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// 1) String & vector hashing 
/***
 *
 * 64-bit hashing for vectors or strings
 * Get the forward and reverse hash of any segment
 * Base is chosen randomly to prevent anti-hash cases from being constructed
 * * Complexity - O(n) to build, O(1) for each hash query
 *
***/
#define MAXLEN 1000010
constexpr uint64_t mod = (1ULL << 61) - 1;
const uint64_t seed = chrono::system_clock::now().time_since_epoch().count();
const uint64_t base = mt19937_64(seed)() % (mod / 3) + (mod / 3);

uint64_t base_pow[MAXLEN];

int64_t modmul(uint64_t a, uint64_t b) {
    uint64_t l1 = (uint32_t)a, h1 = a >> 32, l2 = (uint32_t)b, h2 = b >> 32;
    uint64_t l = l1 * l2, m = l1 * h2 + l2 * h1, h = h1 * h2;
    uint64_t ret = (l & mod) + (l >> 61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
    ret = (ret & mod) + (ret >> 61);
    ret = (ret & mod) + (ret >> 61);
    return ret - 1;
}

void init() {
    base_pow[0] = 1;
    for (int i = 1; i < MAXLEN; i++){
        base_pow[i] = modmul(base_pow[i - 1], base);
    }
}

class PolyHash {
private:
    int n;
    // Remove suff vector and usage if reverse hash is not required for more speed
    vector<int64_t> pref, suff;

public:
    PolyHash() {}

    template <typename T>
    PolyHash(const vector<T>& ar) {
        if(!base_pow[0]) init();

        n = ar.size();
        assert(n < MAXLEN);
        pref.resize(n + 3, 0), suff.resize(n + 3, 0);

        for(int i = 1; i <= n; i++) {
            pref[i] = modmul(pref[i - 1], base) + ar[i - 1] + 997;
            if (pref[i] >= mod) pref[i] -= mod;
        }

        for(int i = n; i >= 1; i--) {
            suff[i] = modmul(suff[i + 1], base) + ar[i - 1] + 997;
            if (suff[i] >= mod) suff[i] -= mod;
        }
    }

    PolyHash(const char* str)
        : PolyHash(vector<char> (str, str + strlen(str))) {}
    
    PolyHash(const string& s) 
        : PolyHash(vector<char>(s.begin(), s.end())) {}

    // functions
    uint64_t get_hash(int l, int r) {
        int64_t h = pref[r + 1] - modmul(base_pow[r - l + 1], pref[l]);
        return h < 0 ? h + mod : h;
    }

    uint64_t rev_hash(int l, int r) {
        int64_t h = suff[l + 1] - modmul(base_pow[r - l + 1], suff[r + 2]);
        return h < 0 ? h + mod : h;
    }

    bool isPrefixSuffix(int len) {
        if(len <= 0 || len > n) return false;
        return get_hash(0, len - 1) == get_hash(n - len, n - 1);
    }

    bool isPalindrome(int l, int r) {
        return get_hash(l, r) == rev_hash(l, r);
    }

    // calc the len of the longest palindromic substr / subarr 
    // within the range [left, right]
    int longestPalindromicSub(int left, int right) {
        int len = right - left + 1; 
        if(len <= 0) return 0;     

        auto chck = [&](int mid) {
            int l = left;
            int r = left + mid - 1;
            while(r <= right) {
                if(isPalindrome(l, r)) return true;
                l++; r++;
            }
            return false;
        };
        
        int max_len = 1;

        // BS for maximum ODD length
        int lo = 1, hi = (len % 2 == 0) ? len - 1 : len; 
        while(lo <= hi) {
            int mid = (lo + hi) >> 1;
            if(mid % 2 == 0) mid++; 
            if(mid > hi) break;
            if(chck(mid)) {
                max_len = max(max_len, mid);
                lo = mid + 2; 
            } else {
                hi = mid - 2; 
            }
        }

        // BS for maximum EVEN length
        lo = 2, hi = (len % 2 == 0) ? len : len - 1;
        while(lo <= hi) {
            int mid = (lo + hi) >> 1;
            if(mid % 2 != 0) mid++;
            if(mid > hi) break;
            if(chck(mid)) {
                max_len = max(max_len, mid);
                lo = mid + 2; 
            } else {
                hi = mid - 2; 
            }
        }
        
        return max_len;
    }

    // Gets the Longest Common Prefix of substrings starting at l1 and l2.
    // max_len caps the binary search (defaults to the end of the string).
    int getLcp(int l1, int l2, int max_len = -1) {
        if(max_len == -1) max_len = n - max(l1, l2);
        int l = 1, r = max_len, ans = 0;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(get_hash(l1, l1 + mid - 1) == get_hash(l2, l2 + mid - 1)) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }

    // Lexicographically compares s[l1..r1] and s[l2..r2].
    // Returns -1 if sub1 < sub2, 0 if equal, 1 if sub1 > sub2.
    template <typename Container>
    int compare(int l1, int r1, int l2, int r2, const Container& s) {
        int len1 = r1 - l1 + 1;
        int len2 = r2 - l2 + 1;
        int min_len = min(len1, len2);
        int lcp = getLcp(l1, l2, min_len);
        if(lcp == min_len) {
            if(len1 == len2) return 0;
            return len1 < len2 ? -1 : 1;
        }
        return s[l1 + lcp] < s[l2 + lcp] ? -1 : 1;
    }

};

// 2) Pattern Matching (in a range [l....r])
bool match(string &s, string &pattern, PolyHash &ph_s, PolyHash &ph_pattern, int l, int r) {
    int m = pattern.length();
    int range_len = r - l + 1;
    if(l < 0 || r >= s.length() || l > r || m > range_len || m == 0) {
        return false;
    }
    uint64_t target_hash = ph_pattern.get_hash(0, m - 1);
    for(int i = l; i <= r - m + 1; i++) {
        if(ph_s.get_hash(i, i + m - 1) == target_hash) {
            return true; 
        }
    }
    return false; 
}
// TC of each query = O((r - l + 1) + (1 - m)) = O(len of range - size of pattern)

// Todo -> manacher's algo for longest palindromic substring of whole string 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // for strings
    string s = "babbcabcbab";
    PolyHash h1 = PolyHash(s);
    auto hash1 = h1.get_hash(2, 6);
    cout << hash1 << " " << h1.isPalindrome(5, 9) << '\n';

    // for vectors
    vector<int> v = {1, 2, 4, 5, 5, 4, 2, 10};
    PolyHash h2 = PolyHash(v);
    auto hash2 = h2.get_hash(0, 4);
    cout << h2.isPalindrome(1, 6) << '\n';

    return 0;
}