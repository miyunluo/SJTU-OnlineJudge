//  main.cpp
//  1202
//  Created on 15/9/26.
#include <iostream>
using namespace std;

struct node{
    int data;
    node*prev;
    node*next;
};
int main()
{
    node*head1 = new node;
    node*head2 = new node;
    node*head3 = new node;
    node*a = head1;
    node*b = head2;
    node*c = head3;
    node*tail1 = new node;
    node*tail2 = new node;
    node*tail3 = new node;
    int len1 = 0,len2 = 0;
    while(true)
    {
        char n = cin.get();
        if(n != '\n')
        {
            node* p = new node;
            ++ len1;
            p->data = n-'0';
            a->next = p;
            p->next = tail1;
            p->prev = a;
            tail1->prev = p;
            a = p;
        }
        else break;
    }
    while(true)
    {
        char n = cin.get();
        if(n != '\n')
        {
            node* p = new node;
            ++ len2;
            p->data = n-'0';
            b->next = p;
            p->next = tail2;
            p->prev = b;
            tail2->prev = p;
            b = p;
        }
        else break;
    }
    int minlen = min(len1,len2);
    int maxlen = max(len1,len2);
    int i,carry = 0;
    a = tail1->prev;
    b = tail2->prev;
    c = tail3;
    for(i=1;i<=minlen;++i)
    {
        node* q = new node;
        q->data = (a->data + b->data + carry)%10;
        carry = (a->data + b->data + carry)/10;
        c->prev = q;
        q->prev = head3;
        q->next = c;
        head3->next = q;
        c = q;
        
        a = a->prev;
        b = b->prev;
    }
    if(len1>len2)
        for(i=minlen+1;i<=maxlen;++i)
        {
            node* q = new node;
            q->data = (a->data + carry)%10;
            carry = (a->data + carry)/10;
            c->prev = q;
            q->prev = head3;
            q->next = c;
            head3->next = q;
            c = q;
            
            a = a->prev;
        }
    
    if(len2>len1)
        for(i=minlen+1;i<=maxlen;++i)
        {
            node* q = new node;
            q->data = (b->data + carry)%10;
            carry = (b->data + carry)/10;
            c->prev = q;
            q->prev = head3;
            q->next = c;
            head3->next = q;
            c = q;
            
            b = b->prev;
        }
    if(carry!=0)
    {
        node* q = new node;
        q->data = carry;
        c->prev = q;
        q->prev = head3;
        q->next = c;
        head3->next = q;
    }
    
    node*pin = head3->next;
    while(pin!=tail3){
        cout << pin->data;
        pin = pin->next;
    }
    
    return 0;
}









