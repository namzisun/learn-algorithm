#include <iostream>
#include <vector>

using namespace std;


int smell[4][4];
int maps[4][4];
int answer = 0;
int M, S;
int shark_r, shark_c;
int die_fish_count = 0;
int shark_route = 555;
bool start = true;

int dir_r[8] = {0,-1,-1,-1,0,1,1,1};
int dir_c[8] = {-1,-1,0,1,1,1,0,-1};

int shark_dir_r[5] = {0, -1, 0, 1, 0};
int shark_dir_c[5] = {0, 0, -1, 0, 1};

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
		int j =0;
		for (; j < 8; ++j) {
			int new_d = fish_vec[i].d - j;
			while (new_d < 0) new_d += 8;
			int new_r = fish_vec[i].r + dir_r[new_d];
			int new_c = fish_vec[i].c + dir_c[new_d];
			cout << "new_r : " << new_r << ", new_c : " << new_c  << ", new_d : " << new_d << endl;
			
			cout << "origin : " << "(" << fish_vec[i].r << ", " << fish_vec[i].c << ") => " << fish_vec[i].d << endl;
			cout << "move  : " << "(" << new_r << ", " << new_c << ") => " << new_d << endl;;
			if (!isValid(new_r, new_c)
				|| (new_r == shark_r && new_c == shark_c)
				|| smell[new_r][new_c]) continue;
			else {
				fish_vec[i].r = new_r;
				fish_vec[i].c = new_c;
				fish_vec[i].d = new_d;
				// if (start) {
					sea[new_r][new_c].push_back(fish_vec[i]);
					maps[new_r][new_c]++;
				// }
				break;
			}
		} 
		if (j == 8) {
			sea[fish_vec[i].r][fish_vec[i].c].push_back(fish_vec[i]);
			maps[fish_vec[i].r][fish_vec[i].c]++;
		}
	}
}

void choose_route_shark(int s[4][4], bool visit[4][4], int r, int c, int die_fish, int route) {
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
		// cout << "route : " <<route  << ", die_fish : " << die_fish<< endl;
		if (die_fish_count == die_fish) {
			if (shark_route > route) shark_route = route;
		} else if (die_fish_count < die_fish) {
			die_fish_count = die_fish;
			shark_route = route;
		}
		return;
	}
	// cout << "shark_route : " << shark_route << endl;

	for (int i = 1; i < 5; ++i) {
		// cout << "for : " << i << endl;
		int new_r = r + shark_dir_r[i];
		int new_c = c + shark_dir_c[i];

		// cout << "visit : (" << new_r << ", " << new_c  << ") " << visit_copy[new_r][new_c] << endl;
		if (!isValid(new_r, new_c) || visit_copy[new_r][new_c] == true) continue;
		int new_route = route * 10 + i;
		// if (i == 0) new_route += 2;
		// else if (i == 2) new_route += 1;
		// else if (i == 4) new_route += 4;
		// else if (i == 6) new_route += 3;

		// if (new_route > 444) break;
		// cout << "q";
		choose_route_shark(sea_copy, visit_copy, new_r, new_c, die_fish, new_route);
	}
	// cout << "h";
}

void move_shark() {
	for (int i = 0; i < 3; ++i) {
		int how;
		if (i == 0) {
			how = shark_route/100;
			// cout << "hi : " << how << endl;;
		} else if (i == 1) {
			how = (shark_route / 10) % 10;
		} else if (i == 2) {
			how = shark_route % 10;
		}
		shark_r = shark_r + shark_dir_r[how];
		shark_c = shark_c + shark_dir_c[how];

		if (maps[shark_r][shark_c] > 0) {
			smell[shark_r][shark_c] = 2;
			maps[shark_r][shark_c] = 0;
			sea[shark_r][shark_c].clear();
		}

	}
}

void paste() {
	for (int i = 0; i < fish_vec_copy.size(); ++i) {
		int r = fish_vec_copy[i].r;
		int c = fish_vec_copy[i].c;
		sea[r][c].push_back(fish_vec_copy[i]);
		maps[r][c]++;
	}
}

void set_smell() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (smell[i][j] > 0) smell[i][j]--;
		}
	}
}

void set_fish_vec() {
	answer = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (maps[i][j] > 0) {
				answer += maps[i][j];
				for (int k = 0; k < maps[i][j]; ++k) {
					fish_vec.push_back(sea[i][j][k]);
				}
				sea[i][j].clear();
				maps[i][j] = 0;
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
		// maps[r][c]++;
	}

	
	cin >> shark_r >> shark_c;
	shark_r--;
	shark_c--;

	// for (int i = 0; i < 4; ++i) {
	// 	for (int j = 0; j < 4; ++j) {
	// 		visit[i][j] = false;
	// 	}
	// }

	for (int i = 0; i < S; ++i) {
		cout << i << endl;

		copy();
		// cout << "w";
		move_fish();
		cout << "after move" << endl;
		for (int r = 0; r < 4; ++r) {
			for (int c = 0; c < 4; ++c) {
				cout << maps[r][c] << " ";
			}cout << endl;
		}
				for (int r = 0; r < fish_vec.size(); r++) {
			cout << fish_vec[r].r << "," << fish_vec[r].c << " => " << fish_vec[r].d  << endl;
		}cout << endl;



		// cout << "smell before \n";
		// for (int r = 0; r < 4; ++r) {
		// 	for (int c = 0; c < 4; ++c) {
		// 		cout << smell[r][c] << " ";
		// 	}cout << endl;
		// }cout << endl;

		set_smell();
		// 		cout << "smell after \n";
		// for (int r = 0; r < 4; ++r) {
		// 	for (int c = 0; c < 4; ++c) {
		// 		cout << smell[r][c] << " ";
		// 	}cout << endl;
		// }cout << endl;


		// cout << "e";
		bool visit[4][4] = {false};
		// cout << "("  << shark_r << ", " << shark_c << ")" << endl;
		choose_route_shark(maps, visit, shark_r, shark_c, 0, 0);
		cout << shark_route << endl;
		move_shark();
		// cout << "after move shark" << endl;
		// for (int r = 0; r < 4; ++r) {
		// 	for (int c = 0; c < 4; ++c) {
		// 		cout << maps[r][c] << " ";
		// 	}cout << endl;
		// }cout << endl;
		paste();

		
				for (int r = 0; r < 4; ++r) {
			for (int c = 0; c < 4; ++c) {
				cout << maps[r][c] << " ";
			}cout << endl;
		}cout << endl;
		fish_vec.clear();
		fish_vec_copy.clear();
		shark_route = 555;
		die_fish_count = 0;
set_fish_vec();
					for (int r = 0; r < fish_vec.size(); r++) {
			cout << fish_vec[r].r << "," << fish_vec[r].c << " => " << fish_vec[r].d  << endl;
		}cout << endl;
		cout << "shark : " << shark_r << ", " << shark_c << endl;
		if (i > 0) start = false;

		// for (int r = 0; r < fish_vec.size(); r++) {
		// 	cout << fish_vec[r].r << "," << fish_vec[r].c << " => " << fish_vec[r].d  << endl;
		// }
	}
	cout << answer << '\n';
	// for (int i = 0; i < 4; i++) {
		// for (int j = 0; j < 4; j++) {
	// 		for (int k = 0; k < sea[i][j].size(); k++) {
	// 			cout << "(" << i << ", " << j << ") : " <<  sea[i][j].at(k).d << endl; 
	// 		}
	// 	}
	// }

	return 0;
}