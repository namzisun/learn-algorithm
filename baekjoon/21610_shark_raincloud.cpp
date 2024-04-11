#include <iostream>
#include <queue>
#include <utility>

using namespace std;

int N, M;
int bucket[50][50];
int cloudMap[50][50];
int dir_r[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int dir_c[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
queue<pair<int, int> > magic;

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> bucket[i][j];
		}
	}
	for (int i = 0; i < M; ++i) {
		int d, s;
		cin >> d >> s;
		magic.push(make_pair(d-1, s));
	}
	cloudMap[N-1][0] = 1;
	cloudMap[N-1][1] = 1;
	cloudMap[N-2][0] = 1;
	cloudMap[N-2][1] = 1;

	// for (int i =0 ; i < N; i++) {
	// 	for (int j = 0; j < N; j++) {
	// 		cout << bucket[i][j];
	// 	}cout << endl;
	// }
}