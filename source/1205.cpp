//  1205
//  Created on 15/9/30.
#include <iostream>
using namespace std;

int Ackerman(int m,int n)
{
    if(m == 0)return n+1;
    else if(n == 0)return Ackerman(m-1,1);
    else return Ackerman(m-1,Ackerman(m,n-1));
}

int main()
{
    int m,n,result;
    cin >> m >> n;
    result = Ackerman(m,n);
    cout << result;
    return 0;
}
