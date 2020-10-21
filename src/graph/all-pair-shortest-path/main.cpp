%include<graph/dijkstra>%
template<class Int=long long>
vector<vector<Int>> APSP(vector<vector<pair<int, Int>>>& adj){
	int N = (int)adj.size();
	vector<vector<Int>> res (N);
	Dijkstra<Int> ds (adj);
	for(int i = 0; i < N; i++){
		res[i] = ds.run(i);
	}
	return res;
}
