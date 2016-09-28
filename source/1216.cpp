#include <iostream>
using namespace std;

template <class T>
class priorityQueue
{
private:
    int currentSize; // 队列长度
    T *arr;          //数组首地址
    int maxSize;     //最大容量
    
    void doubleSpace(); //扩容
    void percolateDown(int hole); //向下过滤
    
    
public:
    priorityQueue(int capacity = 100)
    {arr = new T[capacity];maxSize = capacity;currentSize = 0;}
    ~priorityQueue(){delete []arr;}
    void enQueue(const T &x);
    T deQueue();
    int find(T &x);             //找出优先级值大于x的最小的元素，输出其下标。如果有多个元素优先级值相同输出下标最小的那个
    void decrease(int k, T v);  //将第k个节点的优先级值减少v
};

template<class T>
void priorityQueue<T>::doubleSpace()
{
    T*tmp = arr;
    maxSize *= 2;
    arr = new T[maxSize];
    for(int i=1;i<=currentSize;++i) arr[i] = tmp[i];
    delete []tmp;
}

template <class T>
void priorityQueue<T>::enQueue(const T &x)
{
    if(currentSize == maxSize-1) doubleSpace();
    //向上过滤
    int hole = ++currentSize;
    for(;hole>1 && x<arr[hole/2]; hole /=2){arr[hole] = arr[hole/2];}
    
    arr[hole] = x;
}

template <class T>
void priorityQueue<T>::percolateDown(int hole)
{
    int child;
    T tmp = arr[hole];
    for(;hole*2<= currentSize;hole = child)
    {
        child = hole * 2;
        if(child != currentSize && arr[child+1] < arr[child]) child++;
        if(arr[child] < tmp) arr[hole] = arr[child];
        else break;
    }
    arr[hole] = tmp;
}

template <class T>
T priorityQueue<T>::deQueue()
{
    T minItme;
    minItme = arr[1];
    
    arr[1] = arr[currentSize--];
    
    percolateDown(1);
    
    return minItme;
}


template <class T>
int priorityQueue<T>::find(T &x)
{
    int i,a = 0;
    T tmp = x;
    for(i=1;i<=currentSize;++i)
    {
        if(arr[i] > x)
        {
            if(tmp == x||arr[i] < tmp){tmp = arr[i]; a = i;}
        }
    }
    
    return a;
}

template<class T>
void priorityQueue<T>::decrease(int k, T v)
{
    T tmp = arr[k] - v;
    //向上过滤
    int hole = k;
    for(;hole>1 && tmp < arr[hole/2]; hole /=2){arr[hole] = arr[hole/2];}
    
    arr[hole] = tmp;
}

int main()
{
    int n,i,a,b;
    cin >> n;
    char command[10];
    priorityQueue<int> que;
    for(i=0;i<n;++i)
    {
        cin >> command;
        switch(command[0])
        {
            case 'i':{cin >>a;que.enQueue(a);break;}
            case 'f':{cin >> a;cout <<que.find(a)<<endl;break;}
            case 'd':{cin >>a>>b;que.decrease(a,b);}
        }
    }
    return 0;
}

