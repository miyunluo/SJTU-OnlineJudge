//  1203
//  Created on 15/9/26.

#include <iostream>
using namespace std;

template<class T>
struct node{
    T data;
    node* next;
};

template<class T>
class linklist
{
public:
    
    node<T>*head,*tail;
    
    linklist(){
        head = new node<T>;
        tail = new node<T>;
        head->next = tail;
    }
    
    linklist(const linklist&x);
    
    ~linklist(){clear();delete head;delete tail;}
    
    void clear()
    {
        node<T>*p = head->next,*tmp;
        while(p!=tail){
            tmp = p->next;
            delete p;
            p = tmp;
        }
    }
    
    void listin(int n);
    void add(const linklist&a,const linklist&b);
    void display();
};

template<class T>
linklist<T>::linklist(const linklist&x)
{
    node<T>* p = x.head->next,* k = head,*tmp;
    while(p!=x.tail){
        tmp = new node<T>;
        tmp->data = p->data;
        k->next =tmp;
        tmp->next = tail;
        k = tmp;
        p = p->next;
    }
}
template<class T>
void linklist<T>::listin(int n)
{
    node<T>*p = head,*tmp;
    T x;
    for(int i=0;i<n;++i){
        cin >> x;
        tmp = new node<T>;
        tmp->data = x;
        p->next = tmp;
        tmp->next = tail;
        p = tmp;
    }
}
template<class T>
void linklist<T>::add(const linklist&a,const linklist&b)
{
    node<T> *p = head->next,*tmp,*q=a.head->next;
    while (p!=tail) {        //加法这里必须写一个删除操作，不然会错，不知道为什么。
        tmp = p->next;
        delete p;
        p = tmp;
    }
    
    p = head;
    while (q!=a.tail) {
        tmp = new node<T>;
        tmp->data = q->data;
        p->next = tmp;
        p = tmp;
        q = q->next;
    }
    q = b.head->next;
    while (q!=b.tail) {
        tmp = new node<T>;
        tmp->data = q->data;
        p->next = tmp;
        p = tmp;
        q = q->next;
    }
    p->next = tail;
}
template<class T>
void linklist<T>::display()
{
    node<T>*p = head->next;
    while(p!=tail){
        cout<< p->data << ' ';
        p = p->next;
    }
}
//template<class T>
//linklist<T> operator+(const linklist<T>&a,const linklist<T>&b)
//{
//    linklist<T>c;
//    node<T>*p = a.head->next , *q = c.head , *tmp;
//    while(p!=a.tail){
//        tmp = new node<T>;
//        tmp->data = p->data;
//        q->next = tmp;
//        q = tmp;
//        p = p->next;
//    }
//    p = b.head->next;
//    while(p!=b.tail){
//        tmp = new node<T>;
//        tmp->data = p->data;
//        q->next = tmp;
//        q = tmp;
//        p = p->next;
//    }
//    p->next = c.tail;
//    return c;
//}
int main()
{
    char type[7];
    int len1,len2;
    cin >> type >> len1 >>len2;
    
    if(type[0]=='i')
    {
        linklist<int> a,b,c;
        a.listin(len1);
        b.listin(len2);
        c.add(a,b);
        c.display();
    }
    if(type[0]=='c')
    {
        linklist<char> a,b,c;
        a.listin(len1);
        b.listin(len2);
        c.add(a,b);
        c.display();
    }
    if(type[0]=='d')
    {
        linklist<double> a,b,c;
        a.listin(len1);
        b.listin(len2);
        c.add(a,b);
        c.display();
    }
    
    return 0;
}






