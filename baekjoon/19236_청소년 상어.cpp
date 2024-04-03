#include <iostream>

using namespace std;

class Fish {
public:
	int num, dir, x, y;
	bool live;

	Fish() {}
	Fish(int num, int dir, int x, int y) : num(num), dir(dir), x(x), y(y), live(true) {}
	
	void change(int new_x, int new_y, int new_dir) {
		x = new_x;
		y = new_y;
		dir = new_dir;
	}
};


int answer = 0;

int map[4][4];
Fish fishArr[17];

int dir_x[8] = {0,-1,-1,-1,0,1,1,1};
int dir_y[8] = {-1,-1,0,1,1,1,0,-1};

void dfs(int map[][4], Fish fishArr[], int x, int y, int s) {
	// copy 생성
	int copy_map[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			copy_map[i][j] = map[i][j];
		}
	}

	Fish copy_fishArr[17];
	for (int i = 1; i < 17; i++) {
		copy_fishArr[i] = fishArr[i];
	}

	// 상어 물고기 잡아먹기
	int fishNum = copy_map[y][x];
	int shark_dir = copy_fishArr[fishNum].dir;
	copy_fishArr[fishNum].live = false;
	copy_map[y][x] = -1;

	s += fishNum;
	if (answer < s) answer = s;

	// 물고기 이동
	for (int l = 1; l <= 16; l++) {
		if (copy_fishArr[l].live == false) continue;

		int old_x = copy_fishArr[l].x;
		int old_y = copy_fishArr[l].y;
		int old_dir = copy_fishArr[l].dir;

		int new_x = old_x + dir_x[old_dir];
		int new_y = old_y + dir_y[old_dir];
		int new_dir = old_dir;

		while (new_x < 0 || new_x > 3 || new_y < 0 || new_y > 3 || (new_x == x && new_y == y)) {
			new_dir = (new_dir + 1) % 8;
			new_x = old_x + dir_x[new_dir];
			new_y = old_y + dir_y[new_dir];
		}

		if (copy_map[new_y][new_x] != -1) {
			int tmp = copy_map[new_y][new_x];

			copy_map[new_y][new_x] = l;
			copy_fishArr[l].change(new_x, new_y, new_dir);

			copy_map[old_y][old_x] = tmp;
			copy_fishArr[tmp].change(old_x, old_y, copy_fishArr[tmp].dir);

		} else {
			copy_map[new_y][new_x] = l;
			copy_map[old_y][old_x] = -1;

			copy_fishArr[l].change(new_x, new_y, new_dir);
		}
	}

	// 상어 이동
	for (int k = 1; k < 4; k++) {
		int new_x = x + dir_x[shark_dir] * k;
		int new_y = y + dir_y[shark_dir] * k;

		if (new_x < 0 || new_x > 3 || new_y < 0 || new_y > 3) break;

		if (copy_map[new_y][new_x] != -1)
			dfs(copy_map, copy_fishArr, new_x, new_y, s);
	}
}

int main() {
	// 입력값으로 이차원 배열 만들기
	int num,dir;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			cin >> num >> dir;
			map[i][j] = num;
			Fish fish = Fish(num ,dir-1, j, i);
			fishArr[num] = fish;
		}
	}

	// dfs 호출
	dfs(map, fishArr, 0, 0, 0);

	cout << answer << '\n';
	return 0;
}