//
//  main.cpp
//  1520
//  Created on 15/11/11.
#include <iostream>
using namespace std;

char temp[100001];
char opstack[100001];
long long int datastack[100001];
long long int result[100001];
int tempindex = 0,opindex = 0,dataindex = 0,resindex = 0;

int main()
{
    char origin[100001],newline[100001];
    cin.getline(origin,100000);
    int i = 0,j = 0;
    while(true)
    {
        
        if(origin[i] == '\0') break;
        else if(origin[i] == ' ') ++i;
        else newline[j++] = origin[i++];
    }
    newline[j] = '\0';
    
    int length = j;
    long long int tmp;
    i = 0;
    while(i < length)
    {
        if(newline[i] == '('){temp[tempindex++] = '(';++i;}
        
        else if(newline[i] == '*' || newline[i] == '/')
        {
            while(tempindex !=0 && temp[tempindex - 1] != '+' && temp[tempindex - 1] != '-' && temp[tempindex -1]!= '(')
            {opstack[opindex++] = temp[tempindex - 1]; --tempindex;}
            temp[tempindex++] = newline[i];   //本身进栈
            ++i;
        }
        else if(newline[i] == '+' || newline[i] == '-')
        {
            while(tempindex !=0 && temp[tempindex -1] != '(')
            {opstack[opindex++] = temp[tempindex - 1]; --tempindex;}
            temp[tempindex++] = newline[i];
            ++i;
        }
        else if(newline[i] == ')')
        {
            while(temp[tempindex -1] != '(') //将括号内的运算符都出栈
            {opstack[opindex++] = temp[tempindex - 1]; --tempindex;}
            --tempindex;    //吃掉开括号
            ++i;
        }
        else
        {
            opstack[opindex++] = 'n'; //用 n 代表数字
            tmp = 0;
            while(newline[i] >= '0' && newline[i] <= '9')
            {tmp = tmp*10 + (newline[i]-'0');++i;}
            
            datastack[dataindex++] = tmp;   //将数字放在另一个数组里
        }
        
    }
    while(tempindex != 0)
    {
        opstack[opindex++] = temp[tempindex - 1];
        --tempindex;
    }
    opstack[opindex] = '\0';
    
    //后缀表达式的计算
    
    dataindex = 0;
    long long int num1,num2,num3;
    for(i=0;i<opindex;++i)
    {
        switch(opstack[i]){
            case 'n': result[resindex++] = datastack[dataindex++];break;
            case '+':
            {
                num2 = result[resindex - 1];
                num1 = result[resindex - 2];
                num3 = num1 + num2;
                result[resindex - 2] = num3;
                resindex -= 1;
                
                break;
            }
            case '-':
            {
                num2 = result[resindex - 1];
                num1 = result[resindex - 2];
                num3 = num1 - num2;
                result[resindex - 2] = num3;
                resindex -= 1;
                
                break;
            }
            case '*':
            {
                num2 = result[resindex - 1];
                num1 = result[resindex - 2];
                num3 = num1 * num2;
                result[resindex - 2] = num3;
                resindex -= 1;
                
                break;
            }
            case '/':
            {
                num2 = result[resindex - 1];
                num1 = result[resindex - 2];
                num3 = num1 / num2;
                result[resindex - 2] = num3;
                resindex -= 1;
                
                break;
            }
        }
    }
    
    cout << result[0]<<endl;
    
    return 0;
}
