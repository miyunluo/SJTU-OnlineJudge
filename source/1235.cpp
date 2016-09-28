#include <iostream>
using namespace std;

const int MAX=10000;


//优先级队列的定义
template<class T>
class priorityQueue
{
private:
    int currentSize;
    T *array;
    int maxSize;
    
    void buildHeap()
    {
        for(int i=currentSize/2;i>0;i--) percolateDown(i);
    }
    
    void percolateDown(int hole)
    {
        int child;
        T tmp=array[hole];
        
        for(;hole*2<=currentSize;hole=child)
        {
            child=hole*2;
            if(child!=currentSize&&array[child+1]<array[child]) child++;
            if(array[child]<tmp) array[hole]=array[child];
            else break;
        }
        array[hole]=tmp;
    }
    
    void doubleSpace()
    {
        T *tmp=array;
        
        maxSize*=2;
        array=new T[maxSize];
        
        for(int i=0;i<=currentSize;i++) array[i]=tmp[i];
        
        delete [] tmp;
    }
    
    
public:
    priorityQueue(int capacity=100) {array=new T[capacity];maxSize=capacity;currentSize=0;}
    priorityQueue(const T data[],int size)
    {
        maxSize=size+10;
        currentSize=size;
        array=new T[maxSize];
        for(int i=0;i<size;i++) array[i+1]=data[i];
        buildHeap();
    }
    ~priorityQueue() {delete [] array;}
    
    bool isEmpty() const {return currentSize==0;}
    void enQueue(const T &x)
    {
        if(currentSize==maxSize-1) doubleSpace();
        //向上过滤
        int hole=++currentSize;
        for(;hole>1&&array[hole/2]>x;hole/2) array[hole]=array[hole/2];
        array[hole]=x;
    }
    
    T deQueue()
    {
        T minItem;
        minItem=array[1];
        array[1]=array[currentSize--];
        percolateDown(1);
        return minItem;
    }
    
    T getHead() const {return array[1];}
};

//邻接表图类的定义
template<class TV,class TE>
class adjListGraph
{
public:
    adjListGraph(int vSize,const TV d[]);
    bool insert(int u,int v,TE w);
    int numOfVer() {return vers;}
    int numofEdge() {return edges;}
    ~adjListGraph();
    void dijkstra(int start,int end);
    void printPath(int start,int end,int prev[]);
    
private:
    struct edgeNode
    {
        int end;//到达结点的编号
        TE weight;//边的权值
        edgeNode *next;
        
        edgeNode(int e,TE w,edgeNode *n=NULL) {end=e;weight=w;next=n;}
    };
    
    struct verNode
    {
        TV ver;//顶点值
        edgeNode *head;//对应的链表的头指针,即代表现在头指针指向自己
        
        verNode(edgeNode *h=NULL) {head=h;}
    };
    
    verNode *verList;//存储顶点的数组
    int vers;
    int edges;
};
//

//构造函数的实现
template<class TV,class TE>
adjListGraph<TV,TE>::adjListGraph(int vSize,const TV d[])
{
    vers=vSize;edges=0;
    
    verList=new verNode[vSize];
    for(int i=0;i<vers;i++) verList[i].ver=d[i];
}
//

//析构函数的实现
template<class TV,class TE>
adjListGraph<TV,TE>::~adjListGraph()
{
    int i;
    edgeNode *p;
    
    for(i=0;i<vers;i++)
    {//释放第i个结点的单链表
        while((p=verList[i].head)!=NULL)
        {
            verList[i].head=p->next;
            delete p;
        }
    }
    
    delete [] verList;
}
//

//插入函数的实现
template<class TV,class TE>
bool adjListGraph<TV,TE>::insert(int u,int v,TE w)
{
    verList[u].head=new edgeNode(v,w,verList[u].head);//直接将新增的边连在对应单链表的表头
    ++edges;
    return true;
}
//


template<class TV,class TE>
void adjListGraph<TV,TE>::dijkstra(int start,int end)
{
    int *distance=new int[vers];
    int *prev=new int[vers];
    int *num=new int[vers];
    bool *known=new bool[vers];
    
    int u,sNo;
    edgeNode *p;
    int min;
    
    for(int i=0;i<vers;i++)//初始化
    {
        known[i]=false;
        distance[i]=MAX;
        num[i]=0;
    }
    
    sNo=start-1;
    distance[sNo]=0;//起始节点自己到自己的距离为0
    prev[sNo]=sNo;//起始节点的前继结点就是自己
    for(int i=1;i<vers;i++)//寻找具有最短距离的节点
    {
        min=MAX;
        for(int j=0;j<vers;j++)
            if(!known[j]&&distance[j]<min)
            {
                min=distance[j];
                u=j;
            }
        known[u]=true;//将u放入已经找到最短距离的结点集s
        for(p=verList[u].head;p!=NULL;p=p->next)//更新u的邻接点距离
        {
            if(!known[p->end]&&(distance[p->end]>min+p->weight
                                ||distance[p->end]==min+p->weight&&num[p->end]>num[u]+1))
            {
                distance[p->end]=min+p->weight;
                prev[p->end]=u;
                num[p->end]=num[u]+1;
            }
        }
    }
    
    cout<<distance[end-1]<<endl;
    printPath(sNo,end-1,prev);
}

template<class TV,class TE>
void adjListGraph<TV,TE>::printPath(int start,int end,int prev[])
{
    if(start==end) {cout<<verList[start].ver;return;}
    printPath(start,prev[end],prev);
    cout<<' '<<verList[end].ver;
}

int main()
{
    int n,m,start,end;
    cin>>n>>m>>start>>end;
    
    int *point=new int[n];
    for(int i=0;i<n;i++) point[i]=i+1;
    
    adjListGraph<int,int> graph(n,point);
    
    int beg,over,weight;
    for(int i=0;i<m;i++)
    {
        cin>>beg>>over>>weight;
        graph.insert(beg-1,over-1,weight);
    }
    //
    
    graph.dijkstra(start,end);
    
    return 0;
}