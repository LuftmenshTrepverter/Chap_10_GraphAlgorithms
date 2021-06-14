#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int MAXN = 511;
const int INF = 1000000000;

struct Node
{
    int v, dis;
    Node(int _v, int _dis) : v(_v) , dis(_dis) {}
};

int n, m, st, ed, weight[MAXN];
int d[MAXN], num[MAXN], w[MAXN], numq[MAXN];
bool inq[MAXN];
vector<Node> Adj[MAXN];
set<int> pre[MAXN];

void Bellman(int s)
{
    //d w num都是计算过程中反复更新的，是需要初始化的
    //weight点权等是输入的时候就赋值的，不需要fill初始化
    fill(d, d + MAXN, INF);
    fill(w, w + MAXN, 0);
    fill(num, num + MAXN, 0);

    d[s] = 0;
    num[s] = 1;
    w[s] = weight[s];

    for (int i = 0; i < n-1; i++)
    {
        for (int u = 0; u < n; u++)
        {
            for (int j = 0; j < Adj[u].size(); j++)
            {
                int v = Adj[u][j].v;
                int dis = Adj[u][j].dis;
                if (d[u] + dis < d[v])
                {
                    d[v] = d[u] + dis;
                    w[v] = w[u] + weight[v];
                    num[v] = num[u];
                    pre[v].clear();
                    pre[v].insert(u);
                }
                else if (d[u] + dis == d[v])
                {
                    if (w[u] + weight[v] > w[v])
                    {
                        w[v] = w[u] + weight[v];
                    }
                    pre[v].insert(u);
                    num[v] = 0;
                    set<int>::iterator it;
                    for (it = pre[v].begin(); it != pre[v].end(); it++)
                    {
                        num[v] += num[*it];
                    }
                }
            }
        }
    }

}

void SPFA(int s)
{
    //fill(numq, numq + MAXN, 0);
    fill(inq, inq + MAXN, false);
    fill(num, num + MAXN, 0);
    fill(d, d + MAXN, INF);
    fill(w, w + MAXN, 0);

    queue<int> q;
    q.push(s);
    inq[s] = true;
    num[s]++;
    d[s] = 0;
    w[s] = weight[s];
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        inq[u] = false;
        for (int i = 0; i < Adj[u].size(); i++)
        {
            int v = Adj[u][i].v;
            int dis = Adj[u][i].dis;
            if (d[u] + dis < d[v])
            {
                d[v] = d[u] + dis;
                w[v] = w[u] + weight[v];
                num[v] = num[u];
                pre[v].clear();
                pre[v].insert(u);
                if (inq[v] == false)
                {
                    q.push(v);
                    inq[v] = true;
                    //numq[v]++;
                    //if (numq[v] >= n)
                    //{
                    //    break;
                    //}
                }
            }
            if (d[u] + dis == d[v])
            {
                if (w[u] + weight[v] > w[v])
                {
                    w[v] = w[u] + weight[v];
                }
                pre[v].insert(u);
                num[v] = 0;
                set<int>::iterator it;
                for ( it = pre[v].begin(); it != pre[v].end(); it++)
                {
                    num[v] += num[*it];
                }
                if (inq[v] == false)
                {
                    q.push(v);
                    inq[v] = true;
                    //numq[v]++;
                    //if (numq[v] >= n)
                    //{
                    //    break;
                    //}
                }
            }
        }
    }
}

int main()
{
    int u, v, wt;
    scanf_s("%d%d%d%d", &n, &m, &st, &ed);
    for (int i = 0; i < n; i++)
    {
        scanf_s("%d", &weight[i]);
    }

    for (int i = 0; i < m; i++)
    {
        scanf_s("%d%d%d", &u, &v, &wt);
        Adj[u].push_back(Node(v, wt));
        Adj[v].push_back(Node(u, wt));
    }

    SPFA(st);
    printf_s("%d %d", num[ed], w[ed]);
    return 0;
}


