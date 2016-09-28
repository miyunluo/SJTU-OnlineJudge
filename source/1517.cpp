//
//  main.cpp
//  1517
//  Created on 15/11/5.
#include <iostream>
using namespace std;

char a[100001],b[100001];
char c[100001],d[100001],e[100001];


void sub(char c[],int len1,char d[],int len2)
{
    int i,carry = 0,tmp;
    for(i=0;i<len2;++i)
    {
        tmp = (c[i]-'0') - (d[i]-'0') + carry;
        if(tmp < 0){tmp += 10;carry = -1;}
        else carry = 0;
        e[i] = tmp +'0';
    }
    
    while(i<len1)
    {
        tmp = c[i]-'0' + carry;
        if(tmp < 0){tmp += 10;carry = -1;}
        else carry = 0;
        e[i] = tmp +'0';
        ++i;
    }
    e[i] = '\0';
}



int main()
{
    cin >> a >> b;
    int lena,lenb;
    int i,j;
    
    for(i=0;a[i]!='\0';++i);
    lena = i;
    //cout <<"lena:"<<lena<<endl;
    for(j=0;j<i;++j) c[j] = a[i-j-1];
    c[j] = '\0';
    //cout <<"c:"<<c<<endl;
    
    for(i=0;b[i]!='\0';++i);
    lenb = i;
    //cout <<"lenb:"<<lenb<<endl;
    for(j=0;j<i;++j) d[j] = b[i-j-1];
    d[j] = '\0';
    //cout <<"d:"<<d<<endl;
    
    bool flag = true,immd = false;
    if(lena > lenb)flag = true;
    else if(lena < lenb)flag = false;
    else{
        for(i=0;i<lena;++i)
        {
            if(a[i] == b[i])continue;
            if(a[i] > b[i]) {flag = true;break;}
            if(a[i] < b[i]) {flag = false;break;}
        }
        
        if(i == lena) {flag = true;immd = true;}
    }
    
    //cout <<"flag:"<<flag<<' '<<"i:"<<i<<endl;
    
    if(immd){cout<<'0';return 0;}
    
    int maxlen = max(lena,lenb);
    if(flag) sub(c, lena, d, lenb);
    else sub(d,lenb,c,lena);
    
    //cout <<"e:"<<e<<endl;
    
    if(!flag)cout<<'-';
    for(i = maxlen-1;i>=0 &&e[i] == '0';--i);
    for(j = i;j>=0;--j)cout << e[j];
    
    return 0;
}


/*
111111111
987654321
*/