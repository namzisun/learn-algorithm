#include <iostream>

using namespace std;

int max_result = 0, min_result = 0;
int N;
int* A;
int plus, minus, div, mul;

int main() {
	cin >> N;
	A = new int[N];
	for (int i = 0; i < N; ++i) {
		cin >> A[i];
	}
	cin >> plus >> minus >> mul >> div;


	return 0;
}