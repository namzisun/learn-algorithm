#include <iostream>
#include <vector>

using namespace std;

int N;
int total_student;
int classroom[20][20];

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

	void setSeat(int r, int c) {
		row = r;
		col = c;
	}

	void calculateGood() {
		good = pow(10, nearByFavorite);
	}

	void calculateNearByFavorite() {

	}

	void toString() {
		cout << "student "  << number << " is favorite ";
		for (int i : favoriteFriendArr) {
			cout << i << ", ";
		}
		cout << endl;
	}
};

struct seat {
	int row;
	int column;
	int farvorite;
	int empty;
};

vector<Student> studentVec;

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

	for (int i = 0; i < studentVec.size(); i++) {
		studentVec.at(i).toString();
	}
}