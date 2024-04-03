#include <iostream>
#include <queue>

using namespace std;

int answer = 0;
int N;
int sea[22][22];
int baby_x, baby_y;
int baby_size = 2;

bool help = false;
bool eat = false;

int pos_x[] = {0, -1, 1, 0};
int pos_y[] = {-1, 0, 0, 1};

void bfs() {
	bool visit[22][22] = {0};

	queue<pair<pair<int, int>, int>> q;
	q.push(make_pair(make_pair(baby_x, baby_y), 0));
	visit[baby_y][baby_x] = true;

	int time_to_eat;
	// int k  =0;
	while(!q.empty()) {
		int shark_x = q.front().first.first;
		int shark_y = q.front().first.second;
		int move = q.front().second;

		if (sea[shark_y][shark_x] > 0 && sea[shark_y][shark_x] < baby_size && time_to_eat == move) {
			if ((baby_y > shark_y) || (baby_y == shark_y && baby_x > shark_x)) {
				baby_y = shark_y;
				baby_x = shark_x;
				continue;
			}
		}

		q.pop();
		// cout << k++ << endl;
		// cout << "상어 좌표 (" << shark_x << ", " << shark_y << ")" << endl;
		for (int i = 0; i < 4; i++) {
			int x = shark_x + pos_x[i];
			int y = shark_y + pos_y[i];
			// cout << "현재 좌표 (" << x << ", " << y << ")" << endl;

			if (0 <= x && x < N && 0 <= y && y < N && !visit[y][x]) {
				// cout << "유효한 좌표 (" << x << ", " << y << ")";
				int other_fish = sea[y][x];
				if (other_fish <= baby_size) {
					if (0 < other_fish && other_fish < baby_size && !eat) {
						// cout << " => 먹음";
						eat = true;
						baby_x = x;
						baby_y = y;
						time_to_eat = move + 1;
						answer += time_to_eat;
					} else {
						// cout << " => 못먹음";
						visit[y][x] = true;
						q.push(make_pair(make_pair(x, y), move + 1));
					}
				}
				// cout << endl;
			}
		}
	}
}

int main() {
	cin >> N;

	int fish;

	for(int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> fish;
			if (fish == 9) {
				baby_x = j;
				baby_y = i;
				fish = 0;
			}
			sea[i][j] = fish;
		}
	}

	// for (int i = 0; i < N; i++) {
	// 	for (int j =0; j < N; j++) {
	// 		cout << sea[i][j] << ' ';
	// 	}
	// 	cout << '\n';
	// }


	int ate_fish_count = 0;
	while(!help) {
		bfs();

		if (eat) {
			eat = false;
			ate_fish_count++;
			sea[baby_y][baby_x] = 0;
			if (ate_fish_count == baby_size) {
				baby_size++;
				ate_fish_count = 0;
			}
		} else  {
			help = true;
		}
	}

	cout << answer << '\n';
	return 0;
}