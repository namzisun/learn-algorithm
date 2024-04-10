#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <map>

using namespace std;

int dir_r[4] = {-1, 1, 0, 0};
int dir_c[4] = {0, 0, -1, 1};
int stage[20][20];
int N, M;
int score = 0;

int key =0;
int blockgroup = 0;
bool visit[20][20];

class BlockGroup {
public:
	vector<pair<int, int> > vec;
	vector<pair<int, int> > normalVec;
	vector<pair<int, int> > rainbowVec;
	int normal = 0, rainbow = 0;
	pair<int, int> standard;
	int size = 0;
	int row_min = 20, col_min = 20;

	void pushBlock(int r, int c) {
		int color = stage[r][c];

		vec.push_back(make_pair(r, c));
		size++;

		if (color > 0) {
			normalVec.push_back(make_pair(r, c));
			normal++;
		} else if (color == 0) {

			// cout << "( " << r << ", " << c << ") rainbow\n";
			rainbowVec.push_back(make_pair(r, c));
			rainbow++;
		}
	}

	void setMin() {
		for (vector<pair<int, int> >::iterator it = normalVec.begin(); it != normalVec.end(); it++) {
			if (it->first <= row_min) row_min = it->first;
			if (it->second <= col_min) col_min = it->second;
		}
	}

	void setStandard() { 
		setMin();
		queue<pair<int, int> > q;

		for (vector<pair<int, int> >::iterator it = normalVec.begin(); it != normalVec.end(); it++) {
			if (it->first == row_min) q.push(*it);
		}

		if (q.size() == 1) {
			standard = q.front();
			return ;
		}

		while (q.size() > 0) {
			if (q.front().second == col_min) {
				standard = q.front();
				return ;
			}
			q.pop();
		}
	}

	void clearRainbow() {
		for (vector<pair<int, int> >::iterator it = rainbowVec.begin(); it != rainbowVec.end(); it++) {
			visit[it->first][it->second] = false;
		}
	}

	void toString() {
		for (vector<pair<int, int> >::iterator it = vec.begin(); it != vec.end(); it++) {
			cout << "(" << it->first << "," << it->second << ")" << endl;
		}
	}
};


map<int, BlockGroup> blockGroupMap;
BlockGroup maxBlockGroup[2];

void rotate() {

}


int findMax(int x, int max) {
	if (max < x) return x;
	else return max;
}

bool isValid(int r, int c) {
	if (r < 0 || r >= N || c < 0 || c >= N) return false;
	return true;
}

void findMaxBlockGroup() {
	if (blockGroupMap.size() > 1) {
		// cout << "1\n";
		int size_max = 0;
		for (map<int, BlockGroup>::iterator it = blockGroupMap.begin(); it!= blockGroupMap.end(); it++) {
			// cout << "size : " << it->second.size << ", max :" <<size_max <<endl;
			size_max = findMax(it->second.size, size_max);
		}

// cout << "2 : " << size_max << endl;
		for (map<int, BlockGroup>::iterator it = blockGroupMap.begin(); it != blockGroupMap.end();) {
			if (it->second.size == size_max) it++;
			else blockGroupMap.erase(it++);
		}
	}

	if (blockGroupMap.size() > 1) {
		// cout << "3\n";
		int rainbow_max = 0;
		for (map<int, BlockGroup>::iterator it = blockGroupMap.begin(); it!= blockGroupMap.end(); it++) {
			rainbow_max = findMax(it->second.rainbow, rainbow_max);
		}
// cout << "4\n";
		for (map<int, BlockGroup>::iterator it = blockGroupMap.begin(); it!= blockGroupMap.end();) {
			if (it->second.rainbow == rainbow_max) it++;
			else blockGroupMap.erase(it++);
		}
	}

	if (blockGroupMap.size() > 1) {
		// cout << "5\n";
		int row_max = 0;
		for (map<int, BlockGroup>::iterator it = blockGroupMap.begin(); it!= blockGroupMap.end(); it++) {
			row_max = findMax(it->second.row_min, row_max);
		}
// cout << "6\n";
		for (map<int, BlockGroup>::iterator it = blockGroupMap.begin(); it!= blockGroupMap.end();) {
			if (it->second.row_min == row_max) it++;
			else blockGroupMap.erase(it++);
		}
	}

	if (blockGroupMap.size() > 1) {
// cout << "7\n";
		int col_max = 0;
		for (map<int, BlockGroup>::iterator it = blockGroupMap.begin(); it!= blockGroupMap.end(); it++) {
			col_max = findMax(it->second.col_min, col_max);
		}
// cout << "8\n";
		for (map<int, BlockGroup>::iterator it = blockGroupMap.begin(); it!= blockGroupMap.end();) {
			if (it->second.col_min == col_max) it++;
			else blockGroupMap.erase(it++);
		}
	}
	maxBlockGroup[0] = blockGroupMap.begin()->second;
	blockGroupMap.clear();
	// cout << "끄특긑긑\n";
}

void makeBlockGroup(int r, int c) {
	BlockGroup blockgroup;

	queue<pair<int, int> > q;
	q.push(make_pair(r, c));
	visit[r][c] = true;

	blockgroup.pushBlock(r, c);

	int color = stage[r][c];
	// cout << "(" << r << ", " << c << ") : " << color << endl;
	while (q.size() > 0) {
		int row = q.front().first;
		int col = q.front().second;
		q.pop();
		// cout << "q,size : " << q.size() << endl;
		for (int i = 0; i < 4; ++i) {
			// cout << "여기\n";
			int new_r = row + dir_r[i];
			int new_c = col + dir_c[i];
			// cout << "new (" << new_r << ", " << new_c << ")" << endl;
			if (!isValid(new_r, new_c)) continue;
			// cout << "음\n";
			if (stage[new_r][new_c] == -1 || stage[new_r][new_c] == -2) continue;
			// cout << "뭘까\n";
			if (stage[new_r][new_c] != 0 && color != stage[new_r][new_c]) continue;
			// cout << "why?\n";
			if (visit[new_r][new_c] == true) continue;
			// cout << "here\n";

			q.push(make_pair(new_r, new_c));

			visit[new_r][new_c] = true;

			blockgroup.pushBlock(new_r, new_c);
			// cout << "front : "<< q.front().first << endl;
		}
	}
	// cout << "끝\n";
	if (blockgroup.normal > 1) {
		blockgroup.setStandard();
		// blockgroup.toString();
		blockGroupMap.insert({key++, blockgroup});
	}

}

void gravitiy() {
	for (int r = N-2; r >= 0; --r) {
		for (int c = 0; c < N; ++c) {
			if (stage[r][c] < 0) continue;
			int new_r = r+1;
			while(new_r < N) {
				if (stage[new_r][c] != -2) break;
				new_r++;
			}
			new_r--;
			if (stage[new_r][c] == -2) {
				stage[new_r][c] = stage[r][c];
				stage[r][c] = -2;
			}
		}
	}
}


void autoPlay() {
	for (int r = 0; r < N; ++r) {
		for (int c = 0; c < N; ++c) {
			if (stage[r][c] < 1) continue;
			if (visit[r][c]) continue;

			makeBlockGroup(r, c);
		}
	}
	// cout << "끝끝\n";
	findMaxBlockGroup();
	// maxBlockGroup[0].toString();

	score += maxBlockGroup[0].size * maxBlockGroup[0].size;
	for (vector<pair<int, int> >::iterator it = maxBlockGroup[0].vec.begin(); it != maxBlockGroup[0].vec.end(); it++) {
		stage[it->first][it->second] = -2;
	}

	for (int i =0; i< N; i++) {
		for (int j = 0; j < N; j++) {
			cout << stage[i][j] << " ";
		}cout << endl;
	}
	cout << endl;
	cout << "after gravity\n";
	gravitiy();

	for (int i =0; i< N; i++) {
		for (int j = 0; j < N; j++) {
			cout << stage[i][j] << " ";
		}cout << endl;
	}
}

int main() {
	cin >> N >> M;

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> stage[i][j];
		}
	}

	do{
		autoPlay();
	} while (blockgroup > 0);
}