// 미네랄

#include <iostream>
#include <string.h>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int r, c, n;
char arr[101][101];
bool visited[101][101];
int stick[101];

class Point {
public:
	int y, x;
};
Point p[4] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
vector<Point> kluster;

void print() {
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cout << arr[i][j];
		}
		cout << '\n';
	}
}

bool desc(Point p1, Point p2) {
	if (p1.y > p2.y)
		return true;
	else {
		if (p1.y < p2.y)
			return false;
		else {
			if (p1.x < p2.x)
				return true;
			else
				return false;
		}
	}
}

bool find_kluster(int _y, int _x) {
	int y, x, ny, nx;
	queue<Point> q;
	q.push({ _y, _x });
	visited[_y][_x] = true;
	kluster.push_back({ _y, _x });
	while (!q.empty()) {
		y = q.front().y;
		x = q.front().x;
		q.pop();
		for (int i = 0; i < 4; i++) {
			ny = y + p[i].y;
			nx = x + p[i].x;
			if (ny >= 0 && ny < r && nx >= 0 && nx < c && !visited[ny][nx] && arr[ny][nx] == 'x') {
				if (ny == r - 1) return false;
				kluster.push_back({ ny, nx });
				visited[ny][nx] = true;
				q.push({ ny, nx });
			}
		}
	}
	for (int i = 0; i < kluster.size(); i++)
		arr[kluster[i].y][kluster[i].x] = '.';

	return true;
}

void falling_kluster() {
	sort(kluster.begin(), kluster.end(), desc);
	int len = kluster.size();
	int y, x, cnt = 1;
	bool flag = false;
	while (true) {
		for (int i = 0; i < len; i++) {
			y = kluster[i].y + cnt;
			x = kluster[i].x;
			if (y == r || arr[y][x] == 'x') {
				flag = true;
				break;
			}
		}
		if (flag) {
			cnt--;
			break;
		}
		cnt++;
	}

	for (int i = 0; i < len; i++)
		arr[kluster[i].y + cnt][kluster[i].x] = 'x';
}

void throw_stick() {
	int y, x, d, ny, nx;
	for (int i = 0; i < n; i++) {
		if (i % 2) {
			d = 1;
			x = c;
		}
		else {
			d = 0;
			x = -1;
		}
		y = r - stick[i];
		while (true) {
			x += p[d].x;
			if (x >= c || x < 0) break;
			if (arr[y][x] == 'x') {
				arr[y][x] = '.';
				for (int j = 0; j < 4; j++) {
					ny = y + p[j].y;
					nx = x + p[j].x;
					if (nx >= 0 && nx < c && ny >= 0 && ny < r && arr[ny][nx] == 'x') {
						memset(visited, false, sizeof(visited));
						kluster.clear();
						if (find_kluster(ny, nx)) {
							falling_kluster();
							break;
						}
					}
				}
				break;
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> r >> c;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			cin >> arr[i][j];
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> stick[i];

	throw_stick();
	print();
	return 0;
}