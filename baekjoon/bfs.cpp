#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Vertex
{
	int data;
};

vector<Vertex> vertices;
vector<vector<int> > adjacent;
vector<bool> discovered;

void CreateGraph()
{
	vertices.resize(6);

	adjacent = vector<vector<int> >{
		{0, 1, 0, 1, 0, 0},
		{1, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, 0}
	};
}

void Bfs(int here)
{
	queue<int> q;
	q.push(here);
	discovered[here] = true;

	while (q.empty() == false)
	{
		here = q.front();
		q.pop();

		cout << "visited : " << here << endl;

		int size = vertices.size();
		cout << "vertices.size : " << size << "\n";
		for (int there = 0; there < size; there++)
		{
			if (adjacent[here][there] == 0)
				continue;
			if (discovered[there])
				continue;

			q.push(there);
			discovered[there] = true;
		}
	}
}

int main()
{
	CreateGraph();
	discovered = vector<bool>(6, false);
	Bfs(0);
}