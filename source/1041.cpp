//
//  main.cpp
//  1041
//
//  Created by  on 15/12/4.
#include <iostream>
#include <cstdio>
using namespace std;

struct node{
    int NO = 0;
    int height = 0;
};

node arry[100001];
int cursize = 0;

void insert(int num,int heit)
{
    int index = ++cursize;
    for(;index>1 && heit < arry[index/2].height;index /=2)
        arry[index] = arry[index/2];
    arry[index].NO = num;
    arry[index].height = heit;
}

int findBigThan(int index,int heit)
{
    if(arry[index].NO == 0 && arry[index].height == 0){return 0;}
    if(heit < arry[index].height) //起初没考虑他的下一层可能与他高度相同
    {
        int rootmin = arry[index].NO;
        int leftmin = 0,rightmin = 0;
        if(arry[index*2].height == arry[index].height)
        {leftmin = findBigThan(index*2, heit);}
        if(arry[index*2+1].height == arry[index].height)
        {rightmin = findBigThan(index*2 + 1, heit);}
        if(leftmin !=0) rootmin = min(rootmin,leftmin);
        if(rightmin !=0) rootmin = min(rootmin,rightmin);
        return rootmin;
    }
    else{
        int leftmin = findBigThan(index*2, heit);
        int rightmin  = findBigThan(index*2+1, heit);
        if(leftmin !=0 && rightmin !=0)return min(leftmin,rightmin);
        else return (leftmin !=0 ? leftmin : rightmin);
    }
}

void decrease(int NO,int dec)
{
    int i;
    for(i = 1;i<=cursize;++i){if(arry[i].NO == NO)break;}
    arry[i].height -= dec;
    int heit = arry[i].height;
    for(;i>1 && heit < arry[i/2].height;i/=2)arry[i] = arry[i/2];
    //cout << "i: "<<i<<' '<<arry[i].height<<endl;
    arry[i].NO = NO;
    arry[i].height = heit;
}

int main()
{
    int n,i;
    scanf("%d",&n);
    for(i=1;i<=n;++i)
    {
        int heit;
        scanf("%d",&heit);
        insert(i,heit);
    }
    
    char command[10];
    int order1,order2;
    while(cin >> command)
    {
        switch(command[0])
        {
            case 'f':
            {cin >> order1;cout << findBigThan(1, order1)<<endl;break;}
            case 'd':
            {cin >> order1 >> order2;decrease(order1, order2);}
        }
    }
        
    return 0;
}
