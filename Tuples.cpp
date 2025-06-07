#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // NOTES ->
    // A tuple in C++ is a fixed-size collection of heterogeneous values.
    
    // 1) Tuple Creation ->
    tuple<int, string, double> person(25, "Alice", 72.5);  // using constructor 
    auto t1 = make_tuple(42, "hello", 3.14);  // using make_tuple function
    tuple<int, string, float> t2 = {1, "world", 2.5f};  // using { }
    
    // 2) Accessing Elements
    cout << get<0>(t1);   // 42
    cout << get<1>(t1);   // "hello" 
    // using get function -> get<index>(tuple variable)
    
    // 3) Modifying Elements
    get<0>(t1) = 100;

    // 4) C++17 structured bindings
    tuple<int, string, bool> t = {100, "HelloWorld", true};
    auto [integer, str, boolean] = t;  // always use auto 

    // 5) Tuple Size and Type // not imp
    tuple<int, double, char> t;
    cout << tuple_size<decltype(t)>::value;  // 3
    using T1 = tuple_element<1, decltype(t)>::type;  // double

    // 6) Tie and Ignore
    tuple<int, string> t = {10, "Hi"};
    int x; string s;
    tie(x, s) = t;    // Unpack values or u can use structured binding method
    int y;
    tie(y, ignore) = t;  // Ignore the second element

    // 7) Comparison of Tuples (Lexicographical comparison is used)
    tuple<int, int> a = {1, 2}; tuple<int, int> b = {1, 3};
    cout << (a < b); // true

    return 0;
}