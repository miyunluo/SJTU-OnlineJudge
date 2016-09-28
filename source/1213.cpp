
//  1213
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
    node (T item,T q,node *L=NULL,node*R=NULL) :data(item),quanzhi(q),left(L),right(R){}
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
    int n,m,zero =0;
    cin >> n;
    struct node1{
        int left,right,quan;
    };
    int i;
    node1 in1[100002],in2[100002];
    bool inn1[100002]={0},inn2[100002]={0};
    
    linkQueue<node<int>*>que1;  //用队列生成树
    linkQueue<node<int>*>que2;
    
    node<int>*tmp1,*tmp2;
    int ldata,rdata;
    
    int lf,rt,qa;
    for(i=1;i<=n;++i)
    {
        cin >> lf >> rt >> qa;
        in1[i].left = lf;
        in1[i].right = rt;
        in1[i].quan = qa;
        
        inn1[lf] = 1;
        inn1[rt] = 1;
    }
    
    for(i=1;i<=n;++i) if(!inn1[i]) break;
    
    
    
    
    BinaryTree<int> a;
    a.root = new node<int>(i,in1[i].quan);
    
    que1.enQueue(a.root);
    while(!que1.isEmpty())
    {
        tmp1 = que1.deQueue();
        ldata = in1[tmp1->data].left;    //用[]下标寻找节点
        rdata = in1[tmp1->data].right;
        if(ldata !=0)que1.enQueue(tmp1->left = new node<int>(ldata,in1[ldata].quan));
        else tmp1->left = NULL;
        if(rdata !=0)que1.enQueue(tmp1->right = new node<int>(rdata,in1[rdata].quan));
        else tmp1->right = NULL;
    }
    //*****************************************************//
    cin >> m;
    //cout << m <<endl;
    if(m!=n){cout<<'N';return 0;}
    
    for(i=1;i<=m;++i)
    {
        cin >> lf >> rt >> qa;
        in2[i].left = lf;
        in2[i].right = rt;
        in2[i].quan = qa;
        
        inn2[lf] = 1;
        inn2[rt] = 1;
    }
    
    for(i=1;i<=m;++i) if(!inn2[i]) break;
    
    BinaryTree<int> b;
    b.root = new node<int>(i,in2[i].quan);
    
    que2.enQueue(b.root);
    while(!que2.isEmpty())
    {
        tmp2 = que2.deQueue();
        ldata = in2[tmp2->data].left;    //用[]下标寻找节点
        rdata = in2[tmp2->data].right;
        if(ldata !=0)que2.enQueue(tmp2->left = new node<int>(ldata,in2[ldata].quan));
        else tmp2->left = NULL;
        if(rdata !=0)que2.enQueue(tmp2->right = new node<int>(rdata,in2[rdata].quan));
        else tmp2->right = NULL;
    }
    
    
    que1.enQueue(a.root);
    que2.enQueue(b.root);
    while(!que1.isEmpty()&&!que2.isEmpty())
    {
        tmp1 = que1.deQueue();
        tmp2 = que2.deQueue();
        if(tmp1->quanzhi != tmp2->quanzhi){cout<<'N';return 0;}
        //cout <<tmp1->quanzhi<<" "<<tmp2->quanzhi;
        if(tmp1->left != NULL) que1.enQueue(tmp1->left);
        else{
            if(tmp2->left != NULL){cout<<'N';return 0;}
        }
        if(tmp1->right != NULL) que1.enQueue(tmp1->right);
        else{
            if(tmp2->right != NULL){cout<<'N';return 0;}
        }
        
        if(tmp2->left != NULL) que2.enQueue(tmp2->left);
        if(tmp2->right != NULL) que2.enQueue(tmp2->right);
    }
    
    cout <<'Y';
    return 0;
}