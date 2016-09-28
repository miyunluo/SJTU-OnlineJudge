
#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

template <class T>
struct node{
    T data;
    node *son,*brother;
    node(T d,node *s = NULL,node *b = NULL):data(d),son(s),brother(b){}
};

template<class T>
class Binomial
{
private:
    node<T> **forest;
    int noOfTree;
    node<T>* merge(node<T> *t1,node<T> *t2);
    int findmin();
    void deleteTree(node<T>*t);
public:
    Binomial(int n = 10000);
    ~Binomial();
    bool isEmpty();
    void enQueue(const T &x);
    T deQueue();
    T getHead();
    void merge(Binomial & other);
};

template<class T>
node<T>* Binomial<T>::merge(node<T> *t1,node<T> *t2)
{
    node<T> *min = (t1->data < t2->data)? t1:t2;
    node<T> *max = (t1->data < t2->data)? t2:t1;
    node<T> *tmp;
    
    if(min->son == NULL) {min->son = max;}
    else{
        tmp = min->son;
        while(tmp->brother != NULL) tmp = tmp->brother;
        
        tmp->brother = max;
    }
    return min;
}

template<class T>
int Binomial<T>:: findmin()
{
    int min,i;
    for(min = 0;min<noOfTree && forest[min] == NULL;++min);
    for(i = min;i < noOfTree;++i)
    {if(forest[i] !=NULL && forest[i]->data < forest[min]->data) min = i;}
    return min;
}

template<class T>
void Binomial<T>::deleteTree(node<T>*t)
{
    node<T> *son = t->son, *tmp;
    while(son != NULL)
    {
        tmp = son;
        son = son->brother;
        deleteTree(tmp);
    }
    delete t;
}

template<class T>
Binomial<T>::Binomial(int n)
{
    noOfTree = int(log(n)/log(2)) + 1;
    forest = new node<T>*[noOfTree];
    for(int i=0;i<noOfTree;++i) forest[i] = NULL;
}

template<class T>
Binomial<T>::~Binomial()
{
    for(int i=0;i<noOfTree;++i)
    {if(forest[i] != NULL) deleteTree(forest[i]);}
    delete []forest;
}

template<class T>
bool Binomial<T>::isEmpty()
{
    for(int i=0;i<noOfTree;++i){if(forest[i] != NULL) return false;}
    return true;
}

template<class T>
void Binomial<T>::enQueue(const T &x)
{
    Binomial tmp(1);
    tmp.forest[0] = new node<T>(x);
    
    merge(tmp);
}

template<class T>
T Binomial<T>::deQueue()
{
    int min = findmin();
    T data = forest[min]->data;
    if(min == 0)
    {
        delete forest[min];
        forest[min] = NULL;
        return data;
    }
    
    node<T> *son,*brother;
    Binomial tmp(int(pow(2,min)) -1);
    son = forest[min]->son;
    delete forest[min];
    forest[min] = NULL;
    
    int i = 0;
    do{
        tmp.forest[i++] = son;
        brother = son->brother;
        son->brother = NULL;
    }while( (son = brother)!= NULL);
    
    merge(tmp);
    return data;
}

template<class T>
T Binomial<T>::getHead()
{
    int m = findmin();
    return forest[m]->data;
}


template<class T>
void Binomial<T>::merge(Binomial & other)
{
    node<T> **tmp = forest, *carry = NULL;
    int tmpSize = noOfTree;
    int min = ((noOfTree < other.noOfTree)? noOfTree : other.noOfTree);
    int i;
    if (noOfTree == min) {
        noOfTree = other.noOfTree;
        if (other.forest[noOfTree-1] != NULL) ++noOfTree;
    }
    else {
        if (forest[noOfTree-1] != NULL) ++noOfTree;
    }
    forest = new node<T> *[noOfTree];
    for (i = 0; i < noOfTree; ++i) forest[i] = NULL;
    for (i = 0; i < min; ++i) {
        if (carry == NULL) {
            if (tmp[i] == NULL) forest[i] = other.forest[i];
            else carry = merge(other.forest[i], tmp[i]);
        }
        else {
            if (tmp[i] != NULL && other.forest[i] != NULL) {
                forest[i] = carry;
                carry = merge(other.forest[i], tmp[i]);
            }
            else {
                if (tmp[i] == NULL && other.forest[i] == NULL) {
                    forest[i] = carry;
                    carry = NULL;
                }
                else {
                    if (tmp[i] == NULL) carry = merge(other.forest[i], carry);
                    else carry = merge(tmp[i], carry);
                }
            }
        }
    }
    if (other.noOfTree == min) {
        for (; i < tmpSize; ++i) {
            if (carry == NULL) forest[i] = tmp[i];
            else {
                if (tmp[i] == NULL) {
                    forest[i] = carry;
                    carry = NULL;
                }
                else carry = merge(tmp[i], carry);
            }
        }
    }
    else {
        for (; i < other.noOfTree; ++i) {
            if (carry == NULL) forest[i] = other.forest[i];
            else {
                if (other.forest[i] == NULL) {
                    forest[i] = carry;
                    carry = NULL;
                }
                else carry = merge(other.forest[i], carry);
            }
        }
    }
    if (carry != NULL) forest[i] = carry;
    for (i = 0; i < other.noOfTree; ++i) other.forest[i] = NULL;
    delete [] tmp;
}

int main()
{
    int n,num,i;
    Binomial<int> que;
    char command[10];
    cin >> n;
    for(i=0;i<n;++i)
    {
        cin >> command;
        switch(command[0])
        {
            case 'i':{
                cin >> num;
                que.enQueue(num);break;}
            case 'd':{
                que.deQueue();break;}
            case 'm':{
                cout<< que.getHead()<<endl;}
        }
    }
    
    return 0;
}






