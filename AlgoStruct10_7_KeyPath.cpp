#include <cstdio>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <string>
using namespace std;

const int MAXV = 100;

struct Node
{
	int v, w;
};

int n, m, inDegree[MAXV], ve[MAXV];
stack<int> topOrder; //拓扑排序
vector<Node> G[MAXV];


bool topologicalSort()
{
    queue<int> q;
	for (int i = 0; i < n; i++)
	{
		if (inDegree[i] == 0)
		{
			q.push(i);
		}
	}
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		topOrder.push(u);

		for (int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i].v;
			inDegree[v]--;
			if (inDegree[v] == 0)
			{
				q.push(v);
			}

			if (ve[u] + G[u][i].w > ve[v])
			{
				ve[v] = ve[u] + G[u][i].w;
			}
		}
	}
	if (topOrder.size() == n)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int main()
{


    return 0;
}


