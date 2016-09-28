#include <iostream>
#include <cstdio>
using namespace std;

struct node{
    node*father;
    node*brother ;
    node*son;
    node():father(NULL),brother(NULL),son(NULL){}
};

node* machine[100001]; //存储交换机
node* computer[100001];  //存储电脑

void insert()
{
    for(int i=0;i<=100001;++i)machine[i] = new node();
    for(int i=0;i<=100001;++i)computer[i] = new node();
    int n,m; //n  交换机     m   电脑
    scanf("%d%d",&n,&m);
    int i;
    for(i = 2;i<=n;++i)
    {
        int index;
        scanf("%d",&index);
        machine[i]->father = machine[index];
        if(machine[index]->son == NULL)
        {machine[index]->son = machine[i];}
        else{
            node *tmp = machine[index]->son;
            while(tmp->brother != NULL) tmp = tmp->brother;
            tmp->brother = machine[i];
        }
    }
    
    for(i = 1;i<=m;++i)
    {
        int index;
        scanf("%d",&index);
        computer[i]->father = machine[index];
        if(machine[index]->son == NULL)
        {machine[index]->son = computer[i];}
        else{
            node *tmp = machine[index]->son;
            while(tmp->brother != NULL) tmp = tmp->brother;
            tmp->brother = computer[i];
        }
    }
    
}


int findson(node*t)
{
    int n = 0;
    if(t->son == NULL){return n;}
    else{
        node *tmp = t->son;
        ++n;
        while(tmp->brother != NULL)
        {tmp = tmp->brother;++n;}
        return n;
    }
    
}

int deepth(node *t)
{
    if(t->son == NULL)return  0;
    else{
        int sonnum = findson(t);
        int *list = new int[sonnum];
        node *tmp = t->son;
        for(int i=0;i<sonnum;++i) {list[i] = (deepth(tmp) + 1);tmp = tmp->brother;}
        int maxdeepth = 0;
        for(int i=0;i<sonnum;++i){if(list[i] > maxdeepth) maxdeepth = list[i];}
        
        return maxdeepth;
    }
}

int main()
{
    insert();
    int frst = findson(machine[1]);
    //cout<<"frst:"<<frst<<endl;
    int *sonlist = new int[frst+1];
    node *tmp = machine[1]->son;
    for(int i=0;i<frst;++i)
    {sonlist[i] = deepth(tmp);tmp = tmp->brother;}
    //for(int i=0;i<frst;++i)cout<< sonlist[i];
    int maxmax = 0,maxmin = 0;
    int i,maxindex;
    for(i=0;i<frst;++i)
    {
        if(sonlist[i] > maxmax){maxmax = sonlist[i];maxindex = i;}
    }
    for(i=0;i<frst;++i)
    {
        if(sonlist[i] > maxmin && i != maxindex)maxmin = sonlist[i];
    }
    //cout<<"maxmax:"<<maxmax<<" maxmin:"<<maxmin<<endl;
    cout<< maxmax + maxmin + 2<<endl;
    return 0;
}


