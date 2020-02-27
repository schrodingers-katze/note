// 연결 요소의 개수

#include <iostream>
#include <vector>
#include <set>

using namespace std;

int n, m, res = 0;
set<int> node;
vector<int> connected[1001];
bool visited[1001] = { false, };

void dfs(int idx) {
	visited[idx] = true;
	int len = connected[idx].size();
	for (int i = 0; i < len; i++) {
		if (!visited[connected[idx][i]])
			dfs(connected[idx][i]);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int first, second;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		cin >> first >> second;
		node.insert(first);
		node.insert(second);
		connected[first].push_back(second);
		connected[second].push_back(first);
	}
	set<int>::iterator iter;
	for (iter = node.begin(); iter != node.end(); iter++) {
		if (!visited[*iter]) {
			dfs(*iter);
			res++;
		}
	}
	if (node.size() < n)
		res += (n - node.size());

	cout << res << '\n';
	return 0;
}