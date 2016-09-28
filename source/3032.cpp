
//  Created  on 15/10/3.

#include<iostream>
#include<cstring>
using namespace std;

class HugeInt
{
    friend HugeInt operator+(const HugeInt&r1,const HugeInt&r2);
    friend HugeInt operator-(const HugeInt&r1,const HugeInt&r2);
    friend HugeInt operator*(const HugeInt&r1,const HugeInt&r2);
    friend bool operator>(const HugeInt&r1,const HugeInt&r2);
    friend bool operator>=(const HugeInt&r1,const HugeInt&r2);
    friend bool operator<=(const HugeInt&r1,const HugeInt&r2);
    friend bool operator!=(const HugeInt&r1,const HugeInt&r2);
    friend bool operator==(const HugeInt&r1,const HugeInt&r2);
    friend bool operator<(const HugeInt&r1,const HugeInt&r2);
    //friend istream&operator>>(istream&is,const HugeInt&obj);
    friend ostream&operator<<(ostream&os,const HugeInt&obj);
public:
    int len;
    char *data;
    
    HugeInt(const char*str);
    HugeInt(const HugeInt&r);
    HugeInt& operator=(const HugeInt&r);
    ~HugeInt(){delete[]data;}
};

HugeInt::HugeInt(const char*str)
{
    int k=0;
    while(str[k]=='0' && k<strlen(str))++k;
    
    if(k == strlen(str))
    {
        len = 1;
        data = new char[2];
        data[0] = '0';
        data[1] = '\0';
    }
    else{
        len = strlen(str) - k;
        
        data = new char[len+1];
        for(int i=0;i<len;++i)
            data[i] = str[len+k-1-i];
        data[len] = '\0';
    }
}

HugeInt::HugeInt(const HugeInt&r)
{
    len = r.len;
    data = new char[len+1];
    strcpy(data,r.data);
}

HugeInt operator+(const HugeInt&r1,const HugeInt&r2)
{
    int minlen=(r1.len<r2.len?r1.len:r2.len);
    int maxlen=(r1.len>r2.len?r1.len:r2.len);
    
    char *nut;
    nut = new char[maxlen+2];
    HugeInt r3(nut);
    
    int i,carry = 0,zan;
    for(i=0;i<minlen;++i)
    {
        zan = r1.data[i]- '0' + r2.data[i] - '0' + carry;
        r3.data[i] = zan%10 + '0';
        carry = zan/10;
    }
    while(i<r1.len)
    {
        zan = r1.data[i] - '0' + carry;
        carry = zan/10;
        r3.data[i] = zan%10 + '0';
        ++i;
    }
    while(i<r2.len)
    {
        zan = r2.data[i] - '0' + carry;
        carry = zan/10;
        r3.data[i] = zan%10 + '0';
        ++i;
    }
    if(carry!=0) {r3.data[i] = carry+'0';r3.data[i+1]='\0';r3.len=maxlen+1;}
    else {r3.data[i] = '\0';r3.len=maxlen;}
    
    return r3;
}

HugeInt operator-(const HugeInt&r1,const HugeInt&r2)
{
    HugeInt r4("0");
    if(r1<=r2) return r4;
    
    int minlen = (r1.len<r2.len?r1.len:r2.len);
    int maxlen = (r1.len>r2.len?r1.len:r2.len);
    
    char*nut;
    nut = new char[maxlen+1];
    int i,carry = 0,zan;
    
    for(i=0;i<minlen;++i)
    {
        zan = int(r1.data[i]) - int(r2.data[i]) + carry;
        if(zan<0) {zan+=10;carry=-1;}
        else carry=0;
        nut[i] = zan + '0';
    }
    while(i<r1.len)
    {
        zan = r1.data[i]-'0'+carry;
        if(zan<0) {zan+=10;carry=-1;}
        else carry=0;
        nut[i] = zan + '0';
        ++i;
    }
    nut[i] = '\0';
    
    char newnut[strlen(nut)+1];
    for(i=0;i<strlen(nut);++i) newnut[i] = nut[strlen(nut)-i-1];
    newnut[strlen(nut)] = '\0';
    HugeInt r3(newnut);
    return r3;
}

HugeInt& HugeInt::operator=(const HugeInt&r)
{
    if(this==&r) return *this;
    delete []data;
    data = new char[strlen(r.data)+1];
    strcpy(data,r.data);
    len = r.len;
    return *this;
}

HugeInt operator*(const HugeInt&r1,const HugeInt&r2)
{
    
    int minlen = (r1.len<r2.len?r1.len:r2.len);
    int maxlen = (r1.len>r2.len?r1.len:r2.len);
    
    int i,j,k,carry = 0,zan;
    
    char**nut;
    nut = new char*[minlen];
    for(i=0;i<minlen;++i) nut[i] = new char[maxlen + minlen +1];
    HugeInt lr(r1);HugeInt sr(r2);
    if(r1.len > r2.len){HugeInt lr(r1);HugeInt sr(r2);}
    else{HugeInt lr(r2);HugeInt sr(r1);}
    
    for(i=0;i<minlen;++i){
        for(k=0;k<i;++k) nut[i][k] = '0';
        for(j=0;j<maxlen;++j)
        {
            zan = (sr.data[i]-'0')*(lr.data[j]-'0') + carry;
            nut[i][j+i] = zan%10+'0';
            carry = zan/10;
        }
        
        if(carry!=0)nut[i][i+j++] = carry+'0';
        nut[i][i+j] = '\0';
        carry = 0;
    }
    
    char*nut1;
    nut1 = new char[maxlen*minlen+1];
    for(i=0;i<(maxlen*minlen);++i)nut1[i] = '0';
    nut1[i] = '\0';
    for(i=0;i<minlen;++i)
    {
        
        int minlen1 = strlen(nut[i]);
        carry = 0;
        for(j=0;j<minlen1;++j)
        {
            zan = nut1[j] - '0' + nut[i][j] - '0' + carry;
            nut1[j] = zan%10 + '0';
            carry = zan/10;
        }
        if(carry!=0) nut1[j] = carry+'0';
    }
    if(carry!=0) nut1[j++] = carry+'0';
    nut1[j] = '\0';
    
    char*nut2;
    nut2 = new char[strlen(nut1)+1];
    for(i=0;i<strlen(nut1);++i) nut2[i] = nut1[strlen(nut1)-i-1];
    nut2[strlen(nut1)] = '\0';
    HugeInt r3(nut2);
    return r3;
}
HugeInt operator*(const HugeInt& r1,const int& n)
{
    if (n<0||n>9) {cout << "getout";HugeInt r2("0");return r2;}
    char nut[r1.len+2];
    int zan,carry=0,i;
    
    for(i=0;i<r1.len;++i) {
        zan = (r1.data[i]-'0') * n + carry;
        carry = zan / 10;
        zan %= 10;
        nut[i] = zan + '0';
    }
    if(carry>0) {nut[i] = carry+'0';++i;}
    nut[i] = '\0';
    char newnut[strlen(nut)+1];
    for(i=0;i<strlen(nut);++i) newnut[i] = nut[strlen(nut)-i-1];
    newnut[strlen(nut)] = '\0';
    HugeInt r2(newnut);
    return r2;
}
//>运算符重载
bool operator>(const HugeInt&r1,const HugeInt&r2)
{
    if(r1.len > r2.len) return true;
    else if(r1.len < r2.len) return false;
    else
    {
        int i;
        for(i=r1.len-1;i>=0;--i)
        {
            if(r1.data[i]>r2.data[i])return true;
            else if(r1.data[i]==r2.data[i]) continue;
            else return false;
        }
        return false;
    }
}

bool operator<(const HugeInt&r1,const HugeInt&r2)
{
    return (r2>r1);
}

bool operator<=(const HugeInt&r1,const HugeInt&r2)
{
    return !(r1>r2);
}

bool operator>=(const HugeInt&r1,const HugeInt&r2)
{
    return !(r1<r2);
}

bool operator==(const HugeInt&r1,const HugeInt&r2)
{
    return (strcmp(r1.data,r2.data)==0);
}

bool operator!=(const HugeInt&r1,const HugeInt&r2)
{
    return !(r1==r2);
}

ostream&operator<<(ostream&os,const HugeInt&obj)
{
    for(int i=obj.len-1;i>=0;--i) os << obj.data[i];
    return os;
}

int main()
{
    char p[1000];
    cin >> p;
    HugeInt n(p);
    HugeInt one("1"),two("2");
    HugeInt multi("1"),carry("2");
    
    int k =0;
    while(multi<n||multi==n)
    {
        multi = multi * 2;
        ++k;
    }
    cout << (multi - one - (multi - one-n)*2);

    return 0;
}



