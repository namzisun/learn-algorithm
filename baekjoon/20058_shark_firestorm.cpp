#include <iostream>
#include <cmath>

using namespace std;

int N, Q;
int map_size;
int maps[64][64];
int L[1000];

int first_row;
int last_row;
int first_col;
int last_col;

int a = 0;

void tornado(int l) {
	while(true) {
		if (map_size <= first_row || map_size <= first_col 
			|| map_size <= last_row || map_size <= last_row) break;
		first_row = l*a;
		last_row = first_row + l - 1;
		first_col = l*a;
		last_col = 
	}
}

void firestorm() {

}

int main() {

	cin >> N >> Q;
	map_size = pow(2, N);

	for (int i = 0; i < map_size; ++i) {
		for (int j = 0; j < map_size; ++j) {
			cin >> maps[i][j];
		}
	}
	
	for (int i = 0; i < Q; ++i) {
		cin >> L[i];
	}

	for (int i = 0; i < Q; ++i) {
		tornado(pow(2, L[i]));
	}

	return 0;
}