#include <iostream>


using namespace std;

int chess[41][41];
int chessKignht[41][41];
int L, N, Q;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

struct King {
	int i, d;
};

class Knight{
public :
	int number, r, c, h, w, k;

	Knight() {}
	Knight(int n, int r, int c, int h, int w, int k)
	: number(n), r(r), c(c), h(h), w(w), k(k) {
		setRectangle();
	}

	void setNew(int r, int c) {
		this->r = r;
		this->c = c;
	}

	void setRectangle() {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				chessKignht[r+i][c+j] = number;
			}
 		}
	}
};

Knight knights[31];
King king[101];

int main() {
	cin >> L >> N >> Q;

	for (int i =1; i <= L; i++) {
		for (int j = 1; j <= L; j++) {
			cin >> chess[i][j];
		}
	}

	for (int i =1; i < N+1; i++) {
		int r, c, h, w, k;
		cin >> r >> c>> h >> w>> k;
		Knight kn = Knight(i, r, c, h, w, k);
		knights[i] = kn;
	}

	for (int k = 0; k < Q; k++) {
		int i, d;
		cin >> i >> d;
		King q = {i, d};
		king[i] = q;
	}

	// for (int i =1; i <= L; i++) {
	// 	for (int j = 1; j <= L; j++) {
	// 		cout << chessKignht[i][j] << " ";
	// 	}cout << endl;
	// }

	return 0;
}