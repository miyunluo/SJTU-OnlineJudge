//
//  main.cpp
//  1227
//  Created on 15/11/21.
#include <iostream>
#include <cstdio>
using namespace std;

template<class T>
struct node{
    T data;
    node *next;
    node(){next = NULL;}
    node(T d):data(d){next = NULL;}
};
template<class T>
void sort(node<T> *p)
{
    node<T>*last,*pos,*minp,*tmp;
    T min;
    
    if(p->next == NULL || p->next->next == NULL)return;
    for(last = p;last->next != NULL;last = last->next)
    {
        minp = last;
        min = minp->next->data;
        for(pos = last->next;pos->next!=NULL;pos = pos->next)
        {
            if(pos->next->data < min){minp = pos;min = pos->next->data;}
        }
        if (minp == last)continue;
        
        tmp = minp->next;
        minp->next = tmp->next;
        tmp->next = last->next;
        last->next = tmp;
    }
}

int main()
{
    int n,num;
    scanf("%d",&n);
    node<int> *p,*head;
    head = p = new node<int>;
    for(int i=0;i<n;++i)
    {
        scanf("%d",&num);
        node<int> *tmp = new node<int>(num);
        p->next = tmp;
        p = p->next;
    }
    sort(head);
    p = head;
    while(p->next !=NULL){cout<<p->next->data<<' ';p = p->next;}
    return 0;
}
