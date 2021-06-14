#include <cstdio>
#include <iostream>
#include <string>
#include <map>
using namespace std;

const int MAXN = 2010;
const int INF = 100000000;

map<int, string> int2str;
map<string, int> str2int;
map<string, int> Gang;
int G[MAXN][MAXN], weight[MAXN];
int n, k, tolNum = 0;
bool vis[MAXN] = { false };

//DFS访问单个连通块，nowvisit为当前访问编号
//head为头目，numMenber为成员编号，totalV为连通块总边权
void DFS(int nowVisit, int& head, int& numMember, int& totalV)
{
    numMember++;
    vis[nowVisit] = true;
    if (weight[head] < weight[nowVisit])
    {
        head = nowVisit;
    }
    for (int i = 0; i < tolNum; i++)
    {
        if (G[nowVisit][i]>0)
        {
            totalV += G[nowVisit][i];
            G[nowVisit][i] = G[i][nowVisit] = 0;
            if (vis[i] == false)
            {
                DFS(i, head, numMember, totalV);
            }
        }
    }
}

void DFSTrave()
{
    for (int i = 0; i < tolNum; i++)
    {
        if (vis[i] == false)
        {
            int head = i, numMember = 0, totalV = 0;
            DFS(i, head, numMember, totalV);
            if (numMember > 2 && totalV > k)
            {
                Gang[int2str[head]] = numMember;
            }
        }
    }
}

//change函数返回姓名Str对应的编号
int Change(string str)
{
    if (str2int.find(str) != str2int.end())
    {
        return str2int[str];
    }
    else
    {
        str2int[str] = tolNum;
        int2str[tolNum] = str;
        return tolNum++;
    }
}



int main()
{
    int w;
    string str1, str2;
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        cin >> str1 >> str2 >> w;
        int id1 = Change(str1);
        int id2 = Change(str2);
        weight[id1] += w; //点权
        weight[id2] += w;
        G[id1][id2] += w; //边权
        G[id2][id1] += w;
    }
    DFSTrave();
    cout << Gang.size() << endl;
    map<string, int>::iterator it;

    for (it = Gang.begin(); it != Gang.end(); it++)
    {
        cout << it->first << " " << it->second << endl;
    }

    return 0;
}


