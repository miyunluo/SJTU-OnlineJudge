//
//  main.cpp
//  1225
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
    int n,amount;
    int s[100000];
    cin >> n;
    for(int i=0;i<n;++i)cin>>s[i];
    quickSort(s, 0, n-1);
    if(n == 0){cout << 0<<'\n';return 0;}
    else{
        amount = 1;
        for(int i=1;i<n;++i)
        {
            if(s[i]!=s[i-1])++amount;
        }
        cout << amount<<'\n';
    }
    return 0;
}