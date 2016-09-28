#include <iostream>
#include <cstdio>
using namespace std;

struct node{
    int times = 0;
};
node line[2000000][2];

void insert(long long int x)
{
    long long int index = (x>=0 ? x : (-x));
    if(x >=0) {++line[index][0].times;}
    else {++line[index][1].times;}
}

int main()
{
    int n,i,j,num = 0;
    scanf("%d",&n);
    long long int a[501],b[501],c[501],d[501];
    for(i=0;i<n;++i)
    {
        scanf("%lld",&a[i]);
        scanf("%lld",&b[i]);
        scanf("%lld",&c[i]);
        scanf("%lld",&d[i]);
    }
    
    for(i=0;i<n;++i)
        for(j=0;j<n;++j)
            insert(a[i]+b[j]);
    
    for(i=0;i<n;++i)
        for(j=0;j<n;++j)
        {
            long long int tmp = c[i] + d[j];
            if(tmp <= 0)
            {num += line[-tmp][0].times;}
            else
            {num += line[tmp][1].times;}
        }
    
    cout << num << endl;
    return 0;
}