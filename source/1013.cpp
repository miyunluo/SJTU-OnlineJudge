#include <iostream>
using namespace std;

int main()
{
    int i,n,shizhu[1000000],biaoji[1000000]={0};
    cin >> n;
    for(i=0;i<n;++i) cin >> shizhu[i];

    for(i=0;i<n-1;++i)
        if(shizhu[i]>=0)
    {       shizhu[i+1]+=shizhu[i];biaoji[i+1]=1;}

    int result=0;
    for(i=1;i<n;++i) if(shizhu[i]>result&&biaoji[i]==1) result = shizhu[i];
    if(result<=0) cout << "Game Over";
    else cout << result;
    return 0;
}
