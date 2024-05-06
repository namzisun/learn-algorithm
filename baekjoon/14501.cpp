#include <iostream>

using namespace std;

int N;
int* T;
int* P;
int max_pay = 0;

int max(int n1, int n2) {
	if (n1 > n2) return n1;
	else return n2;
}

void input() {
	cin >> N;
	T = new int[N + 1];
	P = new int[N + 1];
	for (int i = 0; i < N; ++i) {
		cin >> T[i] >> P[i];
	}
}

void solution(int x, int sum) {
	if (x > N) return;

	max_pay = max(max_pay, sum);
	for (int i = x; i < N; ++i) {
		solution(T[i] + i, sum + P[i]);
	}
}

int main() {

	input();
	solution(0, 0);
	cout << max_pay << '\n';
	return 0;
}