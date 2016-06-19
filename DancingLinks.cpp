/**
hihocoder-#1317-ËÑË÷4-ÌøÎèÁ´
15/06/16 16:22:19
xuchen
**/
#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <map>
using namespace std;

const int N = 105;

struct Node{
    int x, y;
    Node *right, *left, *up, *down;
    /*
    Node(int x, int y, Node* r, Node* l, Node* u, Node* d)
    {this->x=x; this->y=y; right=r; left=l; up=u; down=d;}
    */
};

Node head;
Node columnHead[N];
Node nodes[N*N];

int matrix[N][N];
int id[N][N];
int ans[N];
int t;
int n, m;
int cnt;

void build()
{
    head.x=0; head.y=0;
    head.right=&head; head.left=&head; head.up=&head; head.down=&head;

    Node *pre = &head;
    for(int i=1; i<=m; ++i)
    {
        Node* p = &columnHead[i];
        p->up = p;
        p->down = p;
        p->left = pre;
        p->right = &head;
        pre->right = p;
        head.left = p;
        p->x = 0;
        p->y = i;
        pre = p;
    }

    cnt=0;
    for(int i=1; i<=n; ++i)
    {
        for(int j=1; j<=m; ++j)
        {
            if(1 == matrix[i][j])
            {
                ++cnt;
                id[i][j] = cnt;
                nodes[cnt].x=i; nodes[cnt].y=j;
                nodes[cnt].left=&nodes[cnt]; nodes[cnt].right=&nodes[cnt];
                nodes[cnt].up=&nodes[cnt]; nodes[cnt].down=&nodes[cnt];
            }
        }
    }

    for(int j=1; j<=m; ++j)
    {
        Node* pre = &columnHead[j];
        for(int i=1; i<=n; ++i)
        {
            if(1==matrix[i][j])
            {
                Node* p = &nodes[id[i][j]];
                pre->down->up = p;
                p->down = pre->down;
                pre->down = p;
                p->up=pre;
                pre = p;
            }
        }
    }

    for(int i=1; i<=n; ++i)
    {
        Node *pre = NULL;
        for(int j=1; j<=m; ++j)
        {
            if(1==matrix[i][j])
            {
                Node* p = &nodes[id[i][j]];
                if(NULL == pre)
                {
                    pre = p;
                }
                else
                {
                    pre->right->left = p;
                    p->right = pre->right;
                    pre->right = p;
                    p->left = pre;
                    pre = p;
                }
            }
        }
    }
}

void remove(int col)
{
    Node *p = &columnHead[col];
    p->left->right = p->right;
    p->right->left = p->left;
    Node *p1 = p->down;
    while(p1!=p)
    {
        Node *p2 = p1->right;
        while(p2!=p1)
        {
            p2->up->down = p2->down;
            p2->down->up = p2->up;
            p2 = p2->right;
        }
        p1 = p1->down;
    }
}

void recover(int col)
{
    Node *p = &columnHead[col];
    p->left->right = p;
    p->right->left = p;
    Node *p1 = p->down;
    while(p1!=p)
    {
        Node *p2 = p1->right;
        while(p2!=p1)
        {
            p2->up->down = p2;
            p2->down->up = p2;
            p2 = p2->right;
        }
        p1 = p1->down;
    }
}

bool dance(int depth)
{
    Node *p = head.right;
    if(p==&head)
        return true;

    int col = p->y;
    
    Node *p2 = p->down;
    if(p2==p)
        return false;
    
    remove(col);
    while(p2!=p)
    {
        ans[depth] = p2->x;
        Node *p3 = p2->right;
        while(p3!=p2)
        {
            remove(p3->y);
            p3 = p3->right;
        }
        if(dance(depth+1))
            return true;
        
        p3 = p2->left;
        while(p3!=p2)
        {
            recover(p3->y);
            p3 = p3->left;
        }
        p2 = p2->down;
    }

    recover(col);
    return false;
}

int main()
{
    scanf("%d", &t);
    while(t--)
    {
        scanf("%d %d", &n, &m);
        memset(matrix, 0, sizeof(matrix));
        memset(ans, 0, sizeof(ans));
        for(int i=1; i<=n; ++i)
        {
            for(int j=1; j<=m; ++j)
                scanf("%d", &matrix[i][j]);
        }
        build();
        if(dance(0))
            printf("Yes\n");
        else
            printf("No\n");
    }



    return 0;
}

