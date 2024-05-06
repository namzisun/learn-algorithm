#include <iostream>
#include <vector>

using namespace std;

int first, second;
int N;
vector<int> student;


int main() {

	long answer = 0;

	cin >> N;
	
	int num;
	for (int i = 0; i < N; ++i) {
		cin >> num;
		student.push_back(num);
	}
	cin >> first >> second;

	for (auto i : student) {
		i -= first;
		answer++;
		if (i <= 0) continue;
		if (i % second > 0) answer++;
		answer += (i / second);
	}

	cout << answer << '\n';
	return 0;
}