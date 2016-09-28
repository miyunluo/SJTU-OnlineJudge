//  main.cpp
//  1217
//  Created on 15/11/4.
#include <iostream>
using namespace std;

int main()
{
    int arr[2501] = {0};
    int n1,n2,num;
    cin >> n1;
    for(int i=1;i<=n1;++i) cin>>arr[i];
    
    cin >> n2;
    for(int i=1;i<=n2;++i)
    {
        cin >> num;
        arr[0] = num;
        int j;
        for(j = n1;j>=0;--j) if(arr[j] == num)break;
        if(!j) cout<<'N'<<endl;
        else cout << 'Y'<<endl;
        
    }
    
    return 0;
}
