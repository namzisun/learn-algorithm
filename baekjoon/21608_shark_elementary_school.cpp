#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <cmath>

using namespace std;

int N;
int total_student;
int classroom[20][20];
int dir_r[4] = {-1, 1, 0, 0};
int dir_c[4] = {0, 0, -1, 1};

int answer = 0;

bool isValid(int r, int c) {
	if (r < 0 || N <= r || c < 0 || N <= c) return false;
	return true;
}


class Student {
public :
	int favoriteFriendArr[4];
	int number;
	int good;
	int nearByFavorite;
	int row, col;

	Student() {}
	Student(int n, int ffa[4]) {
		number = n;
		for (int i = 0; i < 4; ++i) {
			favoriteFriendArr[i] = ffa[i];
		}
	}

	void setSeat(int r, int c, int f) {
		row = r;
		col = c;
		nearByFavorite = f;
	}

	void calculateGood() {
		good = pow(10, nearByFavorite-1);
	}
};

struct seat {
	int row;
	int column;
	int favorite;
	int empty;
};

vector<Student> studentVec;

void teacher() {

	map<pair<int, int>, seat> seatMap;
	for (int i = 0; i < total_student; ++i) {
		for (int r = 0; r < N; ++r) {
			for (int c = 0; c < N; ++c) {
				// seatMap 채우기
				if (classroom[r][c] == 0) {
					int countFavorite = 0;
					int countEmpty = 0;
					for (int k = 0; k < 4; ++k) {
						int new_r = r + dir_r[k];
						int new_c = c + dir_c[k];

						if (!isValid(new_r, new_c)) continue;

						for(int f = 0; f < 4; ++f) {
							if (classroom[new_r][new_c] == studentVec.at(i).favoriteFriendArr[f])
								countFavorite++;
						}

						if (classroom[new_r][new_c] == 0)
							countEmpty++;
					}
					seat s = {r, c, countFavorite, countEmpty};
					seatMap.insert({make_pair(r, c), s});
				}
			}
		}

		if (seatMap.size() > 1) {
			int maxFavorite = 0;
			// 좋아하는 학생 최댓값 찾기
			for (map<pair<int, int>, seat>::iterator it = seatMap.begin(); it != seatMap.end(); it++) {
				if (it->second.favorite >= maxFavorite)
					maxFavorite = it->second.favorite;
			}

			// 좋아하는 학생 최댓값만 남기기
			for (map<pair<int,int>,seat>::iterator it = seatMap.begin(); it != seatMap.end();) {
				if (it->second.favorite < maxFavorite)
					seatMap.erase(it++);
				else it++;
			}
		}

		if (seatMap.size() > 1) {
			int maxEmpty = 0;
			//empty max 찾기
			for (map<pair<int, int>, seat>::iterator it = seatMap.begin(); it != seatMap.end(); it++) {
				if (it->second.empty >= maxEmpty)
					maxEmpty = it->second.empty;
			}
			// empty max만 남기기
			for (map<pair<int, int>, seat>::iterator it = seatMap.begin(); it != seatMap.end();) {
				if (it->second.empty < maxEmpty)
					seatMap.erase(it++);
				else it++;
			}
		}

		if (seatMap.size() > 1) {
			int minRow = 20;
			// row min인 곳 찾기
			for (map<pair<int, int>, seat>::iterator it = seatMap.begin(); it != seatMap.end(); it++) {
				if (it->second.row < minRow)
					minRow = it->second.row;
			}

			// row 최솟값만 남기기
			for (map<pair<int, int>, seat>::iterator it = seatMap.begin(); it != seatMap.end();) {
				if (it->second.row > minRow)
					seatMap.erase(it++);
				else it++;
			}
		}

		if (seatMap.size() > 1) {
			int minCol = 20;
			// col이 min 인 곳 찾기
			for (map<pair<int,int>,seat>::iterator it = seatMap.begin(); it != seatMap.end(); it++) {
				if (it->second.column < minCol)
					minCol = it->second.column;
			}

			// col min만 남기기
			for (map<pair<int, int>, seat>::iterator it = seatMap.begin(); it != seatMap.end();) {
				if (it->second.column > minCol)
					seatMap.erase(it++);
				else it++;
			}
		}

		seat selectSeat = seatMap.begin()->second;

		studentVec.at(i).setSeat(selectSeat.row, selectSeat.column, selectSeat.favorite);
		classroom[selectSeat.row][selectSeat.column] = studentVec.at(i).number;

		seatMap.clear();
	}
}

void satisfaction() {
	for (int i = 0; i < total_student; ++i) {
		int countFavorite = 0;
		for (int k = 0; k < 4; ++k) {
			int new_r = studentVec.at(i).row + dir_r[k];
			int new_c = studentVec.at(i).col + dir_c[k];

			if (!isValid(new_r, new_c)) continue;

			for(int f = 0; f < 4; ++f) {
				if (classroom[new_r][new_c] == studentVec.at(i).favoriteFriendArr[f])
					countFavorite++;
			}
		}
		studentVec.at(i).nearByFavorite = countFavorite;
		studentVec.at(i).calculateGood();
		answer += studentVec.at(i).good;
	}
}

int main() {
	cin >> N;
	
	total_student = N*N;

	int n, favorite[4];
	for (int i = 0; i < total_student; ++i) {
		cin >> n;
		for (int j = 0; j < 4; ++j) {
			cin >> favorite[j];
		}
		Student s = Student(n, favorite);
		studentVec.push_back(s);
	}

	teacher();

	satisfaction();

	cout << answer << '\n';
}