#include <bits/stdc++.h>
using namespace std;

void make_segment_tree(int* arr, int N, int* tree) {
    for (int i = 0; i < N; i++)
        tree[N + i] = arr[i];
    for (int i = N - 1; i > 0; --i)
        tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

void update(int index, int value, int N, int* tree) {
    tree[index + N] = value;
    index = index + N;
    for (int i = index; i > 1; i /= 2)
        tree[i / 2] = tree[i] + tree[i ^ 1];
}

int sum(int l, int r, int N, int* tree) {
    int res = 0;
    for (l += N, r += N; l < r; l /= 2, r /= 2) {
        if (l & 1) res += tree[l++];
        if (r & 1) res += tree[--r];
    }
    return res;
}

int main(){

    int N = 10;
    int index = 0, value = 2, l = 0, r = N-1;
    int m[N] = {0};
    int tree[N * 2];
    make_segment_tree(m, N, tree);
    update(index, value, N, tree);
    update(5, 4, N, tree);
    cout << sum(l, r, N, tree) << endl;

return 0;
}
