vector<string> split(string s, char c=' ') {
	string build = "";
	vector<string> ans;
	for (char t : s) {
		if (t == c) {
			ans.pb(build);
			build.clear();
		}
		else {
			build.pb(t);
		}
	}
	if (build.size())
		ans.pb(build);
	return ans;
}

