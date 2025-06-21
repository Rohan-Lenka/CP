#include <bits/stdc++.h>
using namespace std;

bool isPrime(int num) {
    if(num < 2) return false; // edge case for 0 & 1
    for(int i = 2; i * i <= num; i++) {
        if(num % i == 0) return false; 
    }
    return true;
    // TC = O(sqrt(num))
    // SC = O(1)
}

vector<int> getDivisors(int num) {
    vector<int> res;
    for(int i = 1; i * i <= num; i++) {
        if(num % i == 0) {
            res.push_back(i);
            if(i != num / i) res.push_back(num / i);
        } 
    }
    return res;
    // TC = O(sqrt(n))
    // SC = O(number of divisors)
}

vector<int> getPrimeFactors(int num) {
    vector<int> res;    
    for(int i = 2; i * i <= num; i++) {
        if(num % i == 0) {
            res.push_back(i);
            while(num % i == 0) {
                num /= i;
            }
        }
    }
    if(num > 1) res.push_back(num); 
    return res;
    // TC = O(sqrt(n) * log(n))
    // SC = O(number of prime factors)
}

vector<bool> sieveOfEratosthenes(int n) {  // all primes upto n 
    vector<int> res;
    vector<bool> isPrime(n + 1, true);
    for(int i = 2; i * i <= n; i++) {  // i * i -> 2nd further optimization
        if(isPrime[i]) {
            for(int j = i * i; j <= n; j += i) isPrime[j] = false;
            // j = i * i -> 1st further optimization
        }
    }
    for(int num = 2; num <= n; num++) {
        if(isPrime[num]) res.push_back(num);
    }

    // we can return res if we want the list of all primes
    return isPrime;
    // TC -> O(n * log(log(n))) + O(n) // reason -> prime harmonic series
    // SC -> O(n)
}

// Query based functions ->
vector<int> countPrimes(vector<pair<int, int>> &queries) {
    int maxNum = INT_MIN;
    for(const auto &[l, r] : queries) {  // 1 <= l <= r <= 1e6
        maxNum = max(maxNum, r);
    }
    auto primesList = sieveOfEratosthenes(maxNum);
    vector<int> cnt(maxNum + 1, 0), res;
    int primes = 0;
    // apply prefix sum for counting primes
    for(int i = 2; i <= maxNum; i++) {
        primes += primesList[i];
        cnt[i] = primes;
    }
    for(const auto &[l, r] : queries) {  
        res.push_back(cnt[r] - cnt[l - 1]);
    }
    return res;
    // TC = O(maxNum * log(log(maxNum))) + O(maxNum) + O(Q)
    // SC = O(2 * maxNum) 
}

void printPrimeFactorization(vector<int> &queries) {  // each query is at max 1e6
    // use the concept of calculating smallest prime factor (spf) 
    // very similar to sieve 
    int maxNum = INT_MIN;
    for(const auto &e : queries) maxNum = max(maxNum, e);
    vector<int> spf(maxNum + 1);
    for(int i = 0; i < spf.size(); i++) {
        spf[i] = i;
    }
    // now we do a process very similar to sieve
    for(int i = 2; i * i <= maxNum; i++) {
        if(spf[i] == i) {  // that means smallest prime factor of the number is the number itself, hence prime
            for(int j = i * i; j <= maxNum; j += i) {
                if(spf[j] == j) {  // this means spf[j] has not been marked yet
                    spf[j] = i;  // mark each upcoming multiple of i's spf as j
                }
            }
        }
    } 
    // now solve for each query ->
    for(auto num : queries) {
        cout << "Prine factorization of " << num << " is:";
        while(num > 1) {
            cout << " " << spf[num];
            num /= spf[num];
        }
        cout << "\n";
    }
    // TC = O(nlog(log(n))) + O(Q * log(maxNum)) 
    // SC = O(maxNum)
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while(T--) {
        int sze;
        cin >> sze;
        vector<int> Q(sze);
        while(sze--) {
            int el;
            cin >> el;
            Q.push_back(el);
        }
        printPrimeFactorization(Q);
    }
    return 0;
}