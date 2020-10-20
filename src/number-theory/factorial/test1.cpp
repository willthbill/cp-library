#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#include "main.cpp"

int main(){
	vector<ll> factorials = get_factorials(50, 1e9 + 7);
	for(int i = 0; i <= 50; i++)
		cout << factorials[i] << ' ';
	cout << endl;
}

