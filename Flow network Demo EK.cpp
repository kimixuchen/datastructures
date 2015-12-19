/**
 *xuchen
 *2015-11-24 16:45:06
**/
/**
 *Flow network Demo
**/
#include "stdio.h"
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int N = 205;
const int INF = 0x3f3f3f3f;
int map[N][N];
int path[N];
int flows[N];
queue<int> q;

int BFS(int m, int s, int t)
{
    memset(path, -1, sizeof(path));
    while(!q.empty())
        q.pop();

    q.push(s);
    path[s] = 0;
    flows[s] = INF;
    bool flag = false;  //if we have found t
    int cur;
    while(!q.empty())
    {
        cur = q.front();
        q.pop();
        for(int i=1; i<=m; i++)
        {
            if(path[i]==-1 && map[cur][i]>0 && !flag)
            {
                flows[i] = flows[cur]<map[cur][i] ? flows[cur]:map[cur][i];
                path[i] = cur;
                q.push(i);
                if(i==t)
                    flag = true;
            }
        }
        if(flag)
            break;
    }
    if(path[t]==-1)
        return 0;
    return flows[t];

}
int Edmons_Karp(int m, int s, int t)
{
    int max_flow = 0;
    int inc;
    while((inc=BFS(m, s, t)) != 0)
    {
        max_flow += inc;
        int m = t;
        while(m!=s)
        {
            map[path[m]][m] -= inc;
            map[m][path[m]] += inc;
            m = path[m];
        }
    }
    return max_flow;
}
int main()
{
    int n, m;
    int from, to, cap;
    int ans;
    while(scanf("%d%d", &n, &m)!=EOF)
    {
        memset(map, 0, sizeof(map));
        for(int i=0; i<n; i++)
        {
           scanf("%d%d%d", &from, &to, &cap);
           map[from][to] += cap;
        }
        ans = Edmons_Karp(m, 1, m);
        printf("%d\n", ans);
    }
	return 0;
}
