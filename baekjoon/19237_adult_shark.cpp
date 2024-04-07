#include <iostream>
#include <queue>
#include <utility>
#include <map>

using namespace std;

int sea[20][20];
int smell_map[20][20];

int result = 0;
int shark_count;
int left_shark_count;
int smell_time;
int map_size;

class Shark {
public:
	int priority[4][4];
	int number;
	int dir;
	int now_x, now_y;
	int next_x, next_y, next_dir;
	bool live;

	queue<pair<int,int>> smell;
	map<pair<int, int>, int> smell_map_list;
	
	

	Shark() {}
	Shark(int n, int x, int y) : number(n), now_x(x), now_y(y), live(true) {
		smell.push(make_pair(x,y));
		smell_map_list.insert({smell.front(), 1});
	}

	void setDirection(int d) {dir = d;}

	void setPriority(int p[4][4]) {
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				priority[i][j] = p[i][j];
			}
		}
	}

	void setSmell() {
		if (live == true) {
			if (smell.size() >= smell_time) {
				if (smell_map_list.find(smell.front()) != smell_map_list.end()) {
					smell_map_list.at(smell.front())--;
					if (smell_map_list.at(smell.front()) == 0)
						smell_map[smell.front().second][smell.front().first] = 0;
				}
				smell.pop();
			}
			smell.push(make_pair(next_x, next_y));
			if (smell_map_list.find(make_pair(next_x, next_y)) != smell_map_list.end())
				smell_map_list.at(make_pair(next_x, next_y))++;
			else
				smell_map_list.insert({make_pair(next_x, next_y), 1});
			smell_map[next_y][next_x] = number;
		} else {
			if (smell.size() >= smell_time) {
				if (smell.front().first > -1)
					if (smell_map_list.find(smell.front()) != smell_map_list.end()) {
					smell_map_list.at(smell.front())--;
					if (smell_map_list.at(smell.front()) == 0)
						smell_map[smell.front().second][smell.front().first] = 0;
				}
				smell.pop();
			}
			smell.push(make_pair(-1, -1));
		}
		
	}

	void setNew(int x, int y, int d) {
		this->next_x = x;
		this->next_y = y;
		this->next_dir = d;
	}

	void setNow() {
		now_x = next_x;
		now_y = next_y;
		dir = next_dir;
	}
	void toString() {
		if (live == true)
			cout << "number : " << number << ", (" << now_x << ", " << now_y << "), dir : " << dir << endl;
		else
			cout << "number : " << number << " is died" << endl;
		// for (int i = 0; i < 4; ++i) {
		// 	for (int j = 0; j < 4; ++j) {
		// 		cout << priority[i][j] << " ";
		// 	}
		// 	cout << endl;
		// }

		// for (int i = 0; i < smell.size(); ++i) {
		// 	cout << "(" << smell.front().first << ", " << smell.front().second << ")" << endl;
		// }

	}
};




Shark sharkArr[401];

int dir_x[4] = {0, 0, -1, 1};
int dir_y[4] = {-1, 1, 0, 0};

bool isValid(int x, int y) {
	if (x < 0 || x >= map_size) return false;
	if (y < 0 || y >= map_size) return false;
	return true;
}

void bfs() {
	int new_x = -1, new_y = -1, new_dir = -1;
	int flag_mysmell;

	for(int i = 1; i <= shark_count; ++i) {
		if (!sharkArr[i].live) continue;

		flag_mysmell = 0;
		for (int j = 0; j < 4; ++j) {
			new_dir = sharkArr[i].priority[sharkArr[i].dir-1][j];
			new_x = sharkArr[i].now_x + dir_x[new_dir-1];
			new_y = sharkArr[i].now_y + dir_y[new_dir-1];
			
			if (!isValid(new_x, new_y)) continue;
			if (smell_map[new_y][new_x] > 0 && smell_map[new_y][new_x] != sharkArr[i].number) continue; 
			if (smell_map[new_y][new_x] == sharkArr[i].number && flag_mysmell == 0) {
				sharkArr[i].setNew(new_x, new_y, new_dir);
				flag_mysmell = 1;
				continue;
			}
			if (smell_map[new_y][new_x] == 0) {
				sharkArr[i].setNew(new_x, new_y, new_dir);
				break;
			}
		}
	}


	for (int i = 1; i <= shark_count; ++i) {
		if (!sharkArr[i].live) {
			sharkArr[i].setSmell();
			continue;
		}
		sea[sharkArr[i].now_y][sharkArr[i].now_x] = 0;

		if (sea[sharkArr[i].next_y][sharkArr[i].next_x] == 0) {
			sea[sharkArr[i].next_y][sharkArr[i].next_x] = sharkArr[i].number;
			sharkArr[i].setSmell(); 
			sharkArr[i].setNow();
		} else {
			sharkArr[i].live = false;
			sharkArr[i].setSmell();
			cout << "!!!!! " << i << " shark is die now !!!" << endl;
			left_shark_count--;
		}
	}
}

int main() {

	int N, M, k;

	cin >> N >> M >> k;

	shark_count = M;
	left_shark_count = M;
	smell_time = k;
	map_size = N;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> sea[i][j];
			if (sea[i][j] != 0) {
				Shark shark = Shark(sea[i][j], j, i);
				sharkArr[sea[i][j]] = shark;
				smell_map[i][j] = sea[i][j];
			}
		}
	}

	int dir;
	for (int i = 0; i < M; ++i) {
		cin >> dir;
		sharkArr[i+1].setDirection(dir);
	}

	int p[4][4];
	for (int i = 0; i < M; ++i) {
		for (int j = 0; j < 4; ++j) {
			cin >> p[j][0] >> p[j][1] >> p[j][2] >> p[j][3];
		}
		sharkArr[i+1].setPriority(p);
	}

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << sea[i][j] << " ";
			} cout <<endl;
		}cout << endl << endl;

	int kkk = 1;
	while (left_shark_count > 1 && result <= 1000) {
				cout << endl << "========== " << kkk++ << " ============" << endl;
		bfs();
		result++;

		for (int i = 1; i <= M; ++i) {
			sharkArr[i].toString();
		}
		cout << endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << smell_map[i][j] << " ";
			} cout <<endl;
		}
	}

	if (result > 1000 && left_shark_count > 1) result = -1;

	cout << result << '\n';

	return 0;
}