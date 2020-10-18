// NOT TESTED on any online task. ordered_set and ordered_map
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T1, typename T2>
using ordered_map = tree<T1, T2, less<T1>, rb_tree_tag, tree_order_statistics_node_update>;
/// Example
/*
    ordered_set<int> oset;
    oset.insert(1);
    oset.find_by_order(0); // 1
    oset.order_of_key(1); // 0
*/
