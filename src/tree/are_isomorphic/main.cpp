string _assign_canonical_names(int v, vector<vector<int>>& edg)
{
	int n = edg.size();
	if (edg[v].size() == 0)
	{
		return "10";
	}
	vector<string> cur;
	for(int nxt : edg[v])
	{
		cur.pb(_assign_canonical_names(nxt, edg));
	}
	string temp = "";
	sort(cur.rbegin(), cur.rend());
	for(string t : cur)
	{
		temp += t;
	}
	return '1' + temp + '0';
}
bool are_isomorphic(vector<vector<int>>& edg1, vector<vector<int>>& edg2)
{
	return _assign_canonical_names(0, edg1) == _assign_canonical_names(0, edg2);
}


