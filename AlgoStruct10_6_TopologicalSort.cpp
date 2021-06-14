#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
using namespace std;
const int MAXV = 100;

vector<int> G[MAXV];
int n, m, inDegree[MAXV], numperson = 0; //入度
map<string, int> string2int; 
map<int, string> int2string;

int ChangeString(string str)
{
    if (string2int.find(str) != string2int.end())
    {
        return string2int[str];
    }
    else
    {
        string2int[str] = numperson;
        int2string[numperson] = str;
        return numperson++;
    }
}

bool topologicalSort()
{
    int num = 0; //加入拓扑序列的顶点数
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
        cout << int2string[u] << ' ';
        q.pop();
        for (int i = 0; i < G[u].size(); i++)
        {
            int v = G[u][i];
            inDegree[v]--;
            if (inDegree[v] == 0)
            {
                q.push(v);
            }
        }
        G[u].clear();
        num++;
    }
    cout << endl;
    if (num == n)
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
    string su, sv, st;
    scanf_s("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
    {
        cin >> su >> sv;
        int idu = ChangeString(su);
        int idv = ChangeString(sv);
        G[idu].push_back(idv);
        inDegree[idv]++;
    }

    bool canDAG = topologicalSort();

    cout << canDAG << endl;
    return 0;
}


