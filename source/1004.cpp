//
//  main.cpp
//  1004
//
//  Created on 15/12/5.
#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    int M,T,U,F,D;
    scanf("%d%d%d%d%d",&M,&T,&U,&F,&D);
    char road;
    int totalTime = 0;
    int path = 0;
    
    for(int i=0;i<T;++i)
    {
        cin >> road;
        if(road == 'u')
        {
            totalTime += U + D;
            if(totalTime > M)break;
            else ++ path;
        }
        if(road == 'f')
        {
            totalTime += F + F;
            if(totalTime > M)break;
            else ++ path;
        }
        if(road == 'd')
        {
            totalTime += U + D;
            if(totalTime > M)break;
            else ++ path;
        }
    }
    printf("%d",path);
    return 0;
}
