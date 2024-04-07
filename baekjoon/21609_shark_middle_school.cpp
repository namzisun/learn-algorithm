#include <iostream>

using namespace std;

int dir_r[4] = {-1, 1, 0, 0};
int dir_c[4] = {0, 0, -1, 1};
int stage[20][20];
int N, M;

void makeBlockGroup() {
	
}

void autoPlay() {

}

int main() {
	cin >> N >> M;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> stage[i][j];
		}
	}
}