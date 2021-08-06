vector<bool> assigned(2*N, 0);
vector<int64_t> assign(2*N, 0);
vector<int64_t> lazy(2*N, 0);
vector<int64_t> tree(2*N, 0);
vector<int64_t> A(n, 0);

function<void(int, int, int)> propagate = [&] (int k, int x, int y) {
    if (assigned[k]) {
        tree[k] = assign[k]*(y-x+1);
        if (k < N) {
            assign[k*2+1] = assign[k*2] = assign[k];
            lazy[k*2+1] = lazy[k*2] = 0;
            assigned[k*2+1] = assigned[k*2] = true;
        }
        assign[k] = 0;
        assigned[k] = false;
    }
    tree[k] += lazy[k]*(y-x+1);
    if (k < N) {
        lazy[k*2] += lazy[k];
        lazy[k*2+1] += lazy[k];
    }
    lazy[k] = 0;
};

function<int64_t(int, int, int, int, int)> qry = [&] (int a, int b, int k, int x, int y) {
    if (y < a || b < x) return (int64_t)0;
    if (x >= a && b >= y) {
        propagate(k, x, y);
        return tree[k];
    }
    int d = x+(y-x)/2;
    propagate(k, x, y);
    return qry(a, b, k*2, x, d)+qry(a, b, k*2+1, d+1, y);
};

function<void(int, int, int, int, int, int64_t)> add = [&] (int a, int b, int k, int x, int y, int64_t u) {
    if (y < a || b < x) propagate(k, x, y);
    else if (x >= a && b >= y) {
        lazy[k] += u;
        propagate(k, x, y);
    } else {
        int d = x+(y-x)/2;
        propagate(k, x, y);
        add(a, b, k*2, x, d, u);
        add(a, b, k*2+1, d+1, y, u);
        tree[k] = tree[k*2]+tree[k*2+1];
    }
};

function<void(int, int, int, int, int, int64_t)> set = [&] (int a, int b, int k, int x, int y, int64_t u) {
    if (y < a || b < x) propagate(k, x, y);
    else if (x >= a && b >= y) {
        assign[k] = u;
        assigned[k] = true;
        lazy[k] = 0;
        propagate(k, x, y);
    } else {
        int d = x+(y-x)/2;
        propagate(k, x, y);
        set(a, b, k*2, x, d, u);
        set(a, b, k*2+1, d+1, y, u);
        tree[k] = tree[k*2]+tree[k*2+1];
    }
};
