//
//  main.cpp
//  1047
//
//  Created on 15/10/24.
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

int a[10],c[10];
int b[10][10]
={  0,0,0,0,0,0,0,0,0,0,
    1,1,0,1,1,0,0,0,0,0,
    1,1,1,0,0,0,0,0,0,0,
    0,1,1,0,1,1,0,0,0,0,
    1,0,0,1,0,0,1,0,0,0,
    0,1,0,1,1,1,0,1,0,0,
    0,0,1,0,0,1,0,0,1,0,
    0,0,0,1,1,0,1,1,0,0,
    0,0,0,0,0,0,1,1,1,0,
    0,0,0,0,1,1,0,1,1,0
};

int main()
{
    
    
    for(int i=1;i<=9;i++)
    {
        scanf("%d",a+i);
        a[i]=(a[i]/3)%4;
    }
    for(int i=1;i<=9;i++) cout << a[i]<<endl;
    for(c[1]=0;c[1]<4;c[1]++)
    {
        for(c[2]=0;c[2]<4;c[2]++)
        {
            for(c[3]=0;c[3]<4;c[3]++)
            {
                for(c[4]=0;c[4]<4;c[4]++)
                {
                    for(c[5]=0;c[5]<4;c[5]++)
                    {
                        for(c[6]=0;c[6]<4;c[6]++)
                        {
                            for(c[7]=0;c[7]<4;c[7]++)
                            {
                                for(c[8]=0;c[8]<4;c[8]++)
                                {
                                    for(c[9]=0;c[9]<4;c[9]++)
                                    {
                                        ///check....
                                        bool flag=true;
                                        for(int i=1;i<=9;i++)
                                        {
                                            int t=a[i];
                                            for(int j=1;j<=9;j++)
                                            {
                                                t+=b[j][i-1]*c[j];
                                            }
                                            t=t%4;
                                            if(t)
                                            {
                                                flag=false;
                                                break;
                                            }
                                        }
                                        if(flag)
                                        {
                                            for(int i=1;i<=9;i++)
                                            {
                                                while(c[i]--)
                                                {
                                                    if(flag)
                                                    {
                                                        flag=false;
                                                    }
                                                    else putchar(32);
                                                    printf("%d",i);
                                                }
                                            }
                                            putchar(10);
                                            return 0;
                                        }
                                        else continue;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}
