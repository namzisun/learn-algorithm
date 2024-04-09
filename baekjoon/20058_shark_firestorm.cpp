#include <iostream>
#include <cmath>

using namespace std;

int N, Q;
int map_size;
int maps[64][64];
int L[1000];

int main() {

	cin >> N >> Q;
	map_size = pow(2, N);

	for (int i = 0; i < map_size; ++i) {
		for (int j = 0; j < map_size; ++j) {
			cin >> maps[i][j];
		}
	}
	
	for (int i = 0; i < Q; ++i) {
		cin >> L[i];
	}

	return 0;
}