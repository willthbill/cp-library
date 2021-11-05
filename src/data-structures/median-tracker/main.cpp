struct median_tracker {
    multiset<int, greater<int>> left;
    multiset<int> right; // if odd amount in total, then more in left
    void _balance() {
        while(left.size() > right.size()) {
            right.insert(*left.begin());
            left.erase(left.begin());
        }
        while(left.size() < right.size()) {
            left.insert(*right.begin());
            right.erase(right.begin());
        }
    }
    int median() {
        assert(left.size() + right.size() > 0);
        if((left.size() + right.size()) % 2 == 0) {
            return (*left.begin() + *right.begin()) / 2;
        }else {
            return *left.begin();
        }
    }
    void insert(int val) {
        if(left.empty() || val > *left.begin()) right.insert(val);
        else left.insert(val);
        _balance();
    }
    void erase(int val) {
        if(val > median()) right.erase(right.find(val));
        else left.erase(left.find(val));
        _balance();
    }
};