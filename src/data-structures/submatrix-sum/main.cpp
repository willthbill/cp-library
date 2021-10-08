template <class T>
struct SubMatrixSum // 0-indexed
{
	int rows, cols;
	vector<vector<T>> p;
	SubMatrixSum(vector<vector<T>>& arr) {
		rows = arr.size(), cols = arr[0].size();
		p = vector<vector<T>>(rows + 1, vector<T>(cols + 1, 0));
		for (int i = 0; i < rows; ++i)
			for (int j = 0; j < cols; ++j)
				p[i+1][j+1] = p[i][j+1] + p[i+1][j] - p[i][j] + arr[i][j]
	}
	// (x1, y1) is topleft, (x2, y2) is bottomright
	T sum(int y1, int x1, int y2, int x2) {
		return prefix[y2 + 1][x2 + 1] - prefix[y1][x2 + 1] - prefix[y2 + 1][x1] + prefix[y1][x1];
	}
};
