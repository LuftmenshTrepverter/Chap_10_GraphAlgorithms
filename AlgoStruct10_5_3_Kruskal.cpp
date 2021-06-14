#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXV = 110;
const int MAXE = 10010;

//边的结构体
struct Edge
{
    int u, v;
    int cost;
}E[MAXE];

//边权比较函数的cmp
bool cmp(Edge a, Edge b)
{
    return a.cost < b.cost;
}

int father[MAXV];

//并查集的查找和路径压缩功能的实现
int findFather(int x)
{
    int a = x;
    //寻找根结点
    while (x != father[x])
    {
        x = father[x];
    }

    //路径压缩
    while (a != father[a])
    {
        int z = a;
        a = father[a];
        father[z] = x;
    }
    return x;
}

int kruskal(int n, int m)
{
    int ans = 0, num_edge = 0;
    
    //并查集初始化
    for (int i = 0; i < n; i++)
    {
        father[i] = i;
    }

    //所有边按边权排序
    sort(E, E + m, cmp);
    
    //枚举所有的边
    for (int i = 0; i < m; i++)
    {
        int U_father = findFather(E[i].u);
        int V_father = findFather(E[i].v);
        if (U_father != V_father) //如果不是一个集合
        {
            father[U_father] = V_father; //合并集合
            ans += E[i].cost; //最小边权累加
            num_edge++; //边数累加，边数是算法结束的条件
            if (num_edge == n-1) //边数=顶点数-1，就退出算法
            {
                break;
            }
        }
    }

    if (num_edge != n-1) //图不连通
    {
        return -1;
    }
    else
    {
        return ans;
    }
}

int main()
{
    int n, m;
    scanf_s("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        scanf_s("%d%d%d", &E[i].u, &E[i].v, &E[i].cost);
    }
    int ans = kruskal(n, m);
    printf("%d", ans);
    return 0;
}

