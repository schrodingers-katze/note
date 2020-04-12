# `BOJ` [`11726`](https://www.acmicpc.net/problem/11726) 2xn 타일링



## 문제

2×n 크기의 직사각형을 1×2, 2×1 타일로 채우는 방법의 수를 구하는 프로그램을 작성하시오.

아래 그림은 2×5 크기의 직사각형을 채운 한 가지 방법의 예이다.



## 코드

```cpp
// 2xn 타일링

#include <iostream>

using namespace std;

int n;
int arr[1001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	arr[0] = arr[1] = 1;
	for (int i = 2; i <= n; i++) 
		arr[i] = (arr[i - 2] + arr[i - 1]) % 10007;
	cout << arr[n] << '\n';
	return 0;
}
```


