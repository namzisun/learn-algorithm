#include <iostream>
#include <map>
#include <utility>

using namespace std;

int N, M, k;
int stage[50][50];

int dir_r[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dir_c[8] = {0, 1, 1, 1, 0, -1, -1, -1};

class Fireball {
public:
	int r, c, m, d, s;

	Fireball(){}
	
	Fireball(int r, int c, int m, int s, int d)
	: r(r), c(c), m(m), d(d), s(s) {}

	void toString() {
		cout << "(" << r << ", " << c << "), m = " << m << ", s = " << s << ", d = " << d <<endl;
	}
};

map<pair<int, int>, Fireball> fireballs;

int makeRPosition(int r, int d, int s) {
	int new_r;

	new_r = (r + dir_r[d]*s) % N;

	return new_r;
}

int makeCPosition(int c, int d, int s) {
	int new_c;

	new_c = (c + dir_c[d]*s) % N;

	return new_c;
}

int main() {
	cin >> N >> M >> k;

	int r, c, m, s, d;
	for (int i = 0; i < M; ++i) {
		cin >> r >> c >> m >> s >> d;
		Fireball f = Fireball(r-1, c-1, m, s, d);
		fireballs.insert({make_pair(r-1, c-1), f});
		stage[r-1][c-1]++;
	}

	for (int i = 0; i < N; i++)
	 {
		for (int j = 0; j < N; j++) {
			cout << stage[i][j] << " ";
		}cout << 
	 }
	// for (map<pair<int,int>,Fireball>::iterator it = fireballs.begin(); it != fireballs.end(); it++) {
	// 	cout << "("  << it->first.first << ", " << it->first.second << ") : ";
	// 	it->second.toString();
	// }
}