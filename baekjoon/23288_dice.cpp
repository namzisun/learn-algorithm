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

int diceArr[6] = {2, 4, 1, 3, 5, 6};

// int diceArr[6][4] = {
// 	{4, 5, 3, 2},
// 	{4, 1, 3, 6},
// 	{2, 1, 5, 6},
// 	{5, 1 ,2, 6},
// 	{3, 1, 4, 6},
// 	{3, 5, 4, 2}
// };

bool isValid(int r, int c) {
	if (r < 0 || c < 0 || N <= r || M <= c) return false;
	return true;
}

void setDice() {
	int tmp[6] ={0, };

	if (d == 0) {
		tmp[0] = diceArr[0];
		tmp[1] = diceArr[5];
		tmp[2] = diceArr[1];
		tmp[3] = diceArr[2];
		tmp[4] = diceArr[4];
		tmp[5] = diceArr[3];
	} else if (d == 1) {
		tmp[0] = diceArr[5];
		tmp[1] = diceArr[1];
		tmp[2] = diceArr[0];
		tmp[3] = diceArr[3];
		tmp[4] = diceArr[2];
		tmp[5] = diceArr[4];
	} else if (d == 2) {
		tmp[0] = diceArr[0];
		tmp[1] = diceArr[2];
		tmp[2] = diceArr[3];
		tmp[3] = diceArr[5];
		tmp[4] = diceArr[4];
		tmp[5] = diceArr[1];
	} else if (d == 3) {
		tmp[0] = diceArr[2];
		tmp[1] = diceArr[1];
		tmp[2] = diceArr[4];
		tmp[3] = diceArr[3];
		tmp[4] = diceArr[5];
		tmp[5] = diceArr[0];
	}
	for (int i = 0; i < 6; ++i) {
		diceArr[i] = tmp[i];
	}

	dice = diceArr[5];
	// cout << "dice : " << dice << endl;
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
	while(d < 0) d += 4;
	// cout << "dir : " << d << endl;
}

int countScore() {
	queue<pair<int, int> > q;
	q.push(make_pair(r, c));
	visit[r][c] = true;

	int number = maps[r][c];
	int count = 1;
			// cout << "(" << r <<", " << c << ")" << endl;
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
			// cout << "(" << new_r <<", " << new_c << ")" << endl;
		}
	}
	return count * number;
}

void move_dice() {
	int new_r, new_c, new_d = d;
	for (int i = 0; i < 2; i++) {
		new_d %= 4;
			// cout << "d :" << new_d << endl;

		new_r = r + dir_r[new_d];
		new_c = c + dir_c[new_d];
	// cout << "new_d : " << new_d << endl;
	// cout << "new_r : " << new_r << endl;
	// cout << "new_c : " << new_c << endl; 
		if (isValid(new_r, new_c)) break;
		new_d+=2;
	}
	r = new_r;
	c = new_c;
	d = new_d;

		// 	cout << "r : " << r << endl;
		// cout << "c : " << c << endl;
		// cout << "d : " << d << endl;

	// cout << "1\n";
	// dice = setDice(d);
	// score += countScore(r, c);
	// cout << "2\n";
	// cout << "d :" << d << endl;
	// cout << "3\n";
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
		// cout << "r : " << r << endl;
		// cout << "c : " << c << endl;
		// cout << "d : " << d << endl;

		move_dice();
		// cout << "======= move dice =======\n";
		// cout << "r : " << r << endl;
		// cout << "c : " << c << endl;
		// cout << "d : " << d << endl;
		// cout << "maps : " << maps[r][c] << endl;
		// cout << "=========================\n";
		score += countScore();
		// cout << "r : " << r << endl;
		// cout << "c : " << c << endl;
		// cout << "d : " << d << endl;

		setDice();
		// cout << "r : " << r << endl;
		// cout << "c : " << c << endl;
		// cout << "d : " << d << endl;
		setDir();
		// cout << "4\n";
		
	}
		cout << score << '\n';


	return 0;
}