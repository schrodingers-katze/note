// 경사로

#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, l, res = 0;
	int arr[101][202];
	cin >> n >> l;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> arr[i][j];

	for (int j = 0; j < n; j++)
		for (int i = 0; i < n; i++)
			arr[j][i + n] = arr[i][j];

	int i, cnt;
	for (int j = 0; j < n + n; j++) {
		cnt = 1;
		for (i = 0; i < n - 1; i++) {
			// 높이가 같은 경우
			if (arr[i][j] == arr[i + 1][j]) cnt++;
			// 다음 블럭이 더 높은 경우 >> 오르막
			else if (arr[i][j] + 1 == arr[i + 1][j] && cnt >= l) cnt = 1;
			// 다음 블럭이 더 낮은 경우 >> 내리막
			else if (arr[i][j] - 1 == arr[i + 1][j] && cnt >= 0) cnt = 1 - l;
			else break;
		}
		if (i == n - 1 && cnt >= 0)
			res++;
	}
	cout << res << '\n';
	return 0;
}