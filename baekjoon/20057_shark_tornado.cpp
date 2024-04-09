#include <iostream>

using namespace std;

int N;
int maps[499][499];

int row, col;

int dir_r[4] = {0, 1, 0, -1};
int dir_c[4] = {-1, 0, 1, 0};
int dir = 0;

void tornado() {
	row += dir_r[dir%4]*(dir/2+1);
	col += dir_c[dir%4]*(dir/2+1);
	if (row < 1) row = 0;
	if (col < 1) col = 0;
	dir++;
}

void sand() {

}

int main() {

	cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> maps[i][j];
		}
	}

	row = N/2;
	col = N/2;

	while(true) {
		if (row == 0 && col == 0) break;
		tornado();
		cout << "(" << row << ", " << col <<")"<< endl;
		sand();
	}

	return 0;
}