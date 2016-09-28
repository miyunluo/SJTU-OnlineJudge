//
//  main.cpp
//  1052
//
//  Created on 15/12/5.
#include <iostream>
#include <cstdio>
using namespace std;

int sett[101][201];
int numOfEach[101];
int n;
void init()
{
    scanf("%d",&n);
    int i,j;
    for(i=0;i<101;++i)
        for(j=0;j<201;++j)  sett[i][j] = -1;
    
    for(i=1;i<=n;++i)scanf("%d",&numOfEach[i]);
    
    for(i=1;i<=n;++i)
        for(j=1;j<=numOfEach[i];++j)
        {
            int num;scanf("%d",&num);
            if(sett[i][num] == -1) sett[i][num] = 0;
            else continue;
        }
}

void bing(int index1,int index2)
{
    for(int i=0;i<=200;++i)
    {
        if(sett[index1][i] == -1 && sett[index2][i] == 0)
        {sett[index1][i] = 0;}
    }
}

void jiao(int index1,int index2)
{
    for(int i=0;i<=200;++i)
    {
        if(sett[index1][i] ==0)
        {
            if(sett[index2][i] == 0)continue;
            else sett[index1][i] = -1;
        }
        else continue;
    }
}

void cha(int index1,int index2)
{
    for(int i=0;i<=200;++i)
    {
        if(sett[index1][i] == 0)
        {
            if(sett[index2][i] == 0)sett[index1][i] = -1;
            else continue;
        }
        else continue;
    }
}

void solution()
{
    int num,index1,index2;
    char alph;
    scanf("%d",&num);
    for(int i=0;i<num;++i)
    {
        cin >> alph;
        switch(alph)
        {
            case '+':
                cin >> index1 >>index2;
                bing(index1,index2);
                break;
            case '*':
                cin >> index1 >>index2;
                jiao(index1,index2);
                break;
            case '-':
                cin >> index1 >>index2;
                cha(index1,index2);
                break;
        }
    }
}
void display()
{
    for(int i=1;i<=n;++i){
        for(int j = 0;j<=200;++j)
        {
            if(sett[i][j] != -1) cout << j <<' ';
        }
        cout << endl;
    }
}
int main()
{
    init();
    solution();
    display();
    return 0;
}
