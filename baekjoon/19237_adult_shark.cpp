#include <iostream>
#include <queue>
#include <utility>

using namespace std;

int map[20][20];
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
	int next_x, next_y;
	bool live;

	queue<pair<int,int>> smell;

	Shark() {}
	Shark(int n, int x, int y) : number(n), now_x(x), now_y(y), live(true) {
		smell.push(make_pair(x,y));
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
				// cout << "set smell : " << smell.front().first << ", " << smell.front().second << endl;
				smell_map[smell.front().second][smell.front().first] = 0;
				smell.pop();
			}
			smell.push(make_pair(next_x, next_y));
			// cout << "next : " << next_x << ", " << next_y << endl;
			smell_map[next_y][next_x] = number;
			cout << "set smell : (" << next_x << ", " << next_y << ") " <<  smell_map[next_y][next_x] <<endl;
		} else {
			cout << "ㅇㅙ 이이거  안돼녀교" << endl;
			if (smell.size() >= smell_time) {
				// cout << "set smell : " << smell.front().first << ", " << smell.front().second << endl;
				if (smell.front().first > -1)
					smell_map[smell.front().second][smell.front().first] = 0;
				smell.pop();
			}
			smell.push(make_pair(-1, -1));
			cout << "set flase smell : (" << smell.back().first << ", " << smell.back().second << ") " <<  smell_map[smell.back().second][smell.back().first] <<endl;

			// cout << "next : " << next_x << ", " << next_y << endl;
			// smell_map[next_y][next_x] = number;
		}
		
	}

	void setNew(int x, int y, int d) {
		this->next_x = x;
		this->next_y = y;
		this->dir = d;
	}

	void setNow() {
		// 왜 여기서 세그폴트가 나지?????????????????
		now_x = next_x;
		now_y = next_y;
	}
	// void toString() {
	// 	cout << "number : " << number << ", (" << now_x << ", " << now_y << ")" << endl;
	// 	for (int i = 0; i < 4; ++i) {
	// 		for (int j = 0; j < 4; ++j) {
	// 			cout << priority[i][j] << " ";
	// 		}
	// 		cout << endl;
	// 	}

	// 	for (int i = 0; i < smell.size(); ++i) {
	// 		cout << "(" << smell.front().first << ", " << smell.front().second << ")" << endl;
	// 	}
	// }
};




Shark sharkArr[401];

int dir_x[4] = {0, 0, -1, 1};
int dir_y[4] = {-1, 1, 0, 0};

bool isValid(int x, int y) {
	if (x < 0 || x >= map_size) return false;
	if (y < 0 || y >= map_size) return false;
	return true;
}

// bool isSmell(int x, int y, int sharkNumber) {
// 	if (map[y][x] == 0 
// 		&& smell_map[y][x] != sharkNumber 
// 		&& smell_map[y][x] > 0) 
// 		return false;
// 	return true;
// }

void bfs() {
	// 상어 이동하기(현재 dir 보고 priority에 접근 -> dir_x[prioirty+1] -> 가능/불가능)
	int new_x = -1, new_y = -1, new_dir = -1;
	int flag_mysmell;

	for(int i = 1; i <= shark_count; ++i) {
		if (!sharkArr[i].live) continue;

		flag_mysmell = 0;
		// 상어 이동할 위치 정하기
		// next 계산하는게 잘못됨. 두번째 사이클부터 바로 틀린다. dir 때문인가?
		for (int j = 0; j < 4; ++j) {
			new_dir = sharkArr[i].priority[sharkArr[i].dir-1][j];
			new_x = sharkArr[i].now_x + dir_x[new_dir-1];
			new_y = sharkArr[i].now_y + dir_y[new_dir-1];
			cout << sharkArr[i].number  << ": " << new_x<< ", " << new_y << endl;
			
			if (!isValid(new_x, new_y)){ 
				cout << "aaaaaaaaa" << endl;
				continue;}
			if (smell_map[new_y][new_x] > 0 && smell_map[new_y][new_x] != sharkArr[i].number) {
				cout << "smell : " << smell_map[new_y][new_x] << ", number : " << sharkArr[i].number << endl;
				cout << "bbbbbbbbbb" << endl; continue;} // 왜 여기서 탈출하지????
			if (smell_map[new_y][new_x] == sharkArr[i].number && flag_mysmell == 0) {
				sharkArr[i].setNew(new_x, new_y, new_dir);
				flag_mysmell = 1;
				cout << "here" << endl;
				continue;
			}
			if (smell_map[new_y][new_x] == 0) {
				sharkArr[i].setNew(new_x, new_y, new_dir);
				break;
			}
		}
	}

	for (int i = 1; i <= shark_count; ++i) {
		cout << sharkArr[i].number << " : (" << sharkArr[i].next_x << ", " << sharkArr[i].next_y << "), dir : " << sharkArr[i].dir << endl; 
	}

	for (int i = 1; i <= shark_count; ++i) {
		if (!sharkArr[i].live) {
			cout << " 너 죽은애야 제발" << endl;
			sharkArr[i].setSmell();
			continue;
		}
		// 상어 번호순으로 new로 옮김. 이떄 내가 갈 자리에 상어가 있으면 죽음
		map[sharkArr[i].now_y][sharkArr[i].now_x] = 0;
		// cout << "now : " << sharkArr[i].now_x << ", " << sharkArr[i].now_y << endl; // 이렇게 값에는 접근이 됨
		// cout << "next : " << sharkArr[i].next_x << ", " << sharkArr[i].next_y << endl;
		
		if (map[sharkArr[i].next_y][sharkArr[i].next_x] == 0) {
			map[sharkArr[i].next_y][sharkArr[i].next_x] = sharkArr[i].number;
			sharkArr[i].setSmell(); // 여기서 세그폴트 => next 계산이 잘못됨 => next를 now로 덮어씌우는 작업이 없어서
			// 이 두개가 왜 세그폴트? => 아. now를 덮어 씌웠을 때 map에 접근하는 과정에서 세그폴트 나는 듯. 그니까 setNow에는 문제가 없을 것 같은데
			sharkArr[i].setNow();
		} else {
			cout << "오잉" << endl;
			sharkArr[i].live = false;
			sharkArr[i].setSmell();
			left_shark_count--;
		}
	}
}

int main() {

	int N, M, k;

	cin >> N >> M >> k;

	// int map[N][N];
	// int smell_map[N][N];
	// Shark sharkArr[M+1];

	shark_count = M;
	left_shark_count = M;
	smell_time = k;
	map_size = N;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> map[i][j];
			if (map[i][j] != 0) {
				Shark shark = Shark(map[i][j], j, i);
				sharkArr[map[i][j]] = shark;
				smell_map[i][j] = map[i][j];
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

	// for (int i = 1; i <= M; i++) {
	// 	sharkArr[i].toString();
	// }

	// for (int i = 0; i < N; ++i) {
	// 	for (int j = 0; j < N; ++j) {
	// 		cout << map[i][j];
	// 	}
	// 	cout << endl;
	// }

	while (left_shark_count > 1 && result < 1000) {
		bfs();
		result++;

		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				cout << smell_map[i][j];
			}
			cout << endl;
		}
		cout << endl << endl << endl;
	}

	if (result >= 1000) result = -1;

	cout << result << '\n';

	return 0;
}