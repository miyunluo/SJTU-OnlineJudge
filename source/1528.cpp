//
//  main.cpp
//  1528小天狼星的访问
//
//  Created by  on 15/11/27.
#include <iostream>
#include <cstdio>
using namespace std;

struct node{
    node*father;
    node*brother;
    node*son;
    int NO;
    long long int distToFthr;
    node():father(NULL),brother(NULL),son(NULL),NO(0),distToFthr(0){}
};

node* room[100001];
int n,p; // n房间综述  p目标所在房间

void insert()
{
    for(int i=0;i<=100001;++i) room[i] = new node();
    scanf("%d%d",&n,&p);
    
    int s,t;
    long long int l;
    for(int i=0;i<n-1;++i)
    {
        scanf("%d%d",&s,&t);
        scanf("%lld",&l);
        room[s]->NO = s;
        room[t]->NO = t;
        
        room[t]->father = room[s];
        room[t]->distToFthr = l;
        
        if(room[s]->son == NULL)
        {room[s]->son = room[t];}
        else {
            bool flag = false;
            if(room[t]->distToFthr < room[s]->son->distToFthr || (room[t]->distToFthr == room[s]->son->distToFthr && t < room[s]->son->NO)) //插在son前面
            {
                node*tmp = room[s]->son;
                room[s]->son = room[t];
                room[t]->brother = tmp;
                flag = true;
            }
            else {                      //插在兄弟链最后
                node *tmp = room[s]->son;
                while(tmp->brother != NULL)tmp = tmp->brother;
                if(tmp->distToFthr < l || (tmp->distToFthr == l && tmp->NO < t)) {tmp->brother = room[t];flag = true;}
            }
            
            if(!flag)                  //插在中间
            {
                node *tmp = room[s]->son;
                for(;;tmp = tmp->brother)
                {
                    if(tmp->distToFthr < l && tmp->brother->distToFthr > l)break;
                    if(tmp->distToFthr == l && tmp->NO < t && tmp->brother->distToFthr == l &&tmp->brother->NO > t)break;
                    if(tmp->distToFthr == l && tmp->NO < t && tmp->brother->distToFthr > l)break;
                }
                node*temp = tmp->brother;
                tmp->brother = room[t];
                room[t]->brother = temp;
            }
            
        }
    }
}


long long int step()
{
    long long int num = 0;
    node *tmp = room[0];
    
    for(;;)
    {
        if(tmp->son != NULL)
        {
            tmp = tmp->son;
            if(tmp->NO != p) num += tmp->distToFthr;
            else return num + tmp->distToFthr;
        }
        else {
            num += tmp->distToFthr;
            
            node *tmp1 = tmp->brother;
            tmp = tmp->father;
            tmp->son = tmp1;
        }
    }
}

int main()
{
    insert();
    cout<< step()<<endl;
    return 0;
}


