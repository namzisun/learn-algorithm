#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int N, M;
int maps[49][49];
int dir_r[4] = {-1, 1, 0, 0};
int dir_c[4] = {0, 0, -1, 1};
int row, col;
int tornado_r[4] = {0, 1, 0, -1};
int tornado_c[4] = {-1, 0, 1, 0};
int map_size;

int one = 0;
int two = 0;
int three = 0;

vector <pair<int, pair<int, int> > > marble;
vector <pair<int, int> > magic;

void print() {
	cout << endl;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << maps[i][j] << " ";
		}cout << endl;
	}
	cout << endl << endl;
	for (int i =0; i < marble.size(); i++) {
		cout << marble[i].first << " : (" << marble[i].second.first << ","  << marble[i].second.second << ")" << endl;
	}
}

bool isValid(int r, int c) {
	if (r < 0 || c < 0 || N<=r || N <=c) return false;
	return true;
}

void mapToVec() {
	int r = row;
	int c = col;
	int i = 2;
	int d = 0;
	int l = 0;

	while (true) {
		int k = 0;
		while (k < i/2) {
			r += tornado_r[d];
			c += tornado_c[d];
			// cout << "(" << r << "," << c << ")" << endl;
			if (!isValid(r, c)) {
				r -= tornado_r[d];
				c -= tornado_c[d];
				break;
			}
			int number = maps[r][c];
			marble.push_back(make_pair(number, make_pair(r, c)));
			maps[r][c] = l++;
			k++;
		}
		i++;
		d = (d+1)%4;
		if (r == 0 && c == 0) break;
	}
}

void ice(int d, int s) {
	for (int i = 1; i <= s; ++i) {
		int new_r = row + dir_r[d]*i;
		int new_c = col + dir_c[d]*i;
		if (!isValid(new_r, new_c)) break;
		int index = maps[new_r][new_c];
		maps[new_r][new_c] = 0;
		marble[index] = make_pair(0, make_pair(new_r, new_c));
	}
}

void bomb() {
	vector<pair<int, pair<int,int>>>::iterator it = marble.begin();
	bool bomb = false;
	
	do {
		if (it->first > 0) {
			int count = 1;
			int number = it->first;
			
			int m = 1;
			while(true) {
				// cout << "hh\n";
				if ((it+m)->first == 0 && (it+m) != marble.end()) {
					m++;
					continue;
				}
				if ((it+m)->second.first == 0 && (it+m)->second.second == 0) break;
				if ((it+m)->first != number) break;
				count++;
				m++;
			}
			if (count >= 4) {
				while (m > 0) {
					it->first = 0;
					it++;
					m--;
					bomb = true;
				}
				it--;
				if (number == 1) one += count;
				else if (number == 2) two += count;
				else if (number == 3) three += count;
			}
		}
		it++;
		if (it == marble.end() && bomb == false) break;
		else if (it == marble.end() && bomb == true) {
			it = marble.begin();
			bomb = false;
		}

	} while(true);
}

void vecToMap() {

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			maps[i][j] = 0;
		}
	}

	int i = 2;
	int r = row;
	int c = col;
	int d = 0;
	int l = 0;
	maps[row][col] = -1;

	for (int v = 0; v  < marble.size(); ++v) {

		if (marble[v].first == 0) continue;
		int k = 0;
		while (k < i/2) {
			if (v == marble.size()) return;
			if (marble[v].first == 0){
				v++;
				continue;
			}
			r += tornado_r[d];
			c += tornado_c[d];
			// cout << "(" << r << "," << c << ")" << endl;
			if (!isValid(r, c)) {
				r -= tornado_r[d];
				c -= tornado_c[d];
				break;
			}
			// cout << "(" << r << "," << c << ") : ";
			// cout << marble[v].first << endl;

			maps[r][c] = marble[v++].first;
			// int number = maps[r][c];
			// marble.push_back(make_pair(number, make_pair(r, c)));
			// maps[r][c] = l++;
			// cout << "k : " << k << ", i/2 : " << i/2 << endl;
			k++;

		}
		v--;
		i++;
		d = (d+1)%4;
		// cout << "d : " << d << endl;
	}
}

void change() {
	vector<pair<int, pair<int, int>>> tmp;
	int number;
	int count;
	for (int i =0; i < marble.size(); ++i) {
		if (marble[i].first == 0) continue;
		number = marble[i].first;
		count = 1;
		for (int j = i+1; j < marble.size(); ++j) {
			if (marble[j].first == 0) {
				i++;
				continue;
			}
			if (marble[j].first != number) break;
			count++;
			i++;
		}
		cout << "count : " << count << ", number : " << number << endl;
		if (tmp.size() < map_size - 1)
			tmp.push_back(make_pair(count, make_pair(0,0)));
		if (tmp.size() < map_size - 1)
			tmp.push_back(make_pair(number, make_pair(0, 0)));
	}

	marble.clear();
	marble = tmp;
}


int main() {

	cin >> N >> M;
	map_size = N*N -1;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> maps[i][j];
		}
	}

	for (int i = 0; i < M; ++i) {
		int d, s;
		cin >> d >> s;
		magic.push_back(make_pair(d-1, s));
	}

	row = col = (N+1)/2 -1;
	maps[row][col] = -1;
	

	for (int i = 0; i < M; ++i) {
		mapToVec();
		// print();
		ice(magic[i].first, magic[i].second);
		// print();
		bomb();
		change();
		// vecToMap();
		// print();
		// marble.clear();
		// mapToVec();
		// print();
		
	}
	// vector<pair<int, pair<int, int>>> tmp;
	// tmp.push_back(make_pair(1, make_pair(0,0)));
	// marble.clear();
	// marble = tmp;
	// cout << marble[1].first << endl;

	int answer = one + 2 * two + 3 * three;
	cout << answer << '\n';

	return 0;
}