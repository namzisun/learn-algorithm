#include <iostream>
#include <queue>
#include <utility>

using namespace std;

int N, Q;
int map_size;
int maps[64][64];
int L[1000];
bool visit[64][64];

int total_ice = 0;
int max_size = 0;

int dir_r[4] = {-1, 1, 0, 0};
int dir_c[4] = {0, 0, -1, 1};

bool isValid(int r, int c) {
	if (r < 0 || map_size <= r || c < 0 || map_size <= c) return false;
	return true;
}

int maxIce(int size) {
	if (size > max_size) max_size = size;
	return max_size;
}

// class Ice {
// public :
// 	int number;
// 	int row, col;

// 	Ice() {}
// 	Ice(int n, int r, int c) : number(n), row(r), col(c) {}

// 	void setRowCol(int r, int c) {
// 		row = r;
// 		col = c;
// 	}
// };


void tornado(int l) {
	int new_r;

	int tmp[64][64];
	// cout << "l : " << l <<endl;
	int sum_old_r_new_c = l-1;
	for (int r = 0; r < map_size; r += l) {
		new_r = r;
		// cout << "r : " << r << endl;
		int sum_c = sum_old_r_new_c;
		for (int c = 0; c < map_size; c += l) {
			// cout << "c : " << c << endl;
			// cout << "sum_c : " << sum_c << endl;
			for (int i = 0; i < l; ++i) {
				// cout << "i : " << i << endl;
				for (int j = 0; j < l; ++j) {
					// cout << "j : " << j << endl;
					// cout << "sum_c-(r+i) : " << sum_c-(r+i) << endl;
					int row = new_r + j;
					int col = sum_c-(r+i);
					// cout << "(" << r+i << ", " << c+j << ") => (" << row << ", " << col << ")" << endl;
					tmp[row][col] = maps[r+i][c+j];
				}
			}
			sum_c += l;
		}
		sum_old_r_new_c += l;
	}

	for (int i = 0; i < map_size; ++i) {
		for (int j = 0; j < map_size; ++j) {
			maps[i][j] = tmp[i][j];
		}
	}
}

void firestorm() {
	int tmp[64][64];

	for (int r = 0; r < map_size; ++r) {
		for (int c = 0; c < map_size; ++c) {
			if (maps[r][c] == 0) {
				tmp[r][c] = 0;
				continue;
			} 
			int count_ice = 0;
			for (int i = 0; i < 4; ++i) {
				int new_r = r + dir_r[i];
				int new_c = c + dir_c[i];

				if (!isValid(new_r, new_c)) continue;
				if (maps[new_r][new_c] > 0) count_ice++;
			}
			if (count_ice < 3) {
				tmp[r][c] = maps[r][c] - 1;
				total_ice--;
			}
		}
	}

	for (int i = 0; i < map_size; ++i) {
		for (int j = 0; j < map_size; ++j)  {
			maps[i][j] = tmp[i][j];
		}
	}
}

int bfs(int r, int c) {
	queue<pair<int, int> > q;
	q.push(make_pair(r, c));
	visit[r][c] = true;

	int count = 1;

	return 0;
}

int main() {


	cin >> N >> Q;
	map_size = 1 << N;
	map_size = pow(2, N);

	for (int i = 0; i < map_size; ++i) { 
		for (int j = 0; j < map_size; ++j) {
			cin >> maps[i][j];
			total_ice += maps[i][j];
		}
	}
	
	for (int i = 0; i < Q; ++i) {
		cin >> L[i];
	}

	for (int i = 0; i < Q; ++i) {
		tornado(1 << L[i]);
		for(int i = 0; i < map_size; ++i) {
			for (int j = 0; j < map_size; ++j) {
				cout << maps[i][j] << " ";
			} cout << endl;
		}
		firestorm();
		cout << "after firestorm\n";
		for(int i = 0; i < map_size; ++i) {
			for (int j = 0; j < map_size; ++j) {
				cout << maps[i][j] << " ";
			} cout << endl;
		}
		cout << "====================" << endl << endl;;
	}

	for (int i = 0; i < map_size; ++i) {
		for (int j = 0; j < map_size; ++j) {
			if (maps[i][j] == 0) continue;
			if (maps[i][j] == true) continue;

			int size = bfs(i, j);
			max_size = maxIce(size);
		}
	}

	cout << total_ice << endl;

	return 0;
}