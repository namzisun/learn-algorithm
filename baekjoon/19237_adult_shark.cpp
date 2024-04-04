#include <iostream>

using namespace std;

int result = 0;

class Shark {
public:
	int priority[4][4];
	int number;

	Shark() {}
	Shark(int n, int p[4][4]) : number(n) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				priority[i][j] = p[i][j];
			}
		}
	}

	// void toString() {
	// 	cout << "number : " << number << endl;
	// 	for (int i = 0; i < 4; ++i) {
	// 		for (int j = 0; j < 4; ++j) {
	// 			cout << priority[i][j] << " ";
	// 		}
	// 		cout << endl;
	// 	}
	// }
};

int main() {

	int N, M, k;

	cin >> N >> M >> k;

	int map[N][N];
	Shark sharkArr[M+1];


	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> map[i][j];
		}
	}

	int p[4][4];
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < 4; ++j) {
			cin >> p[j][0] >> p[j][1] >> p[j][2] >> p[j][3];
		}
		Shark shark = Shark(i+1, p);
		sharkArr[i+1] = shark;
	}
	// cout << endl << endl;

	// for (int i = 0; i < N; ++i) {
	// 	for (int j = 0; j < N; ++j) {
	// 		cout << map[i][j];
	// 	}
	// 	cout << endl;
	// }
	// cout << endl;

	// for (int i = 1; i < M+1; ++i) {
	// 	sharkArr[i].toString();
	// }

	cout << result << '\n';

	return 0;
}