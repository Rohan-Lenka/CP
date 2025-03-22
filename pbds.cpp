#include<bits/stdc++.h>

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; // find_by_order, order_of_key
        // data type         // greater / less_equal -> comparator 
        // to be stored 
        // in the ordered_set          

int main() {
	ordered_set A; // declaration

	// Inserting elements - 1st query
	A.insert(1);
	A.insert(10);
	A.insert(2);
	A.insert(7);
	A.insert(2);  // ordered set only contains unique values

    cout << A.size() << "\n"; // for size, TC = O(1)

	// A contains
	cout << "A = ";
	for (auto i : A)
		cout << i << " ";
	cout << endl;
	cout << endl;

	// finding kth element - 4th query
	cout << "0th element: " << *A.find_by_order(0) << endl;
	cout << "1st element: " << *A.find_by_order(1) << endl;
	cout << "2nd element: " << *A.find_by_order(2) << endl;
	cout << "3rd element: " << *A.find_by_order(3) << endl;
	cout << endl;

	// finding number of elements smaller than X - 3rd query
	cout << "No. of elems smaller than 6: " << A.order_of_key(6) << endl; // 2
	cout << "No. of elems smaller than 11: " << A.order_of_key(11) << endl; // 4
	cout << "No. of elems smaller than 1: " << A.order_of_key(1) << endl; // 0
	cout << endl;

	// lower bound -> Lower Bound of X = first element >= X in the set
	cout << "Lower Bound of 6: " << *A.lower_bound(6) << endl;
	cout << "Lower Bound of 2: " << *A.lower_bound(2) << endl;
	cout << endl;

	// Upper bound -> Upper Bound of X = first element > X in the set
	cout << "Upper Bound of 6: " << *A.upper_bound(6) << endl;
	cout << "Upper Bound of 1: " << *A.upper_bound(1) << endl;
	cout << endl;

	// // Remove elements - 2nd query
	A.erase(1);
	A.erase(11); // element that is not present is not affected

    // all these above functions take log(n) TC

	// A contains
	cout << "A = ";
	for (auto i : A)
		cout << i << " ";
	cout << endl;

}

// NOTE -> 
// never do A.order_of_key(val) - A.begin() // error // reason pbds is not same as STL

// for greater type ordered_set -> 
/*
   typedef tree<int, null_type, greater<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set; 
   // greater means elements in descending order
   // greater_equal or less_equal means no removal of duplicates from the set
   // for greater ->
   A.order_of_key(val) // returns number of elements STRICTLY GREATER than val
   
   int random(ordered_set &os) { // } // always pass by reference for avoidng TLE 
*/

// How to pass a custom comparator to an ordered_set ?
// u cant pass a traditional bool static cmp() {...} comparator to an ordered_set
// instead u can pass a struct as a comparator ->
/*
	struct custom_compare {
		bool operator()(const <data_type>, const <data_type>) const {
			// ur logic
		}
	};
	typedef tree<<data_type>, null_type, custom_compare, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
*/
// Ex -> 
// struct custom_compare {
//     bool operator()(const pair<int, string>& a, const pair<int, string>& b) const {
//         if (a.first == b.first)
//             return a.second < b.second;  // Sort by second value if first values are equal
//         return a.first < b.first;  // Otherwise, sort by first value
//     }
// };
// // Define ordered_set with custom comparator
// typedef tree<pair<int, string>, null_type, custom_compare, rb_tree_tag, tree_order_statistics_node_update> ordered_set;