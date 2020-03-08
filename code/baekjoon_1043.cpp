// 거짓말

#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t_cnt, input, input2;
	int n, m, cnt = 0;
	set<int> is_know;
	set<int> party[51];

	cin >> n >> m;
	cin >> t_cnt;
	for (int i = 0; i < t_cnt; i++) {
		cin >> input;
		is_know.insert(input);
	}
	for (int i = 0; i < m; i++) {
		cin >> input;
		for (int j = 0; j < input; j++) {
			cin >> input2;
			party[i].insert(input2);
		}
	}
	
	int len;
	set<int>::iterator iter1;
	set<int>::iterator iter2;
	while (true) {
		len = is_know.size();
		for (int i = 0; i < m; i++) {
			iter1 = party[i].begin();
			for (iter2 = is_know.begin(); iter2 != is_know.end(); iter2++) {
				iter1 = party[i].find(*iter2);
				if (iter1 != party[i].end()) {
					for (iter1 = party[i].begin(); iter1 != party[i].end(); iter1++)
						is_know.insert(*iter1);
					break;
				}
			}
		}
		if (len == is_know.size())
			break;
	}

	bool flag;
	for (int i = 0; i < m; i++) {
		iter1 = party[i].begin();
		flag = true;
		for (iter2 = is_know.begin(); iter2 != is_know.end(); iter2++) {
			iter1 = party[i].find(*iter2);
			if (iter1 != party[i].end()) {
				flag = false;
				break;
			}
		}
		if (flag)
			cnt++;
	}

	cout << cnt << '\n';
	return 0;
}