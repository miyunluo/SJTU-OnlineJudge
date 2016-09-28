
//  1212
//  Created on 15/10/22.
#include <iostream>
using namespace std;

/***********************************************/
/*------------------链接队列定义-----------------*/
/***********************************************/

template <class T>
class linkQueue
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
    T data,quanzhi;
    
    node():left(NULL),right(NULL){}
    node(T item,T q,node *L=NULL,node*R=NULL):data(item),quanzhi(q),left(L),right(R){}
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
    
private:
    void clear(node<T> *t)const
    {
        if(t->left != NULL)clear(t->left);
        if(t->right != NULL)clear(t->right);
        delete t;
    }
    
};
/***********************************************/

int main()
{
    int n;
    cin >> n;
    struct node1{
        int left,right,quan;
    };
    int i;
    node1 in[100002];
    bool inn[100002]={0};
    
    int lf,rt,qa;
    for(i=1;i<=n;++i)
    {
        cin >> lf >> rt >> qa;
        in[i].left = lf;
        in[i].right = rt;
        in[i].quan = qa;
        
        inn[lf] = 1;
        inn[rt] = 1;
    }
    
    for(i=1;i<=n;++i) if(!inn[i]) break;
    
    node<int>*tmp;
    int ldata,rdata;
    linkQueue<node<int>*>que;  //用队列生成树
    
    BinaryTree<int> a;
    a.root = new node<int>(i,in[i].quan);
    
    que.enQueue(a.root);
    while(!que.isEmpty())
    {
        tmp = que.deQueue();
        ldata = in[tmp->data].left;    //用[]下标寻找节点
        rdata = in[tmp->data].right;
        if(ldata !=0)que.enQueue(tmp->left = new node<int>(ldata,in[ldata].quan));
        else tmp->left = NULL;
        if(rdata !=0)que.enQueue(tmp->right = new node<int>(rdata,in[rdata].quan));
        else tmp->right = NULL;
    }
    
    que.enQueue(a.root);
    while(!que.isEmpty())
    {
        tmp = que.deQueue();
        if (tmp->left != NULL) que.enQueue(tmp->left);
        if (tmp->right != NULL) que.enQueue(tmp->right);
        cout << tmp->quanzhi << ' ';
    }
    
    return 0;
}



