
//  1214
//  Created on 15/10/23.
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
class BinaryTree {
private:
    T value;
    BinaryTree<T> *left;
    BinaryTree<T> *right;
    BinaryTree<T> *father;
public:
    BinaryTree() : left(NULL), right(NULL), father(NULL) {}
    void setLeft(BinaryTree<T> *tree);
    void setRight(BinaryTree<T> *tree);
    void setValue(const T &v);
    BinaryTree *root();
    void preOrder() const;
    void postOrder() const;
    void levelOrder();
};


template <class T>
void BinaryTree<T>::setLeft(BinaryTree<T> *tree)
{   BinaryTree<T> *child = tree;
    while (child != NULL) {
        child -> father = this;
        child = child -> right;
    }
    left = tree;
}

template <class T>
void BinaryTree<T>::setRight(BinaryTree<T> *tree)
{   BinaryTree<T> *tmp = tree;
    while (tmp != NULL) {
        tmp -> father = father;
        tmp = tmp -> right;
    }
    right = tree;
}

template <class T>
void BinaryTree<T>::setValue(const T &v)
{   value = v;
}

template <class T>
BinaryTree<T> *BinaryTree<T>::root()
{   if (father == NULL) return this;
    return father->root();
}

template <class T>
void BinaryTree<T>::preOrder() const
{   cout << value << ' ';
    if (left != NULL) left -> preOrder();
    if (right != NULL) right -> preOrder();
}

template <class T>
void BinaryTree<T>::postOrder() const
{   if (left != NULL) left -> postOrder();
    cout << value << ' ';
    if (right != NULL) right -> postOrder();
}


template <class T>
void BinaryTree<T>::levelOrder()
{   linkQueue<BinaryTree<T> *> queue;
    BinaryTree<T> *tmp = this;
    queue.enQueue(tmp);
    while (!queue.isEmpty())
    {
        tmp = queue.deQueue();
        cout << tmp -> value << ' ';
        if (tmp -> left != NULL)
        {
            tmp = tmp -> left;
            while (tmp != NULL)
            {
                queue.enQueue(tmp);
                tmp = tmp -> right;
            }
        }
    }
}
/***********************************************/
/*---------------------主函数-------------------*/
/***********************************************/
int main() {
    int n;
    cin >> n;
    BinaryTree<int> *array, *tree;
    array = new BinaryTree<int>[n + 1]();
    
    int i,lf,rt,vl;
    
    for (i = 1;i <= n; ++i) {
        cin>> lf >> rt >> vl;
        if (lf) array[i].setLeft(array + lf);
        if (rt) array[i].setRight(array + rt);
        array[i].setValue(vl);
    }
    tree = array[1].root();
    tree -> preOrder();
    cout << endl;
    tree -> postOrder();
    cout << endl;
    tree -> levelOrder();
    return 0;
}

/*
 9
 2 0 1
 5 3 2
 0 4 3
 7 0 4
 0 6 5
 0 0 6
 0 8 7
 0 9 8
 0 0 9
 */
