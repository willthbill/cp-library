template <class T>
struct prefix_sum_2d // 0-indexed
{
	int rows, cols;
	vector<vector<T>> data;
	vector<vector<T>> prefix;
	prefix_sum_2d(int r, int c) : rows(r), cols(c) {
		data = vector<vector<T>>(rows, vector<T>(cols));
		prefix = vector<vector<T>>(rows + 1, vector<T>(cols + 1));
	}
    T& operator()(int i, int j) { return data[i][j]; }
	void build(){
		for(int i = 0; i <= rows; i++)
			prefix[i][0] = 0;
		for(int i = 0; i <= cols; i++)
			prefix[0][i] = 0;
		for(int k = 2; k <= cols + rows; k++)
			for(int i = max(1, k - rows), j = k - i; i <= min(k - 1, rows) && j <= cols; ++i, j = k - i)
				prefix[i][j] = prefix[i-1][j] + prefix[i][j - 1] + data[i - 1][j - 1] - prefix[i-1][j-1];
	}
	T qsum(int y1, int x1, int y2, int x2) {
		y1++,x1++,y2++,x2++;
		return prefix[y2][x2] - prefix[y1 - 1][x2] - prefix[y2][x1 - 1] + prefix[y1 - 1][x1 - 1];
	}
};
