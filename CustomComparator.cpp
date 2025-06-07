#include <bits/stdc++.h>
using namespace std;

vector<int> arr;

// Types of Comparators
// 1) Function Pointer
bool static cmp(int a, int b) {
    return a > b; // Descending order
}

// 2) Lambda Function (Modern C++)
sort(arr.begin(), arr.end(), [](int a, int b) {
    return a > b; // Descending
});

// 3) Functor (Struct with operator())
struct Descending {  // can be a class too
    bool operator()(int a, int b) const {
        return a > b;
    }
};
sort(arr.begin(), arr.end(), Descending());

// Custom Comparator in set / map
struct CustomCmp {
    bool operator()(const pair<int, int> &a, const pair<int, int> &b) const {
        return a.second < b.second; // Order by second
    }
};
set<pair<int, int>, CustomCmp> s;

// Custom Comparator in priority queue
struct Compare {
    bool operator()(int a, int b) {
        return a > b;  
    }
};
priority_queue<int, vector<int>, Compare> pq;

// V-IMP -> Comparator returns true if a should come before b.
// IMP ->
// USE_CASE	    WHAT YOU PASS	                    WHY
// sort()	    Comparator object (Descending())	Function needs actual callable
// set/map	    Comparator type (Descending)	    Class templates create object internally

int main() {
    // Functors ->
    // -they are also called function objects
    // -when function behave as an object
    // -function wrapped inside a class / struct so that it is available as an object
    // -functors are made by overloading the () operator 
    // -syntax_
    /* 
        bool operator()( <params> ) {
            // logic
        }
    */
    // -when u call the object of the class inside which the functor is present,
    //  u can call the function itself by using the overloaded () operator 
    //  example in the custom comparators discussed
    return 0;
}