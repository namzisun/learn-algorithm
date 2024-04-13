#include <iostream>


using namespace std;

int chess[40][40];
int L, N, Q;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

struct King {
	int i, d;
};

class Knight{
public :
	int r, c, h, w, k;

	Knight() {}
	Knight(int r, int c, int h, int w, int k)
	: r(r), c(c), h(h), w(w), k(k) {}

	void setNew(int r, int c) {
		this->r = r;
		this->c = c;
	}
};

Knight knights[30];
King king[100];

int main() {
	cin >> L >> N >> Q;

	for (int i =0; i < L: i++) {
		for (int j = 0; j < L; j++) {
			cin >> L[i][j];
		}
	}

	for (int i =0; i < N; i++) {
		int r, c, h, w, k;
		cin >> r >> c>> h >> w>> k;
		Knight kn = Knight(r, c, h, w, k);
		knights[i] = kn;
	}

	for (int i = 0; i < Q; i++) {
		int i, d;
		cin >> i >> d;
		King q = {i-1, d};
		king[i] = q;
	}

	return 0;
}