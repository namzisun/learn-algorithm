#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int N, M;
int bucket[50][50];
int cloudMap[50][50];
int dir_r[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int dir_c[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
vector<pair<int, int> > magic;
vector<pair<int, int> > cloud;

bool isValid(int r, int c) {
	if (r < 0 || N <= r || c < 0 || N <= c) return false;
	return true;
}

void cloud_move(int d, int s) {
	for (int i = 0; i < cloud.size(); ++i) {
		int r = cloud[i].first;
		int c = cloud[i].second;
		int new_r = (r + dir_r[d] * s) % N;
		int new_c = (c + dir_c[d] * s) % N;
		while (new_r < 0) new_r += N;
		while (new_c < 0) new_c += N;

		// cout << "before : " << cloud[i].first << "," << cloud[i].second << endl;
		cloud[i] = make_pair(new_r, new_c);
		if (cloudMap[r][c] != -1) cloudMap[r][c] = 0;
		// cloudMap[new_r][new_c] = 1;
		bucket[new_r][new_c]++;
		cloudMap[new_r][new_c] = -1;
		// cout << "after : " << cloud[i].first << "," << cloud[i].second << endl;
	}
}

void water_copy_bug() {
	for (int i =0; i < cloud.size(); ++i) {
		int r = cloud[i].first;
		int c = cloud[i].second;
		int count = 0;
		for (int j =1; j < 8; j+=2) {
			int new_r = r + dir_r[j];
			int new_c = c + dir_c[j];

			if (!isValid(new_r, new_c)) continue;

			if (bucket[new_r][new_c] > 0) count++;
		}
		bucket[r][c] += count;
	}
}

void cloud_make() {
	for (int r = 0; r < N; ++r) {
		for (int c = 0; c < N; ++c) {
			if (bucket[r][c] >= 2 && cloudMap[r][c] != -1) {
				bucket[r][c] -= 2;
				cloudMap[r][c] = 1;
				cloud.push_back(make_pair(r, c));
			}
			if (cloudMap[r][c] == -1) cloudMap[r][c] = 0;
		}
	}
}

void print() {

		cout << endl << "bucket" << endl;
	for (int i =0 ; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << bucket[i][j] <<" ";
		}cout << endl;
	}
		cout << endl;
	cout << "cloud" << endl;
			for (int i =0 ; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << cloudMap[i][j] << " ";
		}cout << endl;
	}cout <<endl<< "==================="<<endl << endl;
}

int main() {
	int water = 0;
	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> bucket[i][j];
		}
	}
	for (int i = 0; i < M; ++i) {
		int d, s;
		cin >> d >> s;
		magic.push_back(make_pair(d-1, s));
	}
	cloudMap[N-1][0] = 1;
	cloudMap[N-1][1] = 1;
	cloudMap[N-2][0] = 1;
	cloudMap[N-2][1] = 1;
	cloud.push_back(make_pair(N-1, 0));
	cloud.push_back(make_pair(N-1, 1));
	cloud.push_back(make_pair(N-2, 0));
	cloud.push_back(make_pair(N-2, 1));

	for (int i = 0; i < M; ++i) {
		// cout << "^^^^^ : "  << cloud.size();
		cloud_move(magic[i].first, magic[i].second);
		// cout << "after cloud_move\n\n";
		// print();
		water_copy_bug();
		// cout << "after water_copy_bug\n\n";
		// print();
		cloud.clear();
		cloud_make();
		// cout << "after cloud_make\n\n";
		// print();
	}

	for (int i =0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			water += bucket[i][j];
		}
	}
	cout << water << '\n';
	// for (int i =0 ; i < N; i++) {
	// 	for (int j = 0; j < N; j++) {
	// 		cout << bucket[i][j];
	// 	}cout << endl;
	// }
	return 0;
}