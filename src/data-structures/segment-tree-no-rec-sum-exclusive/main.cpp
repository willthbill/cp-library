template<class T>
class ST {
    int N;
    T* tree;
public:
    ST(T* arr, int N) {
        this->N = N;
        tree = new T[N * 2];
        for (int i = 0; i < N; i++)
            tree[N + i] = arr[i];
        for (int i = N - 1; i > 0; --i)
            tree[i] = tree[i * 2] + tree[i * 2 + 1];
    }

    void update(int index, T value) {
        tree[index + N] = value;
        index = index + N;
        for (int i = index; i > 1; i /= 2)
            tree[i / 2] = tree[i] + tree[i ^ 1];
    }

    T sum(int l, int r) {
        T res = 0;
        for (l += N, r += N; l < r; l /= 2, r /= 2) {
            if (l & 1) res += tree[l++];
            if (r & 1) res += tree[--r];
        }
        return res;
    }

    ~ST() {
        delete[] tree;
    }
};
