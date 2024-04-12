#include <iostream>
#include <vector>

using namespace std;


int smell[4][4];
int maps[4][4];

int M, S;
int shark_r, shark_c;
int die_fish_count = 0;
int shark_route = 555;

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
		// cout << "------ " << i << " ---------\n";
		for (int j = 0; j < 8; ++j) {
			int new_d = fish_vec[i].d - j;
			int new_r = fish_vec[i].r + dir_r[new_d];
			int new_c = fish_vec[i].c + dir_c[new_d];
			// cout << "new_r : " << new_r << ", new_c : " << new_c  << ", new_d : " << new_d << endl;
			while (new_d < 0) new_d += 8;

			if (!isValid(new_r, new_c)
				|| (new_r == shark_r && new_c == shark_c)
				|| smell[new_r][new_c]) continue;
			else {
				fish_vec[i].r = new_r;
				fish_vec[i].c = new_c;
				fish_vec[i].d = new_d;
				sea[new_r][new_c].push_back(fish_vec[i]);
				maps[new_r][new_c]++;
				break;
			}
		}
	}
}

void move_shark(int s[4][4], bool visit[4][4], int r, int c, int die_fish, int route) {
	bool visit_copy[4][4];
	int sea_copy[4][4];
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			sea_copy[i][j] = s[i][j];
			visit_copy[i][j] = visit[i][j];
		}
	}

	visit_copy[r][c] = true;
	die_fish += sea_copy[r][c];
	sea_copy[r][c] = 0;
	if (route > 100) {
		cout << "route : " <<route << endl;
		if (die_fish_count == die_fish) {
			if (shark_route > route) shark_route = route;
		} else if (die_fish_count < die_fish) {
			die_fish_count = die_fish;
			shark_route = route;
		}
		return;
	}
	cout << "shark_route : " << shark_route << endl;

	for (int i = 0; i < 8; i+=2) {
		// cout << "f ";
		int new_r = r + dir_r[i];
		int new_c = c + dir_c[i];

		if (!isValid(new_r, new_c) || visit_copy[new_r][new_c] == true) continue;

		route *= 10;
		if (i == 0) route += 2;
		else if (i == 2) route += 1;
		else if (i == 4) route += 4;
		else if (i == 6) route += 3;

		// if (route > 444) break;
		// cout << "q";
		move_shark(sea_copy, visit_copy, new_r, new_c, die_fish, route);
	}
	// cout << "h";
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
	shark_r--;
	shark_c--;
	bool visit[4][4];

	for (int i = 0; i < S; ++i) {
		cout << i << endl;
		copy();
		cout << "w";
		move_fish();
		cout << "e";
		move_shark(maps, visit, shark_r, shark_c, 0, 0);
		cout << shark_route << endl;
		fish_vec_copy.clear();
	}

	// for (int i = 0; i < 4; i++) {
		// for (int j = 0; j < 4; j++) {
	// 		for (int k = 0; k < sea[i][j].size(); k++) {
	// 			cout << "(" << i << ", " << j << ") : " <<  sea[i][j].at(k).d << endl; 
	// 		}
	// 	}
	// }

	return 0;
}