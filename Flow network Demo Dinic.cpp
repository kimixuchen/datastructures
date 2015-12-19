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
int n,m; //1��Դ�㣬m�ǻ��
bool CountLayer()
{
	int layer = 0;
	deque<int>q;
	memset(Layer,0xff,sizeof(Layer));//����ʼ����-1
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
				//Layer[j] == -1 ˵��j��û�з��ʹ�
				Layer[j] = Layer[v] + 1;
				if( j == m ) //�ֲ㵽��㼴��
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
	deque<int> q;//DFS�õ�ջ
	while( CountLayer() )   //ֻҪ�ֲܷ�
	{
		q.push_back(1); //Դ����ջ
		memset(Visited,0,sizeof(Visited));
		Visited[1] = 1;
		while( !q.empty())
		{
			int nd = q.back();
			if( nd == m )   // nd�ǻ��
			{
				//��ջ����������С��
				int nMinC = INFINITE;
				int nMinC_vs; //������С�ߵ����
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
				//���㣬��ͼ
				nMaxFlow += nMinC;
				for( i = 1; i < q.size(); i ++ )
				{
					int vs = q[i-1];
					int ve = q[i];
					G[vs][ve] -= nMinC; //�޸ı�����
					G[ve][vs] += nMinC; //��ӷ����
				}
				//��ջ�� nMinC_vs��Ϊջ�����Ա����dfs
				while( !q.empty() && q.back() != nMinC_vs )
				{
					Visited[q.back()] = 0; //û�����Ӧ��Ҳ��
					q.pop_back();
				}
			}
			else   //nd���ǻ��
			{
				for( i = 1; i <= m; i ++ )
				{
					if( G[nd][i] > 0 && Layer[i] == Layer[nd] + 1 &&
					        ! Visited[i])
					{
						//ֻ����һ���û���߹��Ľڵ���
						Visited[i] = 1;
						q.push_back(i);
						break;
					}
				}
				if( i > m) //�Ҳ�����һ����
					q.pop_back(); //����
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
			G[s][e] += c; //����֮������ж�����
		}
		cout << Dinic() << endl;
	}
	return 0;
}