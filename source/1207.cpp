//  1207
//  Created on 15/10/11.
#include <iostream>
#include <stdio.h>
using namespace std;

template <class T>
class queue
{
public:
    virtual bool isEmpty() = 0;
    virtual void enQueue(T x) = 0;//入队
    virtual T deQueue() = 0;//出队
    virtual T getHead() = 0;//读队头元素
    virtual T getRear() = 0;//读队尾元素
    virtual ~queue(){}
};

/*template <class T>
 struct node
 {
 T data;
 node *next;
 };*/

template <class T>
class linkQueue:public queue<T>
{
private:
    struct node
    {
        T data;
        node *next;
        node(const T&x,node*N = NULL){data = x;next = N;}
        node():next(NULL){}
        ~node(){}
    };
    
    node *front,*rear;
    
public:
    linkQueue(){front = rear =NULL;}
    ~linkQueue();
    
    bool isEmpty(){return front == NULL;}
    void enQueue(T x);
    T deQueue();
    T getHead(){return front->data;}//读队头元素
    T getRear(){return rear->data;}//读队尾元素
};

template <class T>
linkQueue<T>::~linkQueue()
{
    node *tmp;
    while(front!=NULL)
    {
        tmp = front;
        front = front->next;
        delete tmp;
    }
}
template <class T>
void linkQueue<T>::enQueue(T x)//入队
{
    if (rear==NULL)front = rear =new node(x);
    
    else{
        rear->next = new node(x);
        rear = rear->next;
    }
}
template <class T>
T linkQueue<T>::deQueue()//出对
{
    node*tmp = front;
    T value = front->data;
    front = front->next;
    if(front == NULL) rear =NULL;
    delete tmp;
    return value;
}


int main()
{
    linkQueue<int> busQueue,vanQueue;
    int n,flag,i;//n为总车辆数
    float busnum = 0,vannum = 0;//各个车辆数
    cin >> n;
    for(i=1;i<=n;++i)
    {
        cin>>flag;
        if(!flag){cin >> flag;busQueue.enQueue(flag);++busnum;}//客车到达时间的队列
        else {cin >> flag;vanQueue.enQueue(flag);++vannum;}//货车到达时间的队列
    }
    int buswait = 0,vanwait = 0;//等待时间
    int currnum;//当前船上的车数
    int timer;//计时器
    
    int tmp = min(busQueue.getHead(),vanQueue.getHead());
    int mintime = (tmp/10)*10;
    if(tmp%10 !=0)mintime += 10;
    
    //tmp = max(busQueue.getRear(),vanQueue.getRear());
    //int maxtime = (tmp/10)*10;
    //if(tmp%10 !=0)maxtime += 10;
    
    for(timer = mintime;!busQueue.isEmpty()||!vanQueue.isEmpty();timer +=10)
    {
        for(currnum =0;currnum<8 && !busQueue.isEmpty() && busQueue.getHead()<=timer; ++currnum){
            buswait += timer - busQueue.deQueue();
        }
        for(;currnum<10 && !vanQueue.isEmpty() && vanQueue.getHead()<=timer; ++currnum){
            vanwait += timer - vanQueue.deQueue();
        }
        for(;currnum<10 && !busQueue.isEmpty() && busQueue.getHead()<=timer; ++currnum){
            buswait += timer - busQueue.deQueue();
        }
    }
    float busaver,vanaver;
    busaver = buswait / busnum;
    vanaver = vanwait / vannum;
    printf("%0.3f",busaver);
    cout<<' ';
    printf("%0.3f",vanaver);
    return 0;
}
