// 열쇠

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <queue>
#include <vector>

using namespace std;

int test_case, h, w, res;
char arr[105][105];
bool visited[105][105];
string give_key;

class Point {
public:
	int y, x;
};
Point p[4] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
vector<Point> door[26];
bool key[26];

void bfs() {
	queue<Point> q;
	q.push({ 0, 0 });
	visited[0][0] = true;
	int y, x, ny, nx;
	while (!q.empty()) {
		y = q.front().y;
		x = q.front().x;
		q.pop();
		for (int i = 0; i < 4; i++) {
			ny = y + p[i].y;
			nx = x + p[i].x;
			// 범위 벗어나감 || 이미 방문함
			if (ny < 0 || ny > h + 1 || nx < 0 || nx > w + 1 || arr[ny][nx] == '*' || visited[ny][nx])
				continue;
			else if (arr[ny][nx] >= 'A' && arr[ny][nx] <= 'Z') { // 문 발견
				if (key[arr[ny][nx] - 'A']) {  // 키 있음
					q.push({ ny, nx });
					visited[ny][nx] = true;
				}
				else  // 키 없음
					door[arr[ny][nx] - 'A'].push_back({ ny, nx });
			}
			else if (arr[ny][nx] >= 'a' && arr[ny][nx] <= 'z') {  // 키 발견
				key[arr[ny][nx] - 'a'] = true;
				q.push({ ny, nx });
				visited[ny][nx] = true;
				if (!door[arr[ny][nx] - 'a'].empty()) {  // 열지 못한 문 존재 
					int len = door[arr[ny][nx] - 'a'].size();
					for (int j = 0; j < len; j++) {
						q.push({ door[arr[ny][nx] - 'a'][j].y, door[arr[ny][nx] - 'a'][j].x });
						visited[door[arr[ny][nx] - 'a'][j].y][door[arr[ny][nx] - 'a'][j].x] = true;
					}
					door[arr[ny][nx] - 'a'].clear();
				}
			}
			else if (arr[ny][nx] == '$') { // 문서 발견
				res++;
				q.push({ ny, nx });
				visited[ny][nx] = true;
			}
			else {
				q.push({ ny, nx });
				visited[ny][nx] = true;
			}
		}
	}
}

int main() {
	scanf("%d", &test_case);
	for (int tc = 1; tc <= test_case; tc++) {
		res = 0;
		memset(arr, 0, sizeof(arr));
		memset(visited, 0, sizeof(visited));
		memset(key, false, sizeof(key));
		for (int i = 0; i < 26; i++)
			door[i].clear();
		give_key.clear();

		scanf(" %d %d", &h, &w);
		for (int i = 1; i <= h; i++) 
			for (int j = 1; j <= w; j++) 
				scanf(" %1c", &arr[i][j]);

		cin >> give_key;
		int len = give_key.size();
		for (int i = 0; i < len; i++) {
			if (give_key[i] == '0') break;
			key[give_key[i] - 'a'] = true;
		}
		for (int i = 1; i <= h; i++) {
			for (int j = 1; j <= w; j++) {
				if (arr[i][j] >= 'A' && arr[i][j] <= 'Z' && key[arr[i][j] - 'A'])
					arr[i][j] = '.';
			}
		}
		bfs();
		printf("%d\n", res);
	}
	return 0;
}