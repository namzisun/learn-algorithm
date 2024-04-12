#include <iostream>
#include <deque>
#include <vector>

using namespace std;

#define MAX 110
deque<int> bowl[MAX];

int N, K;

int dir_r[2] = {0, -1};
int dir_c[2] = {1, 0};

bool check() {
	int min = 10000;
	int max = 0;
	for (int i = 0; i < bowl[0].size(); i++) {
		if (min > bowl[0][i]) min = bowl[0][i];
		if (max < bowl[0][i]) max = bowl[0][i];
	}

	int d = max - min;
	if (d > K) return false;
	else return true;
}

void addFish() {
	int min = 10000;
	vector<int> vec;

	for (int i =0; i < bowl[0].size(); ++i) {
		if (bowl[0][i] < min) {
			min = bowl[0][i];
			vec.clear();
			vec.push_back(i);
		} else if (bowl[0][i] == min) {
			vec.push_back(i);
		}
	}

	for (auto i : vec) {
		bowl[0][i]++;
	}
}

bool canBuild(int w, int h) {
	if (bowl[0].size() - w < h) return false;
	return true;
}

int buildBowl() {
	int width = 1;
	int height = 1;
	bool flag = false;

	while (true) {
		if (canBuild(width, height) == false) break;

		int tmpWidth = width;

		for (int i = 0; i < width; i++, tmpWidth--) {
			int idx = 0;
			for (int j = 0; j < height; j++, idx++) {
				bowl[tmpWidth].push_back(bowl[idx][i]);
			}
		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				bowl[i].pop_front();
			}
		}

		if (flag == false) {
			height++;
			flag = true;
		} else {
			width++;
			flag = false;
		}
	}
	return height;
}

void buildBowl2() {
	int n = bowl[0].size();

	for (int i = 0; i < n/2; i++) {
		bowl[1].push_front(bowl[0][i]);
	}

	for (int i =0; i < n/2; i++) {
		bowl[0].pop_front();
	}

	n = bowl[0].size();
	for (int i = 0; i < n/2; i++) {
		bowl[2].push_front(bowl[1][i]);
		bowl[3].push_front(bowl[0][i]);
	}

	for (int i =0; i < n/2; i++) {
		bowl[1].pop_front();
		bowl[0].pop_front();
	}
}

void spreadBowl(int height) {
	int width = bowl[height - 1].size();
	int size = bowl[0].size();
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			bowl[0].push_back(bowl[j][i]);
		}
	}

	for (int i = 1; i < height; i++) {
		bowl[i].clear();
	}

	for (int i = width; i < size; i++) {
		bowl[0].push_back(bowl[0][i]);
	}

	for (int i = 0; i < size; i++) {
		bowl[0].pop_front();
	}
}

void adjustFish(int height) {
	deque<int> tmpbowl[MAX];
	for (int i = 0; i < height; i++) {
		tmpbowl[i] = bowl[i];
	}

	for (int i = height - 1; i >= 0; i--) {
		for (int j = 0; j < tmpbowl[i].size(); j++) {
			int r = i;
			int c = j;
			int num = tmpbowl[r][c];

			for (int k = 0; k < 2; k++) {
				int new_r = r + dir_r[k];
				int new_c = c + dir_c[k];

				if (0 <= new_r && new_c < tmpbowl[i].size()) {
					int num2 = tmpbowl[new_r][new_c];
					int diff = abs(num - num2) / 5;
					if (diff > 0) {
						if (num > num2) {
							bowl[r][c] -= diff;
							bowl[new_r][new_c] += diff;
						} else {
							bowl[r][c] += diff;
							bowl[new_r][new_c] -= diff;
						}
					}
				}
			}
		}
	} 
}

int main() {

	cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		int fish;
		cin >> fish;
		bowl[0].push_back(fish);
	}

	int answer = 0;
	while(true) {
		if (check()) break;

		addFish();
		int height = buildBowl();
		adjustFish(height);
		spreadBowl(height);
		buildBowl2();
		adjustFish(4);
		spreadBowl(4);
		answer++;
	}
	cout << answer << '\n';
	return 0;
}