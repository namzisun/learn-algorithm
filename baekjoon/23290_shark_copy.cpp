#include <iostream>
#include <vector>

using namespace std;


int smell[4][4];

int M, S;
int shark_r, shark_c;

int dir_r[8] = {0,-1,-1,-1,0,1,1,1};
int dir_c[8] = {-1,-1,0,1,1,1,0,-1};


struct Fish {
	int r, c, d;
	bool live;
};

vector<Fish> fish_vec;
vector<Fish> fish_vec_copy;
vector<Fish> sea[4][4];

bool isValid(int r, int c) {
	if (r < 0 || c < 0 || 4 <= r || 4 <= c) return false;
	return true;
}

void copy() {
	fish_vec_copy = fish_vec;
}

void move_fish() {
	for (int i = 0; i < fish_vec.size(); ++i) {
		cout << "------ " << i << " ---------\n";
		for (int j = 0; j < 8; ++j) {
			int new_d = fish_vec[i].d - j;
			int new_r = fish_vec[i].r + dir_r[new_d];
			int new_c = fish_vec[i].c + dir_c[new_d];
			cout << "new_r : " << new_r << ", new_c : " << new_c  << ", new_d : " << new_d << endl;
			while (new_d < 0) new_d += 8;

			if (!isValid(new_r, new_c)
				|| (new_r == shark_r && new_c == shark_c)
				|| smell[new_r][new_c]) continue;
			else {
				fish_vec[i].r = new_r;
				fish_vec[i].c = new_c;
				fish_vec[i].d = new_d;
				sea[new_r][new_c].push_back(fish_vec[i]);

				break;
			}
		}
	}
}

int main() {
	cin >> M >> S;

	for (int i = 0; i < M; ++i) {
		int r,c,d;

		cin >> r >> c >> d;

		Fish f = {r-1, c-1, d-1, true};
		fish_vec.push_back(f);
		// sea[r][c].push_back(f);
	}

	cin >> shark_r >> shark_c;


	for (int i = 0; i < S; ++i) {
		copy();
		move_fish();
		fish_vec_copy.clear();
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < sea[i][j].size(); k++) {
				cout << "(" << i << ", " << j << ") : " <<  sea[i][j].at(k).d << endl; 
			}
		}
	}

	return 0;
}