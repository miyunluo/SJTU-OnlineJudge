//
//  main.cpp
//  1236 SPFA
//
//  Created on 15/12/19.
#include <iostream>
#include <cstdio>
#define noEdge 9999999999;
using namespace std;

class squeue
{
public:
    int *arry;
    int length;
    int front,rear;
    
    squeue(){arry = new int[10000];length = 10000;front = rear = 0;}
    ~squeue(){delete [] arry;}
    void enQueue(int &x)
    {
        if((rear+1)%length == front) doubleSpace();
        arry[(++rear)%length] = x;
    }
    int deQueue()
    {return arry[(++front)%length];}
    void doubleSpace()
    {
        int *tmp = new int[length];
        for(int i=0;i<length;++i) tmp[i] = arry[i];
        arry = new int[length * 2];
        for(int i=0;i<length;++i) arry[i] = tmp[i];
        length *= 2;
        delete tmp;
    }
    bool isEmpty()
    {return (front%length == rear % length);}
    
};

int spotNum,edgeNum,startNum,endNum;

struct node{
    int NO;
    int weight;
    node*next;
    node(){weight = 0;next = NULL;}
    node(int n,int w){NO = n;weight = w;next = NULL;}
};
node* spot[11];
int Distance[11];
bool inQueue[11] = {false};

void init()
{
    for(int i=0;i<11;++i) spot[i] = new node(i,0);
    scanf("%d%d%d%d",&spotNum,&edgeNum,&startNum,&endNum);
    for(int i = 0;i<edgeNum;++i)
    {
        int a,b,p;
        scanf("%d%d%d",&a,&b,&p);
        node *add = new node(b,p);
        node *tmp = spot[a]->next;
        add->next = tmp;
        spot[a]->next = add;
    }
    
}

void solution()
{
    squeue que;
    int i;
    for(i = 0;i<11;++i)Distance[i] = noEdge;
    Distance[startNum] = 0;
    que.enQueue(startNum);
    inQueue[startNum] = true;
    while(!que.isEmpty())
    {
        int v = que.deQueue();
        inQueue[v] = false;
        node*p;
        for(p = spot[v]->next;p != NULL;p = p->next)
        {
            if( (Distance[v] + p->weight) < Distance[p->NO])
            {
                Distance[p->NO] = (Distance[v] + p->weight);
                if(!inQueue[p->NO])
                {que.enQueue(p->NO);inQueue[p->NO] = true;}
            }
        }
    }
    
    cout << Distance[endNum]<<endl;
}

int main()
{
    init();
    solution();
    return 0;
}





