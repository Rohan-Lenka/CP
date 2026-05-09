#include <bits/stdc++.h>
using namespace std;
#define ll long long

// 1) Modulo and subtraction
/*
    Always do this when you are performing modulo and also doing subtraction
    example -> 
    ll a = myPow(n, k1, MOD); ll b = myPow(n, k2, MOD);
    if u are doing ll c = (a - b) % MOD; then this can be wrong when a < b, i.e negative ans
    as by doing % MOD gives u remainder, ll a can be a lower remainder while ll b be a higher one
    so to avoid this always do -> 
    ll c = (a - b + MOD) % MOD    
*/

// 2) FERMAT'S LITTLE THEORM FOR CP -> 
/*
    (a / b) % MOD != (a % MOD / b % MOD) coz division itself is invalid in modular arithmatic 
    here we have to do -> (a * modInverseOfB) % MOD 
    where modInverseOfB = binary_exponentiation(b, MOD - 2, MOD)
    therefore -> (a / b) % MOD = ((a % MOD) * binary_exponentiation(b, MOD - 2, MOD)) % MOD
    This is used in many CP problems involving number theory, maths, combinatorics, etc
    NOTE -> MOD must always be a PRIME NUMBER for this to work like MOD = 1e9 + 7, 998244353, etc 
*/

// 3) Legendre's Formula
/*
    finds the highest power of a prime that divides n! 
    formula -> highest_power(n, p) = (n/p) + (n/p^2) + (n/p^3) + ......
    explanation -> https://codeforces.com/topic/122957/en1
*/
long long legendre(long long n, long long p) {
    long long cnt = 0;
    while(n > 0) {
        cnt += n / p;
        n /= p;
    }
    return cnt;
}

// 4) Bertrand's postulate
/*
    For each positive integer x there is a prime p, inside the interval [x,2x]
*/

// 5) Euclidean algorithm 
int findGCD(int a, int b) {
    while(a > 0 && b > 0) {
        if(a > b) a = a % b;
        else b = b % a;
    }
    if(!a) return b;
    return a;
    // TC = O(log(min(a, b)))
    // SC = O(1)
}

// 6) Bezout identity
/*
    for three known integers -> a, b, c if c == gcd(a, b) then there exists
    a pair of intergers -> x, y such that ax + by = c.
    Basically => ax + by = gcd(a, b).
    x, y are called bezout coefficients.
*/

// 7) Extended Euclidean algorithm
/*
    Used to solve the bezout identity i.e the eq -> ax + by = gcd(a, b)
    explanation -> https://www.geeksforgeeks.org/dsa/euclidean-algorithms-basic-and-extended/ 
*/
tuple<ll, ll, ll> egcd(ll a, ll b) {
    ll x = 0, y = 1, u = 1, v = 0;
    while(a != 0) {
        ll q = b / a, r = b % a;
        ll m = x - u * q, n = y - v * q;
        b = a; a = r;
        x = u; y = v;
        u = m; v = n;
    }
    return {b, x, y};
}
// returns {gcd, x, y}
// TC = o(min(a, b)) (same as euclid algo )

// 8) Chinese Remainder Theorm
/*
    Used to solve a system of linear congruences i.e ->
    x = r1 (mod m1)
    x = r2 (mod m2)
    ......
    x = rk (mod mk)
    NOTE -> There is a solution iff gcd(mi, mj) divides ai - aj for all pairs of i, j such that i != j
    explanation -> https://codeforces.com/blog/entry/61290
*/
pair<ll, ll> crt(vector<ll> &r, vector<ll> &m) {
    ll R = r[0], M = m[0];
    for(int i = 1; i < (int)r.size(); i++) {
        ll ri = r[i], mi = m[i];
        auto [g, x, y] = egcd(M, mi);
        if ((ri - R) % g != 0) return {-1, -1};
        ll lcm = M / g * mi;
        R = (R + M * ((ri - R) / g % (mi / g) * x % (mi / g)) % lcm + lcm) % lcm;
        M = lcm;
    }
    return {R, M};
}
// solves x ≡ r[i] (mod m[i]) for all i
// returns {x, lcm} such that x is the unique solution mod lcm
// for a particular system of linear congruences, if the final ans is {x, lcm} other solutions are 
// -> x +- k * lcm i.e x, x+2*lcm, x+3*lcm, etc 
// returns {-1, -1} if no solution exists

int main() {
    
    return 0;
}