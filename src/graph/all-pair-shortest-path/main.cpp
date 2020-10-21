%include<graph/dijkstra>%
%include<graph/floyd_warshall>%
template<class Int=long long>
vector<vector<Int>> APSP(vector<vector<pair<int, Int>>>& adj, Int MX, int M){
	// dijkstra: O((n + m log m) * n), c = 5
	// floyd_warshall: O(n^3), c = 1
	int N = (int)adj.size();
	long long timedijk = ((long long)(((long long)(N + M * 20)) * N)) * 5;
	long long timefloyd = ((long long)(((long long)N) * N)) * N;
	if(timedijk <= timefloyd){
		vector<vector<Int>> res (N);
		Dijkstra<Int> ds (adj, MX);
		for(int i = 0; i < N; i++){
			res[i] = ds.run(i);
		}
		return res;
	}else{
		return floyd_warshall(adj, MX);
	}
}
