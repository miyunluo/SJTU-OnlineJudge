//
//  main.cpp
//  1024
//
//  Created on 15/12/5.
#include <iostream>
#include <cstdio>
using namespace std;

int lisst[10001];

void quick_sort(int s[], int l, int r)
{
    if (l < r)
    {
        //Swap(s[l], s[(l + r) / 2]); //将中间的这个数和第一个数交换 
        int i = l, j = r, x = s[l];
        while (i < j)
        {
            while(i < j && s[j] >= x) // 从右向左找第一个小于x的数
                j--;
            if(i < j)
                s[i++] = s[j];
            
            while(i < j && s[i] < x) // 从左向右找第一个大于等于x的数
                i++;
            if(i < j)
                s[j--] = s[i];
        }
        s[i] = x;
        quick_sort(s, l, i - 1); // 递归调用
        quick_sort(s, i + 1, r);
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    int i,j;
    for(i = 0;i<n;++i)scanf("%d",&lisst[i]);
    
    quick_sort(lisst, 0, n-1);
    /*
    for(i=1;i<=n;++i){
        bool flag = false;
        for(j=0;j<=n-1-i;++j)
        {
            if(lisst[j]>lisst[j+1])
            {int tmp = lisst[j];lisst[j] = lisst[j+1];lisst[j+1] = tmp;flag = true;}
        }
        if(!flag)break;
    }
     */
    
    for(i = 0;i<n;++i)printf("%d ",lisst[i]);
}
