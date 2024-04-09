#include <iostream>

using namespace std;

int N;
int maps[499][499];

int row, col;

int tornado_dir_r[4] = {0, 1, 0, -1};
int tornado_dir_c[4] = {-1, 0, 1, 0};
int tornado_dir = 0;

int sand_dir_r[4][10] = {
	{-2, -1, -1, -1, 0, 1, 1, 1, 2, 0},
	{0, 1, 0, -1, 2, 1, 0, -1, 0, 1},
	{-2, -1, -1, -1, 0, 1, 1, 1, 2, 0},
	{0, -1, 0, 1, -2, -1, 0, 1, 0, -1}
};
int sand_dir_c[4][10] = {
	{0, -1, 0, 1, -2, -1, 0, 1, 0, -1},
	{-2, -1, -1, -1, 0, 1, 1, 1, 2, 0},
	{0, 1, 0, -1, 2, 1, 0, -1, 0, 1},
	{-2, -1, -1, -1, 0, 1, 1, 1, 2, 0}
};
int sand_rate[10] = {2, 10, 7, 1, 5, 10, 7, 1, 2, -1};

int outside = 0;

void print() {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << maps[i][j] << " ";
		} cout << endl;
	}
	cout << endl;
}

bool isOut(int r, int c) {
	if (r < 0 || N <= r || c < 0 || N <= c) return true;
	return false;
}

void sand() {
	int left_sand = maps[row][col];
	int sand;

	for (int i = 0; i < 10; i++) {
		int r = row + sand_dir_r[tornado_dir%4][i];
		int c = col + sand_dir_c[tornado_dir%4][i];
		
		if (i < 9) {
			sand = maps[row][col] * sand_rate[i] / 100;
			left_sand -= sand;
		} else {
			sand = left_sand;
		}
		// cout << "sand : " << sand << endl;
		if (isOut(r, c)) 
			outside += sand;
		else 
			maps[r][c] += sand;
	}
}

void tornado() {

	for (int i = 0; i < (tornado_dir/2+1); i++) {
		row += tornado_dir_r[tornado_dir%4];
		col += tornado_dir_c[tornado_dir%4];
		
		if (row < 1) row = 0;
		if (col < 1) col = 0;
		sand();
		maps[row][col] = 0;
		
		// cout << "(" << row << ", " << col <<") : "<< maps[row][col] << endl;
		// print();
		// cout << "out : " << outside<< endl;
		if (row == 0 && col == 0) break;
	}
	tornado_dir++;
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

	int o = 1;

	while(true) {
		if (row == 0 && col == 0) break;
		// cout << o << ": (" << row << ", " << col << ")" << endl;
		tornado();
		// cout << "===========================" << endl;
		// sand();
	}

	cout << outside << '\n';

	return 0;
}