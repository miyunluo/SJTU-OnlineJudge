//  main.cpp
//  Created on 15/10/17.
#include <iostream>
#include <cmath>
using namespace std;

struct node{
    int frst;
    int scnd;
    float value;
    node*prev;
    node*next;
    
    node(int f,int s):frst(f),scnd(s),prev(NULL),next(NULL)
    {value = (frst*1.0)/(scnd*1.0);}
    node():frst(0),scnd(0),value(0.0),prev(NULL),next(NULL){}
    ~node(){}
};

void yuefen(int&fz,int&fm)
{
    int a = (fz>fm? fz:fm); //两者的较大值
    int b = (fz<fm? fz:fm); //两者的较小值
    int tmp;
    while(b!=0)             //辗转相除得到最大公约数
    {
        tmp = a % b;
        a = b;
        b = tmp;
    }
    fz /=a;                //化简
    fm /=a;
}

int main()
{
    int n;
    cin >> n;
    int a = 0,b = 1;
    node*tail = new node(a,b);
    node*tmp = new node(a,b);
    node*head = tmp;
    tmp->next = tail;
    tail->prev = tmp;

    int i,j;
    for(i=n;i>=1;--i){               //将每个数化简后插入合适的位置，不包括0和1
        for(j=1;j<i;++j)
        {
            int fenzi = j,fenmu = i;
            yuefen(fenzi,fenmu);
            node *tmp1 = new node(fenzi,fenmu);
            
            node *tmp2 = head;
            bool flag = false;
            while(tmp2 != tail)
            {
                if(fabs(tmp1->value - tmp2->value)<0.000000000000001)
                {
                    flag = true;
                    break;
                }
                if(tmp1->value > tmp2->value) tmp2 = tmp2->next;
                else break;
            }
            
            if(flag) continue;
            
            node*tmp3 = tmp2->prev;
            tmp3->next = tmp1;
            tmp1->next = tmp2;
            tmp2->prev = tmp1;
            tmp1->prev = tmp3;        
        }
    }
    
    node*tmp4 = head;
    while(tmp4!=tail) //按顺序输出
    {
        cout << tmp4->frst << '/' << tmp4->scnd <<endl;
        tmp4 = tmp4->next;
    }
    
    cout <<'1'<<'/'<<'1';  //最后加上1
    return 0;
}



