#include <iostream>
#include <map>
#include <utility>
#include <set>

using namespace std;

int N, M, k;
int stage[50][50];

int dir_r[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dir_c[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int sumM = 0;
int map_key = 0;

set<pair<int, int> > moreThanOneFireball;

class Fireball {
public:
	int r, c, m, d, s;

	Fireball(){}
	
	Fireball(int r, int c, int m, int s, int d)
	: r(r), c(c), m(m), d(d), s(s) {
		stage[r][c]++;
	}

	void toString() {
		cout << "(" << r << ", " << c << "), m = " << m << ", s = " << s << ", d = " << d <<endl;
	}

	void setNewPosition() {
		stage[r][c]--;
		// cout << "set old " << r << ", " << c << endl;
		r = (r + dir_r[d]*s) % N;
		// cout << "1\n";
		c = (c + dir_c[d]*s) % N;
		// cout << "2\n";
		// cout << r << ", " << c << endl;
		while (r < 0) r += N;
		while (c < 0) c += N;
		stage[r][c]++;
		// cout << "set new " << r << ", " << c << endl;
		if (stage[r][c] > 1) moreThanOneFireball.insert(make_pair(r, c));

	}
};

map<int, Fireball> fireballs;

void moveFireball() {
	for (map<int, Fireball>::iterator it = fireballs.begin(); it != fireballs.end(); it++) {
		it->second.setNewPosition();
	}
}

void seperateFireball() {
	set<pair<int, int> >::iterator it_s = moreThanOneFireball.begin();
	while (it_s != moreThanOneFireball.end()) {
		// cout << "set\n";
		pair<int, int> key = *it_s;
		// cout << key.first << ", " << key.second << endl;
		int M = 0;
		int S = 0;
		int D;
		int odd = 0;
		int even = 0;
		int count = 0;
		for (map<int, Fireball>::iterator it = fireballs.begin(); it != fireballs.end();) {
			// cout << "map\n";
			if (it->second.r == key.first && it->second.c == key.second) {
				// cout << "if when it->first == key\n";
				M += it->second.m;
				S += it->second.s;
				if (it->second.d % 2 == 0) even++;
				else odd++;

				fireballs.erase(it++);
				stage[key.first][key.second]--;
				count++;
			} 
			else it++;
		}
		if (count > 1) {
			// cout << "if when count > 1\n";
			M = M/5;
			S = S/count;
			if (M == 0) continue;
			if (even == 0 || odd == 0) {
				D = 0;
				for (int i = 0; i < 4; i++) {
					Fireball f = Fireball(key.first, key.second, M, S, D);
					// cout << map_key << ": " ;
					fireballs.insert({map_key++, f});
					
					// f.toString();
					D+=2;
				}
			} else {
				D = 1;
				for (int i = 0; i < 4; i++) {
					Fireball f = Fireball(key.first, key.second, M, S, D);
					// cout << map_key << ": " ;
					fireballs.insert({map_key++, f});
					// f.toString();
					D+=2;
				}
			}
		}
		it_s++;
	}
	moreThanOneFireball.clear();
}

int main() {
	cin >> N >> M >> k;

	int r, c, m, s, d;
	for (int i = 0; i < M; ++i) {
		cin >> r >> c >> m >> s >> d;
		Fireball f = Fireball(r-1, c-1, m, s, d);
		fireballs.insert({map_key++, f});
		// stage[r-1][c-1]++;
	}

	for (int i = 0; i < k; ++i) {
		moveFireball();
		seperateFireball();
	}

	for (map<int, Fireball>::iterator it = fireballs.begin(); it != fireballs.end(); it++) {
		sumM += it->second.m;
	}

	cout << sumM << '\n';

	// for (int i = 0; i < N; i++)
	//  {
	// 	for (int j = 0; j < N; j++) {
	// 		cout << stage[i][j] << " ";
	// 	} cout << endl;
	//  }
	// for (map<int,Fireball>::iterator it = fireballs.begin(); it != fireballs.end(); it++) {
	// 	cout << "("  << it->second.r << ", " << it->second.c<< ") : ";
	// 	it->second.toString();
	// }cout << endl;
	return 0;
}