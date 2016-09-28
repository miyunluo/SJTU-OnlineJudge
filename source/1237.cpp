//
//  main.cpp
//  1237拓扑排序
//
//  Created on 15/12/18.
#include <cstdio>
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

struct node{
    int NO;
    node *next;
    
    node(){next = NULL;}
    node(int n){NO = n;next = NULL;}
};

node* spot[10002];
int spotNum,command;
int inDgree[10002] = {0};
int xueqi = 0;

void init()
{
    for(int i=0;i<10002;++i)spot[i] = new node(i);
    scanf("%d%d",&spotNum,&command);
    for(int i=0;i<command;++i)
    {
        int latter,formmer;
        scanf("%d%d",&latter,&formmer);
        
        ++ inDgree[latter];
        
        node *tmp = new node(latter);
        tmp->next = spot[formmer]->next;
        spot[formmer]->next = tmp;
        //cout << spot[formmer]->next ->NO<<endl;
    }
}

void solution()
{
    squeue q,qq;
    for(int i=1;i <= spotNum;++i)
    {if(inDgree[i] == 0) q.enQueue(i);}
    
    while(!q.isEmpty())
    {
        while(!q.isEmpty())
        {
            int current = q.deQueue();
            //cout <<"current:"<<current<<endl;
            node *p;
            for(p = spot[current]->next;p != NULL;p = p->next)
            {if(--inDgree[p->NO] == 0) qq.enQueue(p->NO);}
        }
        
        ++xueqi;
        
        while(!qq.isEmpty())
        {
            int k = qq.deQueue();
            q.enQueue(k);
        }
        
    }
    
    cout << xueqi <<endl;
}

int main()
{
    init();
    solution();
    return 0;
}



