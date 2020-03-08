// 좀비
// 11:40

#define SIZE 100000
#include <iostream>
#include <limits.h>
#include <string.h>
#include <vector>
#include <queue>

using namespace std;

int n, m, k, s, p, q;
long long res;
int dist[SIZE + 1] = { 0, };
long long low_dist[SIZE + 1] = { 0, };
bool visited[SIZE + 1] = { false, };
bool zombie_visited[SIZE + 1] = { false, };
vector<int> zombie;
vector<vector<int>> v;

class Point {
public:
	int node, depth;
};

class Point2 {
public:
	int node;
	long long cost;
};

// 위험한 도시 찾기
void bfs(int _node) {
	queue<Point> pq;
	pq.push({ _node, 0 });
	zombie_visited[_node] = true;
	int node, nnode, depth, len;
	while (!pq.empty()) {
		node = pq.front().node;
		depth = pq.front().depth;
		if (depth == s) return;
		pq.pop();

		len = v[node].size();
		for (int i = 0; i < len; i++) {
			nnode = v[node][i];
			if (!zombie_visited[nnode]) {
				if (dist[nnode] == INT_MAX)
					continue;
				dist[nnode] = q;
				zombie_visited[nnode] = true;
				pq.push({ nnode, depth + 1 });
			}
		}
	}
}

// 최단비용 찾기
void bfs2() {
	int node, nnode, len;
	long long cost;
	for (int i = 1; i <= n; i++)
		low_dist[i] = LLONG_MAX;
	queue<Point2> pq;
	pq.push({ 1, 0 });
	low_dist[1] = 0;
	while (!pq.empty()) {
		node = pq.front().node;
		cost = pq.front().cost;
		len = v[node].size();
		pq.pop();
		for (int i = 0; i < len; i++) {
			nnode = v[node][i];
			if (dist[nnode] == INT_MAX) continue;
			if (nnode == n) {
				res = res > cost ? cost : res;
				continue;
			}
			if (low_dist[nnode] > cost + dist[nnode]) {
				low_dist[nnode] = cost + dist[nnode];
				pq.push({ nnode, cost + dist[nnode] });
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n >> m >> k >> s;
	cin >> p >> q;
	v.resize(n + 1);
	int input1, input2;
	res = LLONG_MAX;
	for (int i = 0; i < k; i++) {
		cin >> input1;
		dist[input1] = INT_MAX;
		zombie.push_back(input1);
	}
	for (int i = 0; i < m; i++) {
		cin >> input1 >> input2;
		if (!dist[input1]) dist[input1] = p;
		if (!dist[input2]) dist[input2] = p;
		v[input1].push_back(input2);
		v[input2].push_back(input1);
	}

	// 위험한 도시 찾기
	for (int i = 0; i < k; i++) {
		memset(zombie_visited, false, sizeof(zombie_visited));
		bfs(zombie[i]);
	}

	dist[1] = 0;
	dist[n] = 0;
	visited[1] = true;
	bfs2();

	cout << res << '\n';
	return 0;
}