//  1033
//  Created on 15/10/4.
#include <iostream>
#include <cstring>
#include <cmath>
#include <stdlib.h>
using namespace std;
//--------------------------------------------------------
template<class T>
class seqStack
{
private:
    T*data;
    int top_p;  //栈顶元素下标
    int maxSize;
    
    void doubleSpace();
public:
    seqStack(int initSize = 10)
    {
        data = new T[initSize];
        maxSize = initSize;
        top_p = -1;
    }
    ~seqStack(){delete[]data;}
    bool isEmpty()const { return top_p == -1;}
    void push(const T x)   //入栈
    {
        if(top_p == maxSize-1)doubleSpace();
        data[++top_p] = x;
    }
    T pop(){return data[top_p --];}   //出栈
    T top()const {return data[top_p];}  //返回栈顶元素
};

template<class T>
void seqStack<T>::doubleSpace()
{
    T*tmp = data;
    data = new T[2*maxSize];
    for(int i=0;i<maxSize;++i)data[i] = tmp[i];
    maxSize *= 2;
    delete tmp;
}
//----------------------------------------------------------
class calc{
    char*expression;//要计算的中缀表达式
    char*head;      //表达式的首地址
    //按照优先级排序,增加一个NONE用来初始化
    enum token{NONE,OPAREN,ADD,SUB,MULTI,DIV,EXP,MINUS,CPAREN,VALUE,EOL};
    void binaryOp(token op,seqStack<long long>&dataStack);//操作符计算
    token getOp(long long& value);//获得元素类型
    
public:
    calc(char*s){
        expression = new char[strlen(s)+1];
        strcpy(expression,s);
        head = expression;
    }
    ~calc(){delete expression;}
    long long result();
};

//--------------------------------------------------------------------------
long long calc::result()
{
    token lastOp,topOp; //读入的符号与栈顶的符号
    long long result_value,currentvalue;
    seqStack<token>opStack;    //操作符
    seqStack<long long>dataStack;    //操作数
    
    while(true)
    {
        topOp = NONE;    //栈顶符号,初始化为space,这样如果op栈为空，可以正常判断括号
        lastOp = getOp(currentvalue);//从中缀表达式读入
        if(lastOp == EOL)break;  //如果是行结束符,就结束
        switch(lastOp)
        {
            case VALUE:dataStack.push(currentvalue);break;
                
            case CPAREN:
                while(!opStack.isEmpty()&&(topOp = opStack.pop())!= OPAREN)
                    binaryOp(topOp,dataStack);
                if(topOp!=OPAREN){cerr<<"Error"<<endl;exit(0);}
                break;
            case OPAREN:opStack.push(OPAREN);break;
            case MINUS:opStack.push(MINUS);break; //负号进栈
            case EXP:      //计算前面优先级大于它的符号,这里是负号
                while(!opStack.isEmpty()&&opStack.top()>EXP)
                    binaryOp(opStack.pop(),dataStack);
                opStack.push(EXP);break;
            case MULTI:   //计算前面优先级不小于他们的符号
            case DIV:
                while(!opStack.isEmpty() && opStack.top()>= MULTI)
                    binaryOp(opStack.pop(),dataStack);
                opStack.push(lastOp);
                break;
                
            case ADD:   //计算前面的所有符号直到遇到左括号
            case SUB:
                while(!opStack.isEmpty() && opStack.top()!=OPAREN)
                    binaryOp(opStack.pop(),dataStack);
                opStack.push(lastOp);break;
        }
    }
    while(!opStack.isEmpty())  //符号栈非空，就计算掉
        binaryOp(opStack.pop(),dataStack);
    
    if(dataStack.isEmpty())
    {
        cout<<"Error\n";exit(0);return 0;
    }
    result_value = dataStack.pop();

    if(!dataStack.isEmpty())
    {
        cout<<"Error\n";exit(0);return 0;
    }
    expression = head;   //指针重新指到首地址,完成析构
    return result_value;
}

void calc::binaryOp(token op,seqStack<long long>&dataStack)
{
    long long num1,num2;
    if(dataStack.isEmpty())
    {
        cerr<<"Error";exit(0);
    }
    else num2 = dataStack.pop();
    if(op == MINUS) {dataStack.push(-num2);return;}
    
    if(dataStack.isEmpty())
    {
        cerr<<"Error";exit(0);
    }
    else num1 = dataStack.pop();
    switch(op)
    {
        case ADD:dataStack.push(num1 + num2);break;
        case SUB:dataStack.push(num1 - num2);break;
        case MULTI:dataStack.push(num1*num2);break;
        case DIV:
            if(num2 == 0) {cout<<"Error";exit(0);}
            dataStack.push(num1/num2);
            break;
        case EXP:dataStack.push(pow(num1,num2));break;
    }
}

calc::token calc::getOp(long long &value)
{
    while(*expression!='\0')
    {
        if(*expression<='9' && *expression>='0')
        {
            value = 0;
            while(*expression>='0'&& *expression<='9')
            {
                value = value*10 + *expression - '0';
                ++ expression;
            }
            return VALUE;
        }
        switch(*expression)
        {
            case'(':++expression;return OPAREN;
            case')':++expression;return CPAREN;
            case'+':++expression;return ADD;
            case'*':++expression;return MULTI;
            case'/':++expression;return DIV;
            case'^':++expression;return EXP;
            //如果－号前出现 + - * / ^ ( 则它一定是负号
            case'-':
                if(expression == head){++expression;return MINUS;}
                else if(*(expression-1)=='+'||*(expression-1)=='-'||*(expression-1)=='*'||*(expression-1)=='/'||*(expression-1)=='^'||*(expression-1)=='(') {++expression;return MINUS;}
                else {++expression;return SUB;}      
        }
    }
    return EOL;
}

int main()
{
    char getin[101],newget[101];
    cin.getline(getin,101);
    //去掉所有空格
    int i,j=0;
    for(i=0;i<strlen(getin);++i) if(getin[i]!=' '){newget[j] = getin[i];++j;}
    newget[j] = '\0';
    //除去式子内的空阔号
    char *tmp;
    while((tmp=strstr(newget,"()"))!=NULL)
    {
        char tmmp[strlen(newget)];
        strcpy(tmmp,tmp+2);
        strcpy(tmp,tmmp);
    }
    calc exp(newget);
    cout<< exp.result()<<endl;
    return 0;
}
