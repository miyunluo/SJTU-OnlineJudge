//
//  main.cpp
//  1316
//  Created on 15/10/18.
#include <iostream>
#include <algorithm>
using namespace std;

struct node
{
    int timevalue; //timevalue用来存储时间值
    int flag;      //flag用来存储是时间区间左边界还是右边界,左为0，右为1
};

node timeline[100000];

bool cmp(node a,node b)
{
    if(a.timevalue == b.timevalue) return a.flag < b.flag;//如果时间值相等左边界在前
    else return a.timevalue < b.timevalue;   //否则以时间值排序
}

int main()
{
    int n;
    cin >> n;
    
    int i,j = 0;
    for(i=0;i<n;++i)
    {
        cin >> timeline[++j].timevalue;
        timeline[j].flag = 0;
        cin >> timeline[++j].timevalue;
        timeline[j].flag = 1;
    }
    
    sort(timeline+1,timeline+1+j,cmp);
    
    int num = 0,leftedge = 0;
    int maxworking = 0,maxfree = 0;
    
    for(i=1;i<=j;++i)
    {
        if(timeline[i].flag == 0) ++num;  
        if(timeline[i].flag == 1) --num;
        
        if(num == 0)     //num为0时遇到一个闭合时间区间
        {
            maxworking = max(maxworking,timeline[i].timevalue - timeline[leftedge+1].timevalue);
            leftedge = i;
            maxfree = max(maxfree,timeline[i+1].timevalue-timeline[i].timevalue);
        }
    }
    
    cout << maxworking<<' '<<maxfree;
    
    return 0;
}
