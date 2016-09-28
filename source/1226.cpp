//
//  main.cpp
//  1226
//  Created on 15/11/21.
#include <iostream>
using namespace std;

void quickSort(int s[],int l,int r)
{
    if(l<r){
        int i = l,j = r,tmp = s[i];
        while(i < j)
        {
            while(i < j && s[j] >= tmp) --j;
            if(i < j) s[i++] = s[j];
            
            while(i < j && s[i] < tmp) ++i;
            if(i < j) s[j--] = s[i];
        }
        s[i] = tmp;
        quickSort(s, l, i-1);
        quickSort(s, i+1, r);
    }
}

int main()
{
    int n,i;
    int s[100000];
    cin >> n;
    for(i=0;i<n;++i)cin>>s[i];
    quickSort(s, 0, n-1);
    for(i=0;i<n;++i)cout<<s[i]<<' ';
    return 0;
}
