#include <cstdio>
#include <iostream>
using namespace std;

const int INF = 1000000000;
const int MAXN = 200;
int n, m;
int dis[MAXN][MAXN];

void Floyd()
{
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (dis[i][k] != INF && dis[k][j] != INF &&  dis[i][k] + dis[k][j] < dis[i][j])
				{
					dis[i][j] = dis[i][k] + dis[k][j];
				}
			}
		}
	}
}

int main()
{
	int u, v, w;
	fill(dis[0], dis[0] + MAXN * MAXN, INF);
	scanf_s("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		dis[i][i] = 0;
	}
	for (int i = 0; i < m; i++)
	{
		scanf_s("%d%d%d", &u, &v, &w);
		dis[u][v] = w;
	}

	Floyd();
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%10d ", dis[i][j]);
		}
		printf("\n");
	}
	return 0;
}


