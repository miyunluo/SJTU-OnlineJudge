#include <iostream>
#include <cstdio>
using namespace std;

struct node{
    int NO;
    int red = 0;  //1 means red
    node *left = NULL,*right = NULL;
};
node* skim[100001];
int bulbnum[100001];
int stackindex = 0;
int n,p,q;

/********************************************/
void init()                  //构造二叉树
{
    for(int i=0;i<100001;++i) skim[i] = new node;  //这里要先申请空间
    
    scanf("%d%d%d",&n,&p,&q);
    int i;
    for(i=0;i<n;++i)
    {
        int num,lf,rt;
        scanf("%d%d%d",&num,&lf,&rt);
        skim[num]->NO = num;
        if(lf != 0){skim[num]->left = skim[lf];}
        if(rt != 0){skim[num]->right = skim[rt];}
    }
}
/*******************************************/
int size(node *t)
{
    if(t == NULL)return 0;
    else{
        int lfsize = size(t->left);
        int rtsize = size(t->right);
        return (lfsize + rtsize + 1);
    }
}

void midorder(node *t,int theno)
{
    if(t != NULL){
        midorder(t->left,theno);
        bulbnum[stackindex++] = t->NO;
        if(stackindex > theno)return;
        midorder(t->right,theno);
    }
}
void paint(int index,int x)
{
    int y = size(skim[index]);
    int theno = x%y ;
    midorder(skim[index],theno);
    int k = bulbnum[theno];
    skim[k]->red = 1;
    stackindex = 0;
}

void makered()
{
    for(int i=0;i<p;++i)
    {
        int index,x;
        scanf("%d%d",&index,&x);
        paint(index,x);
    }
}

/*******************************************/
int rednum(node *t)
{
    if(t == NULL)return 0;
    else{
        int lfnum = rednum(t->left);
        int rtnum = rednum(t->right);
        if(t->red == 1) return (lfnum + rtnum + 1);
        else return (lfnum + rtnum);
        
    }
}

void ask()
{
    for (int i=0;i<q;++i)
    {
        int num;
        scanf("%d",&num);
        cout << rednum(skim[num])<<endl;
    }
}
/*******************************************/
int main()
{
    init();
    makered();
    ask();
    return 0;
}

