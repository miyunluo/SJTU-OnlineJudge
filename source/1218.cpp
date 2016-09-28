//
//  main.cpp
//  1218
//  Created on 15/11/4.
#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class Set {
public:
    T *elem;
    int currsize,maxSize;
    void doubleSpace();
    bool find(T &x)const;
    
    Set(){currsize = 0,maxSize =202,elem = new T[maxSize];}
    ~Set(){delete []elem;}
    Set(const Set<T>&a);
    int getSize(){return currsize;}
    bool insert(T x);  //插入
    bool erase(T &x);   //删除
    void display();    //打印
    
    Set<T>& operator = (const Set<T> &a);
    
    Set<T> jiao(const Set<T> &a,const Set<T> &b); //交
    Set<T> bing(const Set<T> &a,const Set<T> &b); //并
    Set<T> cha(const Set<T> &a,const Set<T> &b); //差

};

template<class T>
void Set<T>::doubleSpace()
{
    maxSize *= 2;
    T *tmp =new T[maxSize];
    for(int i=0;i<currsize;++i) tmp[i] = elem[i];
    delete []elem;
    elem = tmp;
}

template<class T>
bool Set<T>::find(T &x)const
{
    for(int i=0;i<currsize;++i)
        if(elem[i] == x)return true;
    return false;
}

template<class T>
Set<T>::Set(const Set<T> &a)
{
    currsize = a.currsize;
    maxSize = a.maxSize;
    elem = new T[maxSize];
    for(int i=0;i<currsize;++i)elem[i] = a.elem[i];
}

template<class T>
bool Set<T>::insert(T x)
{
    if(find(x))return false;
    if(currsize == maxSize-1) doubleSpace();
    
    elem[currsize++] = x;
    return true;
}

template<class T>
bool Set<T>::erase(T &x)
{
    bool flag = false;
    int i;
    for(i=0;i<currsize;++i)
        if(elem[i] == x){flag = true;break;}
    
    if(flag)
    {
        for(;i<currsize;++i) {elem[i] = elem[i+1];}
        --currsize;
    }
}

template<class T>
void Set<T>::display()
{
    for(int i=0;i<currsize;++i)cout<<elem[i]<<' ';
    cout<<endl;
}

template<class T>
Set<T>& Set<T>::operator = (const Set<T> &a)
{
    currsize = a.currsize;
    maxSize = a.maxSize;
    delete []elem;
    elem = new T[maxSize];
    for(int i=0;i<currsize;++i)elem[i] = a.elem[i];
    return *this;
}

template<class T>
Set<T> jiao(const Set<T> &a,const Set<T> &b)
{
    Set<T> c;
    for(int i=0;i<a.currsize;++i)
    {
        if(b.find(a.elem[i])) c.insert(a.elem[i]);
    }
    return c;
}

template<class T>
Set<T> bing(const Set<T> &a,const Set<T> &b)
{
    Set<T> c = a;
    for(int i=0;i<b.currsize;++i)c.insert(b.elem[i]);
    return c;
}

template<class T>
Set<T> cha(const Set<T> &a,const Set<T> &b)
{
    Set<T> c;
    for(int i=0;i<a.currsize;++i)
        if(!b.find(a.elem[i]))c.insert(a.elem[i]);
    return c;
}

int main()
{
    int n,i,j;
    cin >> n;
    char command;
    int aont,num;
    Set<int> a;
    for(i=0;i<n;++i)
    {
        cin >> command;
        switch(command)
        {
            case '*':
            {
                cin >> aont;
                Set<int>b;
                for(j=0;j<aont;++j){cin >> num;b.insert(num);}
                a = jiao(a,b);
                sort(a.elem,a.elem+a.currsize);
                a.display();
                break;
            }
            case '+':
            {
                cin >> aont;
                Set<int>b;
                for(j=0;j<aont;++j){cin >> num;b.insert(num);}
                a = bing(a,b);
                sort(a.elem,a.elem+a.currsize);
                a.display();
                break;
            }
            case '-':
            {
                cin >> aont;
                Set<int>b;
                for(j=0;j<aont;++j){cin >> num;b.insert(num);}
                a = cha(a,b);
                sort(a.elem,a.elem+a.currsize);
                a.display();
            }
        }
    }
    
    return 0;
}

/*
7
+ 3 1 2 3
- 1 2
+ 3 4 5 6
* 2 1 4
- 2 1 4
+ 1 100
- 1 99
 */




