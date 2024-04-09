#include <iostream>
#include <vector>

using namespace std;

int N, M, k;

int dir_r[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dir_c[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int sumM = 0;



class Fireball {
public:
	int r, c, m, d, s;

	Fireball(){}
	
	Fireball(int r, int c, int m, int s, int d)
	: r(r), c(c), m(m), d(d), s(s) {}

	void toString() {
		cout << "(" << r << ", " << c << "), m = " << m << ", s = " << s << ", d = " << d <<endl;
	}

	void setNewPosition() {
		// cout << "set old " << r << ", " << c << endl;
		r = (r + dir_r[d]*s) % N;
		// cout << "1\n";
		c = (c + dir_c[d]*s) % N;
		// cout << "2\n";
		// cout << r << ", " << c << endl;
		while (r < 0) r += N;
		while (c < 0) c += N;
		// cout << "set new " << r << ", " << c << endl;

	}
};

vector<Fireball> fireballs;
vector<Fireball> fireballMap[50][50];

void moveFireball() {
	for (int i = 0; i < fireballs.size(); ++i) {
		fireballs.at(i).setNewPosition();
		Fireball f = Fireball(fireballs.at(i));
		fireballMap[f.r][f.c].push_back(f);
	}
}

void seperateFireball() {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			if (fireballMap[i][j].empty()) continue;
			else if (fireballMap[i][j].size() == 1) 
				fireballs.push_back(fireballMap[i][j].at(0));
			else {
				int r = fireballMap[i][j].at(0).r;
				int c = fireballMap[i][j].at(0).c;
				int m = 0, s = 0;
				int odd = 0, even = 0;
				for(int l = 0; l < fireballMap[i][j].size(); ++l) {
					m += fireballMap[i][j].at(l).m;
					s += fireballMap[i][j].at(l).s;
					if (fireballMap[i][j].at(l).d % 2 == 0) even++;
					else odd++;
				}
				if (m/5 > 0) {
					if (even == 0 || odd == 0) {
						for (int l = 0; l < 8; l += 2) {
							Fireball f = Fireball(r, c, m/5, s/fireballMap[i][j].size(), l);
							fireballs.push_back(f);
						}
					} else {
						for (int l = 1; l < 8; l += 2) {
							Fireball f = Fireball(r, c, m/5, s/fireballMap[i][j].size(), l);
							fireballs.push_back(f);
						}
					}
				}
			}
			fireballMap[i][j].clear();
		}
	}
}


int main() {
	cin >> N >> M >> k;

	int r, c, m, s, d;
	for (int i = 0; i < M; ++i) {
		cin >> r >> c >> m >> s >> d;
		Fireball f = Fireball(r-1, c-1, m, s, d);
		fireballs.push_back(f);
	}

	for (int i = 0; i < k; ++i) {
		moveFireball();
		fireballs.clear();
		seperateFireball();
	}

	for (int i = 0; i < fireballs.size(); ++i) {
		sumM += fireballs.at(i).m;
	}


	cout << sumM << '\n';

	return 0;
}