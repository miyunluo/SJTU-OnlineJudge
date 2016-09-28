//
//  main.cpp
//  1233 Path
//
//  Created on 15/12/11.
//
#include <iostream>
#include <cstdio>
using namespace std;
/*
struct node{
    int NO;
    node *next;
    
    node(int n){NO = n;next = NULL;}
    node(){next = NULL;}
};

node* spot[11];
int n,m,start,M;   //n节点数  m有向边数  start起点编号   M简单路径长度

void init()
{
    scanf("%d%d%d%d",&m,&m,&start,&M);
    int i;
    for(i = 1;i<=10;++i)spot[i] = new node(i);
    
    for(i=0;i<m;++i)
    {
        int begin,end;
        scanf("%d%d",&begin,&end);
        node *tmp = spot[begin];
        
        if(tmp->next == NULL) tmp->next = new node(end);
        
        else {
            bool exist = false;
            node *temp = tmp->next;
            while(temp != NULL)
            {
                if(temp->NO == end) {exist = true;break;}
                temp = temp->next;
            }
            
            if(!exist)
            {
                temp = tmp->next;
                tmp->next = new node(end);
                tmp->next->next = temp;
            }     
        }
    }
}
*/

int **table;
int n,m,start,M;   //n节点数  m有向边数  start起点编号   M简单路径长度
bool *visited;
int pathnum;

void init()
{
    table = new int *[11];
    for (int i = 0; i <11; ++i) {
        table[i] = new int [11];
        for (int j = 0; j <11; ++j) table[i][j] = 0;
    }
    visited = new bool[11];
    for(int i=0;i<11;++i) visited[i] = false;
    
    scanf("%d%d%d%d",&n,&m,&start,&M);
    int i,j;
    for(i=0;i<11;++i)
        for(j=0;j<11;++j) table[i][j] = 0;
    
    for(int k = 0;k<m;++k)
    {
        int begin,end;
        scanf("%d%d",&begin,&end);
        table[begin][end] = 1;
    }
}

// n 结点数量 / 非负整数 m 图中有向边的数量 / start 起点编号 / M为题中的简单路径长度
    
void DFS(int **table,int n,int M,int start,bool *visited)
{
    if(M == 0){++pathnum;return;}
    
    for(int i=1;i<=n;++i)
    {
        if(table[start][i] == 1)
        {
            if(!visited[i])
            {
                visited[i] = true;
                DFS(table,n,M-1,i,visited);
                visited[i] = false;
            }
        }
    }
}

int main()
{
    init();
    visited[start] = true;
    DFS(table,n,M,start,visited);
    cout << pathnum <<endl;
    return 0;
}
