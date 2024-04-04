#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Shark {
public:
	int priority[4][4];
	int number;
	int dir;
	int x,y;

	queue<pair<int,int>> smell;

	Shark() {}
	Shark(int n, int x, int y) : number(n), x(x), y(y) {
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

	void setSmell(int x, int y) {
		if (smell.size() > 4) smell.pop();
		smell.push(make_pair(x,y));
	}

	// void toString() {
	// 	cout << "number : " << number << ", (" << x << ", " << y << ")" << endl;
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

int result = 0;
int shark_count;
int smell_time;
int map_size;

int map[20][20];
int smell_map[20][20];
Shark sharkArr[401];

void bfs() {
}

int main() {

	int N, M, k;

	cin >> N >> M >> k;

	// int map[N][N];
	// int smell_map[N][N];
	// Shark sharkArr[M+1];

	shark_count = M;
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

	for (int i = 1; i <= M; i++) {
		sharkArr[i].toString();
	}

	// for (int i = 0; i < N; ++i) {
	// 	for (int j = 0; j < N; ++j) {
	// 		cout << map[i][j];
	// 	}
	// 	cout << endl;
	// }


	// while (shark_count > 1 && result < 1000) {

	// }

	if (result >= 1000) result = -1;

	cout << result << '\n';

	return 0;
}