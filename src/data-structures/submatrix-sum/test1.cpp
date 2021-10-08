#include<bits/stdc++.h>
using namespace std;
#define ll long long

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
				p[i+1][j+1] = p[i][j+1] + p[i+1][j] - p[i][j] + arr[i][j];
	}
	// (x1, y1) is topleft, (x2, y2) is bottomright
	T sum(int y1, int x1, int y2, int x2) {
		return p[y2 + 1][x2 + 1] - p[y1][x2 + 1] - p[y2 + 1][x1] + p[y1][x1];
	}
};


int main(){
	int n, q;
	cin >> n >> q;
	vector<vector<int>> arr(n, vector<int>(n, 0));
	for(int i = 0; i < n; i++){
		string in;
		cin >> in;
		for(int j = 0; j < n; j++)
			arr[i][j] = (in[j] == '*');
	}
	SubMatrixSum<int> ps(arr);
	while(q--) {
		int y1, x1, y2, x2;
		cin >> y1 >> x1 >> y2 >> x2;
		y1--,x1--,y2--,x2--;
		cout << ps.sum(y1,x1,y2,x2) << endl;
	}
	return 0;
}
