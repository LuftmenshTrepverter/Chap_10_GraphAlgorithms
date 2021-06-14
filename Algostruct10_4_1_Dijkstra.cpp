#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXV = 1000;
const int INF = 1000000000;

int n, m, s, G[MAXV][MAXV]; //顶点数 边数 起点 邻接矩阵
int d[MAXV]; //起点到各顶点的最短路径长度

/*
新增边权，以新增边权代表花费，要求最短距离相同情况下花费最小
int cost[MAXV][MAXV]; //u->v的花费
int c[MAXV]; //起点到各顶点的最少花费和
*/

/*
新增点权，以新增点权代表城市物资，要求最短距离相同情况下点权和最大
int weight[MAXV]; //城市u的物资
int w[MAXV]; //起点到各顶点的最大物资和，初始化时只有w[s]为weight[s]，其余的都是0
*/

/*
求最短路径条数
int num[MAXV]; //起点到各顶点的最短路径条数，初始化时只有num[s]为1，其余的都是0
*/

int pre[MAXV]; //pre[v]表示从起点到顶点v的最短路径上v的前一个顶点

bool vis[MAXV] = { false }; //标记点v是否被访问过


//邻接表版本
struct Node
{
    int v, dis;
};
vector<Node> Adj[MAXV];

void DijkstraAdjList(int s)
{
    fill(d, d + MAXV, INF);
    d[s] = 0;
    for (int i = 0; i < n; i++)
    {
        int u = -1, MIN = INF; //MIN存放最小的d[u]
        for (int j = 0; j < n; j++)
        {   
            //找到未访问的顶点中d[]最小的
            if (vis[j] == false && d[j] < MIN)
            {
                u = j;
                MIN = d[j]; 
            }
        }

        //找不到小于INF的d[u]，说明剩下的顶点和起点s不连通
        if (u == -1)
        {
            return;
        }
        
        //更新集合S
        vis[u] = true;

        //优化d[v]
        for (int j = 0; j < Adj[u].size(); j++)
        {
            int v = Adj[u][j].v;
            if (vis[v] == false && d[u] + Adj[u][j].dis < d[v])
            {
                d[v] = d[u] + Adj[u][j].dis;
            }
        }

    }
}


//邻接矩阵版本
void Dijkstra(int s)
{
    fill(d, d + MAXV, INF); //初始化数组
    for (int i = 0; i < n; i++)
    {
        pre[i] = i;
    }
    d[s] = 0;
    for (int i = 0; i < n; i++)
    {
        int u = -1, MIN = INF;
        for (int j = 0; j < n; j++)
        {
            if (vis[j]==false && d[j]<MIN)
            {
                u = j;
                MIN = d[j];
            }
        }
        if (u == -1)
        {
            return;
        }
        vis[u] = true;
        //更新d[u]
        for (int v = 0; v < n; v++)
        {
            //v未被访问，u能到达v，以u为中介点可以是d[v]更小
            if (vis[v]==false && G[u][v] != INF && d[u] + G[u][v] < d[v])
            {
                d[v] = d[u] + G[u][v];
                pre[v] = u;
            }
        }
        /* 新增边权
        for (int v = 0; v < n; v++)
        {
            if (vis[v]==false && G[u][v] != INF) //v未被访问且u能到达v
            {
                if (d[u]+G[u][v]<d[v]) //以u为中介点可以是d[v]更小，同时更新d[v] c[v]
                {
                    d[v] = d[u] + G[u][v];
                    c[v] = c[u] + cost[u][v];
                }
                else if (d[u]+G[u][v]=d[v] && c[u]+cost[u][v] < c[v]) //最短距离相同时如果c[v]能更优，更新c[v]
                {
                    c[v] = c[u] + cost[u][v];
                }
            }
        }*/

        /* 新增点权
        for (int v = 0; v < n; v++)
        {
            if (vis[v]==false && G[u][v] != INF) //v未被访问且u能到达v
            {
                if (d[u]+G[u][v]<d[v]) //以u为中介点可以是d[v]更小，同时更新d[v] w[v]
                {
                    d[v] = d[u] + G[u][v];
                    w[v] = w[u] + weight[v];
                }
                else if (d[u]+G[u][v]=d[v] && w[u] + weight[v] < w[v]) //最短距离相同时如果c[v]能更优，更新c[v]
                {
                    w[v] = w[u] + weight[v];
                }
            }
        }*/

        /* 求最短路径条数
        for (int v = 0; v < n; v++)
        {
            if (vis[v]==false && G[u][v] != INF) //v未被访问且u能到达v
            {
                if (d[u]+G[u][v]<d[v]) //以u为中介点可以是d[v]更小，同时更新d[v] w[v]
                {
                    d[v] = d[u] + G[u][v];
                    num[v] = num[u];
                }
                else if (d[u]+G[u][v]=d[v]) //最短距离相同时如果c[v]能更优，更新c[v]
                {
                    num[v] += num[u];
                }
            }
        }*/
    }
}

void DFS(int s, int v)
{
    if (v == s)
    {
        printf("%d\n", s);
        return;
    }
    DFS(s, pre[v]);
    printf("%d\n", v);
}

int main()
{
    int u, v, w;
    scanf_s("%d%d%d", &n, &m, &s); //起点编号
    fill(G[0], G[0] + MAXV * MAXV, INF); //初始化邻接矩阵
    for (int i = 0; i < m; i++)
    {
        scanf_s("%d%d%d", &u, &v, &w); //输入u, v以及u->v的边权
        G[u][v] = w;
    }

    Dijkstra(s); //算法入口

    for (int i = 0; i < n; i++)
    {
        if (i == n-1)
        {
            printf("%d\n", d[i]);
        }
        else
        {
            printf("%d ", d[i]); //输出所有顶点的最短距离
        }
    }
    DFS(0, 5);

    return 0;        
}

