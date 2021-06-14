#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 1000;
const int INF = 1000000000;

struct Node
{
    int v, dis;
    Node(int _v, int _dis) : v(_v), dis(_dis) {}
};

int G[MAXN][MAXN];
vector<Node> Adj[MAXN];
int n, m;
int d[MAXN];
bool vis[MAXN] = { false };

int PrimAdj()
{
    int ans = 0;
    fill(d, d + MAXN, INF);
    d[0] = 0;

    for (int i = 0; i < n; i++)
    {
        int u = -1, MIN = INF;
        for (int j = 0; j < n; j++)
        {
            if (vis[j] == false && d[j] < MIN)
            {
                u = j;
                MIN = d[j];
            }
        }

        if (u == -1)
        {
            return -1;
        }

        vis[u] = true;
        ans += d[u];

        for (int j = 0; j < Adj[u].size(); j++)
        {
            int v = Adj[u][j].v;
            int dis = Adj[u][j].dis;
            if (vis[v] == false &&  dis < d[v])
            {
                d[v] = dis;
            }
        }

    }
    return ans;
}

int PrimMatrix()
{
    int ans = 0;
    fill(d, d + MAXN, INF);
    d[0] = 0;

    for (int i = 0; i < n; i++)
    {
        int u = -1, MIN = INF;
        for (int j = 0; j < n; j++) //找最小的d[u]
        {
            if (vis[j]==false && d[j] < MIN)
            {
                u = j;
                MIN = d[j];
            }
        }
        if (u == -1)
        {
            return -1;
        }

        vis[u] = true;
        ans += d[u];
        for (int v = 0; v < n; v++)
        {
            if (vis[v] == false && G[u][v] != INF && G[u][v] < d[v])
            {
                d[v] = G[u][v];
            }
        }
    }
    return ans;
}

int main()
{
    int u, v, w;
    scanf_s("%d%d", &n, &m);
    fill(G[0], G[0] + MAXN * MAXN, INF);
    for (int i = 0; i < m; i++)
    {
        scanf_s("%d%d%d", &u, &v, &w);
        G[u][v] = G[v][u] = w;
        Adj[u].push_back(Node(v,w));
        Adj[v].push_back(Node(u,w));
    }
    //int ansPrimMatrix = PrimMatrix();
    int ansPrimAdj = PrimAdj();
    printf("%d\n", ansPrimAdj);
    return 0;
}

