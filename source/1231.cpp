//
//  main.cpp
//  1231最近共同祖先
//
//  Created on 15/12/11.
#include <iostream>
#include <cstdio>
using namespace std;

int n,x,y;
struct node{
    int NO = 0;
    node *father = NULL,*left = NULL,*right = NULL;
};
node* tree[100000];

void init()
{
    int i;
    for(i=0;i<100000;++i) tree[i] = new node;
    scanf("%d%d%d",&n,&x,&y);
    for(i=1;i<=n;++i)
    {
        int lf,rt;
        scanf("%d%d",&lf,&rt);
        tree[i]->NO = i;
        if(lf != 0) {tree[i]->left = tree[lf];tree[lf]->father = tree[i];}
        if(rt != 0) {tree[i]->right = tree[rt];tree[rt]->father = tree[i];}
    }
}

int deepth(int NO)
{
    int dp = 1;
    node *tmp = tree[NO];
    while(tmp->father != NULL)
    {tmp = tmp->father;++dp;}
    return dp;
}

void findcommen(node *&a,int dp_a,node *&b,int dp_b)
{
    if(dp_a == dp_b)
    {
        if(a->NO == b->NO)
        {cout << a->NO <<endl;return;}
        else {
            findcommen(a->father,dp_a-1,b,dp_b);
        }
    }
    else if(dp_a > dp_b) findcommen(a->father,dp_a-1,b,dp_b);
    else findcommen(a,dp_a,b->father,dp_b-1);
}

int main()
{
    init();
    findcommen(tree[x],deepth(x),tree[y],deepth(y));
    return 0;
}


