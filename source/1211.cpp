//  1211
//  Created on 15/10/20.
#include <iostream>
using namespace std;

/***********************************************/
/*------------------链接队列定义-----------------*/
/***********************************************/
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

/***********************************************/
/*------------------二叉树类定义-----------------*/
/***********************************************/

template <class T>
struct node{
    node *left,*right;
    T data;
    
    node():left(NULL),right(NULL){}
    node(T item,node *L=NULL,node*R=NULL):data(item),left(L),right(R){}
    ~node(){}
};

template <class T>
class BinaryTree {
public:
    node<T> *root;
    
    BinaryTree():root(NULL){}
    BinaryTree(const T&value){root = new node<T>(value);}
    ~BinaryTree(){clear();}
    
    T getRoot(){return root->data;}
    T getLeft(){return root->left->data;}
    T getRight(){return root->right->data;}
    void clear()
    {
        if(root != NULL) clear(root);
        root = NULL;
    }
    
    bool isCompleteTree();
private:
    void clear(node<T> *t)const
    {
        if(t->left != NULL)clear(t->left);
        if(t->right != NULL)clear(t->right);
        delete t;
    }

};

template <class T>
struct elem{
    node<T> *p;
    int num;
};

template <class T>
bool BinaryTree<T>::isCompleteTree()
{
    linkQueue< elem<T> > que;
    elem<T> current,child;
    int count = 1;
    int last = 1;
    
    if(root == NULL) return true;
    
    current.p = root;
    current.num = 1;
    que.enQueue(current);
    
    while(!que.isEmpty())
    {
        current = que.deQueue();
        if(current.p->left != NULL){
            ++count;
            child.p = current.p->left;
            last = child.num = current.num *2;
            que.enQueue(child);
        }
        if(current.p->right != NULL){
            ++count;
            child.p = current.p->right;
            last = child.num = current.num *2 + 1;
            que.enQueue(child);
        }
    }
    return count == last;
}

/***********************************************/


int main()
{
    int n,i,j;
    cin >> n;
    
    struct node1{
        int left,right;
    };
    
    node1 in[100002];
    bool inn[n+1];
    for(i=0;i<=n;++i) inn[i] = 0;
    for(i=1;i<=n;++i)
    {
        cin >> in[i].left >>in[i].right;
        inn[in[i].left] = 1;
        inn[in[i].right] = 1;
    }
    
    for(i=1;i<=n;++i) if(!inn[i]) break;
    
    /*bool flag = false;
    for(i=1;i<=n;++i){    //对于编号 1-n 的点,没有在数据中出现的点就是根
        for(j=1;j<=n;++j)
        {
            if(in[j].left == i || in[j].right == i) break;
            if(j == n) flag = true;
        }
        if(flag)break;
    }*/
    
    linkQueue<node<int>*>que;  //用队列生成树
    node<int>*tmp;
    int ldata,rdata;
    
    BinaryTree<int> a;
    a.root = new node<int>(i); //in[i]为root
    que.enQueue(a.root);
    
    while(!que.isEmpty())
    {
        tmp = que.deQueue();
        ldata = in[tmp->data].left;    //用[]下标寻找节点
        rdata = in[tmp->data].right;
        if(ldata !=0)que.enQueue(tmp->left = new node<int>(ldata));
        else tmp->left = NULL;
        if(rdata !=0)que.enQueue(tmp->right = new node<int>(rdata));
        else tmp->right = NULL;
        
        /*cout << "tmp->data:"<<tmp->data<<endl;
        if(tmp->left !=NULL)cout <<tmp->left->data ;
        else cout <<"null";
        if(tmp->right !=NULL)cout <<tmp->right->data ;
        else cout <<"null";
        cout <<endl;*/
    }
    
    if(a.isCompleteTree())cout <<'Y';   //判断
    else cout << 'N';
    
    return  0;
}





