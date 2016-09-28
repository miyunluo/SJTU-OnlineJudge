//
//  main.cpp
//  1003
//
//  Created on 15/12/6.

#include <iostream>
#include <cstdio>
using namespace std;

int pymin[101][101];
int L;

void init()
{
    scanf("%d",&L);
    
    for(int i=1;i<=L;++i)
        for(int j=1;j<=L;++j)scanf("%d",&pymin[i][j]);
}

int solution()
{
    int i,j,times = 0;
    int unable = 0;
    for(i=1;i<=L;++i)
        for(j=1;j<=L;++j)
        {if(pymin[i][j] == 2)++unable;}
    
    for(;;)
    {
        int zbiao[20001],index = 0;
        for(i=1;i<=L;++i)
            for(j=1;j<=L;++j)
            {
                if(pymin[i][j] == 1){zbiao[index++] = i;zbiao[index++] = j;}
            }
        
        if((index/2 + unable) == (L*L) )break;
        
        for(i=0;i<index;i +=2)
        {
            int x = zbiao[i];
            int y = zbiao[i+1];
            if(y-1 >=1 && pymin[x][y-1] != 2)pymin[x][y-1] = 1;
            if(y+1 <=L && pymin[x][y+1] != 2)pymin[x][y+1] = 1;
            if(x-1 >=1 && pymin[x-1][y] != 2)pymin[x-1][y] = 1;
            if(x+1 <=L && pymin[x+1][y] != 2)pymin[x+1][y] = 1;
        }
        ++times;
        /*
        for(int a=1;a<=L;++a)
            for(int b=1;b<=L;++b)
            {
                cout << pymin[a][b] <<' ';
                if(b == L) cout <<endl;
            }
        cout<<endl;
        */
    }
    return times;
}

int main()
{
    init();
    cout<<solution();
    return 0;
}

/*
 4
 0 0 0 0
 0 2 0 0
 2 1 0 0
 0 0 0 0
 
 1
 1
 */

