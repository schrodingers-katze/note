// 고스택
// 1. 숫자 부족
// 2. 0으로 나눔
// 3. 연산 결과 절대값 > 10^9
// >> 에러 발생하거나 스택에 저장되어 있는 숫자가 1개가 아니면 에러 출력
// >> 에러가 아니라면 스택에 저장되어 있는 숫자 출력
// NUM : 절대값 10^9 넘어가면 종료
// POP  : dq.size == 0 이면 종료
// INV  : dq.size == 0 이면 종료
// DUP  : dq.size == 0 이면 종료
// SWP  : dq.size < 2 이면 종료
// ADD  : dq.size < 2이면 종료 || 연산 결과 > 10^9 이면 종료
// SUB  : dq.size < 2이면 종료 || 연산 결과 > 10^9이면 종료
// MUL  : dq.size < 2이면 종료 || 연산 결과 > 10^9 이면 종료
// DIV  : dq.size < 2이면 종료 || 0으로 나눔 
// MOD  : dq.size < 2이면 종료 || 0으로 나눔

#define MAX 1000000000
#include <iostream>
#include <deque>
#include <math.h>
#include <string>
#include <string.h>

using namespace std;

int c_cnt, e_cnt;
long long execute[10001];
string command[200002];
deque<long long> dq;

bool calculate() {
	long long tmp1, tmp2;
	string tmp;
	for (int i = 0; i < c_cnt; i++) {
		tmp = command[i];
		if (!tmp.compare("NUM")) 
			dq.push_front(stoll(command[++i]));
		else if (!tmp.compare("POP")) {
			if (dq.empty()) return false;
			dq.pop_front();
		}
		else if (!tmp.compare("INV")) {
			if (dq.empty()) return false;
			dq[0] *= -1;
		}
		else if (!tmp.compare("DUP")) {
			if (dq.empty()) return false;
			dq.push_front(dq.front());
		}
		else if (!tmp.compare("SWP")) {
			if (dq.empty() || dq.size() < 2) return false;
			tmp1 = dq.front();
			dq.pop_front();
			tmp2 = dq.front();
			dq.pop_front();
			dq.push_front(tmp1);
			dq.push_front(tmp2);
		}
		else if (!tmp.compare("ADD")) {
			if (dq.empty() || dq.size() < 2) return false;
			tmp1 = dq.front();
			dq.pop_front();
			tmp2 = dq.front();
			tmp2 += tmp1;
			if (abs(tmp2) > MAX) return false;
			dq.pop_front();
			dq.push_front(tmp2);
		}
		else if (!tmp.compare("SUB")) {
			if (dq.empty() || dq.size() < 2) return false;
			tmp1 = dq.front();
			dq.pop_front();
			tmp2 = dq.front();
			dq.pop_front();
			tmp2 -= tmp1;
			if (abs(tmp2) > MAX) return false;
			dq.push_front(tmp2);
		}
		else if (!tmp.compare("MUL")) {
			if (dq.empty() || dq.size() < 2) return false;
			tmp1 = dq.front();
			dq.pop_front();
			tmp2 = dq.front();
			dq.pop_front();
			tmp2 *= tmp1;
			if (abs(tmp2) > MAX) return false;
			dq.push_front(tmp2);
		}
		else if (!tmp.compare("DIV")) {
			if (dq.empty() || dq.size() < 2) return false;
			tmp1 = dq.front();
			dq.pop_front();
			tmp2 = dq.front();
			dq.pop_front();
			if (!tmp1) return false;
			tmp2 /= tmp1;
			dq.push_front(tmp2);
		}
		else if (!tmp.compare("MOD")) {
			if (dq.empty() || dq.size() < 2) return false;
			tmp1 = dq.front();
			dq.pop_front();
			tmp2 = dq.front();
			dq.pop_front();
			if (!tmp1) return false;

			tmp2 %= tmp1;
			dq.push_front(tmp2);
		}
	}

	if (dq.size() != 1) return false;
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	while (true) {
		c_cnt = 0;
		e_cnt = 0;
		while (true) {
			cin >> command[c_cnt];
			if (!command[c_cnt].compare("QUIT"))
				return 0;
			if (!command[c_cnt].compare("END"))
				break;
			c_cnt++;
		}
		cin >> e_cnt;
		for (int i = 0; i < e_cnt; i++)
			cin >> execute[i];

		for (int i = 0; i < e_cnt; i++) {
			dq.clear();
			dq.push_back(execute[i]);
			if (!calculate())
				cout << "ERROR\n";
			else
				cout << dq[0] << '\n';
		}

		for (int i = 0; i < c_cnt; i++)
			command[c_cnt].clear();
		cout << '\n';
	}
	return 0;
}