#include <iostream>
#include <queue>
#include <utility>

using namespace std;

int N, M, K;
int maps[20][20] = {0, };
bool visit[20][20] = {false, };

int dir_r[4] = {0, 1, 0, -1};
int dir_c[4] = {1, 0, -1, 0};

int r = 0, c = 0, d = 0;

int score = 0;

int dice = 6;

int diceArr[6][4] = {
	{4, 5, 3, 2},
	{3, 1, 4, 6},
	{6, 5, 1, 2},
	{1, 5, 6, 2},
	{3, 6, 4, 1},
	{3, 2, 4, 5}
};

bool isValid(int r, int c) {
	if (r < 0 || c < 0 || N <= r || M <= c) return true;
	return false;
}

int setDice(int dir) {
	return diceArr[dice-1][dir];
}

void initVisit() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			visit[i][j] = false;
		}
	}
}

void setDir() {
	if (dice > maps[r][c]) d++;
	else if (dice < maps[r][c]) d--;
}

int countScore(int r, int c) {
	queue<pair<int, int> > q;
	q.push(make_pair(r, c));
	visit[r][c] = true;

	int number = maps[r][c];
	int count = 0;

	while (!q.empty()) {
		// cout << "hehe\n";
		int old_r = q.front().first;
		int old_c = q.front().second;
		q.pop();

		for (int i = 0; i < 4; ++i) {
			// cout << i << endl;
			int new_r = old_r + dir_r[i];
			int new_c = old_c + dir_c[i];

			if (!isValid(new_r, new_c) 
				|| visit[new_r][new_c]
				|| maps[new_r][new_c] != number) continue;
			
			visit[new_r][new_c] = true;
			q.push(make_pair(new_r, new_c));
			count++;
		}
	}
	return count;
}

void move_dice() {
	int new_r, new_c, new_d = d;
	for (int i = 0; i < 2; i++) {
		new_d %= 4;
			cout << "d :" << new_d << endl;

		new_r = r + dir_r[new_d];
		new_c = c + dir_c[new_d];
		if (isValid(new_r, new_c)) break;
		new_d+=2;
	}
	cout << "new_d : " << new_d << endl;
	r = new_r;
	c = new_c;
	d = new_d;

	cout << "1\n";
	dice = setDice(d);
	score += countScore(r, c);
	cout << "2\n";
	cout << "d :" << d << endl;
	cout << "3\n";
}


int main() {
	cin >> N >> M >> K;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cin >> maps[i][j];
		}
	}

	for (int i = 0; i < K; ++i) {
		initVisit();
		move_dice();
		cout << "d : " << d << endl;
		setDir();
		cout << "4\n";
		
	}

	cout << score << '\n';

	return 0;
}