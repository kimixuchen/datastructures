/**
 *POJ-1273-Drainage Ditches
 *xuchen
 *2015-12-19 13:59:05
**/
/**
 *Flow network
 *Dinic
**/
#include "stdio.h"
#include <cstring>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include "time.h"
using namespace std;

const int INFINITE = 0x3f3f3f3f;
int G[300][300];
bool Visited[300];
int Layer[300];
int n,m; //1是源点，m是汇点
bool CountLayer()
{
	int layer = 0;
	deque<int>q;
	memset(Layer,0xff,sizeof(Layer));//都初始化成-1
	Layer[1] = 0;
	q.push_back(1);
	while( ! q.empty())
	{
		int v = q.front();
		q.pop_front();
		for( int j = 1; j <= m; j ++ )
		{
			if( G[v][j] > 0 && Layer[j] == -1 )
			{
				//Layer[j] == -1 说明j还没有访问过
				Layer[j] = Layer[v] + 1;
				if( j == m ) //分层到汇点即可
					return true;
				else
					q.push_back(j);
			}
		}
	}
	return false;
}
int Dinic()
{
	int i;
	int s;
	int nMaxFlow = 0;
	deque<int> q;//DFS用的栈
	while( CountLayer() )   //只要能分层
	{
		q.push_back(1); //源点入栈
		memset(Visited,0,sizeof(Visited));
		Visited[1] = 1;
		while( !q.empty())
		{
			int nd = q.back();
			if( nd == m )   // nd是汇点
			{
				//在栈中找容量最小边
				int nMinC = INFINITE;
				int nMinC_vs; //容量最小边的起点
				for( i = 1; i < q.size(); i ++ )
				{
					int vs = q[i-1];
					int ve = q[i];
					if( G[vs][ve] > 0 )
					{
						if( nMinC > G[vs][ve] )
						{
							nMinC = G[vs][ve];
							nMinC_vs = vs;
						}
					}
				}
				//增广，改图
				nMaxFlow += nMinC;
				for( i = 1; i < q.size(); i ++ )
				{
					int vs = q[i-1];
					int ve = q[i];
					G[vs][ve] -= nMinC; //修改边容量
					G[ve][vs] += nMinC; //添加反向边
				}
				//退栈到 nMinC_vs成为栈顶，以便继续dfs
				while( !q.empty() && q.back() != nMinC_vs )
				{
					Visited[q.back()] = 0; //没有这个应该也对
					q.pop_back();
				}
			}
			else   //nd不是汇点
			{
				for( i = 1; i <= m; i ++ )
				{
					if( G[nd][i] > 0 && Layer[i] == Layer[nd] + 1 &&
					        ! Visited[i])
					{
						//只往下一层的没有走过的节点走
						Visited[i] = 1;
						q.push_back(i);
						break;
					}
				}
				if( i > m) //找不到下一个点
					q.pop_back(); //回溯
			}
		}
	}
	return nMaxFlow;
}
int main()
{
	while (cin >> n >> m )
	{
		int i,j,k;
		int s,e,c;
		memset( G,0,sizeof(G));
		for( i = 0; i < n; i ++ )
		{
			cin >> s >> e >> c;
			G[s][e] += c; //两点之间可能有多条边
		}
		cout << Dinic() << endl;
	}
	return 0;
}