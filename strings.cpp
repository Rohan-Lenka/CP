#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD1 = 1e9 + 7, MOD2 = 1e9 + 9;
const int BASE = 131;

struct PalindromeChecker {
    int n;
    vector<ll> hash1, hash2, rev_hash1, rev_hash2, pow1, pow2;

    PalindromeChecker(const string &s) {
        n = s.size();
        hash1.resize(n + 1);
        hash2.resize(n + 1);
        rev_hash1.resize(n + 1);
        rev_hash2.resize(n + 1);
        pow1.resize(n + 1, 1);
        pow2.resize(n + 1, 1);

        string rev_s = s;
        reverse(rev_s.begin(), rev_s.end());

        for (int i = 1; i <= n; i++) {
            hash1[i] = (hash1[i - 1] * BASE + s[i - 1]) % MOD1;
            hash2[i] = (hash2[i - 1] * BASE + s[i - 1]) % MOD2;

            rev_hash1[i] = (rev_hash1[i - 1] * BASE + rev_s[i - 1]) % MOD1;
            rev_hash2[i] = (rev_hash2[i - 1] * BASE + rev_s[i - 1]) % MOD2;

            pow1[i] = (pow1[i - 1] * BASE) % MOD1;
            pow2[i] = (pow2[i - 1] * BASE) % MOD2;
        }
    }

    pair<ll, ll> getHash(const vector<ll> &h1, const vector<ll> &h2,
                         const vector<ll> &p1, const vector<ll> &p2,
                         int l, int r) {
        ll hash_val1 = (h1[r + 1] - h1[l] * p1[r - l + 1] % MOD1 + MOD1) % MOD1;
        ll hash_val2 = (h2[r + 1] - h2[l] * p2[r - l + 1] % MOD2 + MOD2) % MOD2;
        return {hash_val1, hash_val2};
    }

    bool isPalindrome(int l, int r) {
        int rev_l = n - 1 - r;
        int rev_r = n - 1 - l;
        auto fwd = getHash(hash1, hash2, pow1, pow2, l, r);
        auto rev = getHash(rev_hash1, rev_hash2, pow1, pow2, rev_l, rev_r);
        return fwd == rev;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s = "abacaba";
    PalindromeChecker pc(s);
    
    cout << pc.isPalindrome(1, 5) << "\n";  // O(1) TC
    return 0;
}