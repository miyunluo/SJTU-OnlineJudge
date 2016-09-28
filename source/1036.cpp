#include <iostream>
#include <cstdio>
using namespace std;

long long int n;                      //总人数
long long int servetime[100009] = {0};//每个人的servetime

inline long long int max(long long int a,long long int b){
    return a>b?a:b;
}

/*************************oldqueue***************************/
long long int queue[3][100009];       //三个柜台的队伍
int rear1 = 0,rear2 = 0,rear3 = 0;    //队伍尾下标
long long int allWait1 = 0,theLast1 = 0; //要输出的值
/**************************************************************/

/*************************newqueue****************************/
long long int waitTime[100009];       //每个人的等待时间的数组
long long int allWait2 = 0,theLast2 = 0;
/***************************************************************/
void init()
{
    scanf("%lld",&n);
    for(int i = 0;i < n; ++i)scanf("%lld",&servetime[i]);
}

void oldqueue()
{
    if(n <= 3)
    {
        theLast1 = max(servetime[0],servetime[1]);
        theLast1 = max(theLast1,servetime[2]);
        cout<< 0 <<' '<< theLast1 <<endl;
        return;
    }
    
    long long int i;
    for(i=0;i<n;i += 3)   //讲每个人分配到柜台
    {
        rear1 ++;
        queue[0][rear1] = servetime[i];
        
        if(servetime[i + 1] != 0){
            rear2 ++;
            queue[1][rear2] = servetime[i+1];}
        if(servetime[i + 2] != 0){
            rear3 ++;
            queue[2][rear3] = servetime[i+2];}
    }
    
    long long int tmp1 = 0,tmp2 = 0,tmp3 = 0; //分别存储三个队列的总时间
    long long int tmpwait1 = 0,tmpwait2 = 0,tmpwait3 = 0;//分别存储三个队列等待时间的和 三个变量为了检验对错
    queue[0][0] = queue[1][0] = queue[2][0] = 0; //头设为0为了方便 等待时间总和的计算，第一个人的等待时间为0
    for(i = 0;i<=rear1;++i) {tmp1 +=queue[0][i];tmpwait1 += tmp1;}
    tmpwait1 -= tmp1;
    //cout <<"tmpwait1: "<<tmpwait1<<endl;
    for(i = 0;i<=rear2;++i) {tmp2 +=queue[1][i];tmpwait2 += tmp2;}
    tmpwait2 -= tmp2;
    //cout <<"tmpwait2: "<<tmpwait2<<endl;
    for(i = 0;i<=rear3;++i) {tmp3 +=queue[2][i];tmpwait3 += tmp3;}
    tmpwait3 -= tmp3;
    //cout <<"tmpwait3: "<<tmpwait3<<endl;
    
    allWait1 = tmpwait1 + tmpwait2 + tmpwait3;
    theLast1 = max(tmp1,tmp2);
    theLast1 = max(theLast1,tmp3);
    
    cout << allWait1 <<' '<< theLast1 << endl; 
}

void newqueue()
{
    if(n <= 3)
    {
        theLast2 = max(servetime[0],servetime[1]);
        theLast2 = max(theLast2,servetime[2]);
        cout<< 0 <<' '<< theLast2 <<endl;
        return;
    }
    
    long long int currtime = 0; //系统当前时间，既三个柜台的最小时间
    long long int serve[3] = {0};//三个柜台累计服务时间，既下一个人的等待时间
    long long int index = 0;
    for(;;)   //系统时间和三个柜台的最小时间相等就可以换人了
    {
        if(serve[0] == currtime)
        {
            waitTime[index] = serve[0];
            serve[0] += servetime[index];
            ++index;
            if(index == n)break;
        }
        if(serve[1] == currtime)
        {
            waitTime[index] = serve[1];
            serve[1] += servetime[index];
            ++index;
            if(index == n)break;
        }
        if(serve[2] == currtime)
        {
            waitTime[index] = serve[2];
            serve[2] += servetime[index];
            ++index;
            if(index == n)break;
        }
        
        currtime = min(serve[0],serve[1]);
        currtime = min(currtime,serve[2]);//更新系统时间
        
    }
    theLast2 = max(serve[0],serve[1]);
    theLast2 = max(theLast2,serve[2]);
    for(int i=0;i< n;++i)allWait2 += waitTime[i];
    cout << allWait2 <<' '<<theLast2<<endl;
}

int main()
{
    init();
    oldqueue();
    newqueue();
    return 0;
}
/*
15
 3 5 6 2 3 4 5 1 8 6 9 8 7 5 18
 */
