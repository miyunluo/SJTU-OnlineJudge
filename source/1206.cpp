//  1206
//  Created on 15/9/30.
#include <iostream>
#include <cstring>
using namespace std;

char x[6] = {'\0'};    //存储出栈的字符串

struct node
{
    char data[6]={'\0'};
    node *next;
};

class linkstack
{
public:
    node*elem;
    
    linkstack(){ elem = NULL;}
    ~linkstack();
    
    bool isEmpty() const{return elem == NULL;}
    void push(const char* a)  //进栈
    {
        node*tmp = new node;
        strcpy(tmp->data,a);
        tmp->next = elem;
        elem = tmp;
    }
    void pop()              //出栈 并 删除
    {
        node*tmp = elem;
        
        for(int i=0;i<6;++i) x[i] = '\0';
        
        strcpy(x,tmp->data);
        elem = elem->next;
        delete tmp;
    }
    char* top()           //返回栈顶元素
    {
        return elem->data;
    }
    
};

linkstack::~linkstack()
{
    node*tmp;
    while(elem != NULL)
    {
        tmp = elem;
        elem = elem->next;
        delete tmp;
    }
}

int main()
{
    linkstack st;
    char in[100];
    while(cin >> in)
    {
        if(strcmp(in,"begin")==0)
        {
            if(!st.isEmpty() && strcmp(st.top(),"if")==0){cout<<"Error!";return 0;}
            else st.push(in);
        }
        //如果begin前为if则出错，否侧入栈
        
        if(strcmp(in,"if")==0) st.push(in);
        //如果是if直接入栈
        
        if(strcmp(in,"then")==0)
        {
            if(st.isEmpty()){cout<<"Error!";return 0;}
            if(strcmp(st.top(),"if")!=0){cout<<"Error!";return 0;}
            else st.push(in);
        }
        //如果是then，如果前面不为if则出错，否则入栈
        
        if(strcmp(in,"else")==0)
        {
            if(st.isEmpty()){cout<<"Error!";return 0;}
            st.pop();
            if(strcmp(x,"then")!=0){cout<<"Error!";return 0;}
            if(st.isEmpty()){cout<<"Error!";return 0;}
            st.pop();
            if(strcmp(x,"if")!=0){cout<<"Error!";return 0;}
        }
        //如果是else，判断前面两个是否为 then，if，否则出错
        
        if(strcmp(in,"end")==0)
        {
            if(st.isEmpty()) {cout<< "Error!"<<endl;return 0;}
            else
            {
                st.pop();
                if(strcmp(x,"if")==0) {cout<< "Error!"<<endl;return 0;}
                
                while(strcmp(x,"then")==0)
                {
                    if(st.isEmpty()) {cout<< "Error!"<<endl;return 0;}
                    
                    st.pop();
                    if(!(strcmp(x,"if")==0)){cout<< "Error!"<<endl;return 0;}
                    st.pop();
                }
                
                if(strcmp(x,"begin")!=0) {cout<< "Error!"<<endl;return 0;}
            }
        }
        //如果是end，那么除去它与begin之间的 if then，再判断
    }
    
    while(!st.isEmpty())
    {
        st.pop();
        if((strcmp(x,"then")!=0)){cout<< "Error!"<<endl;return 0;}
        if(st.isEmpty()) {cout<< "Error!"<<endl;return 0;}
        st.pop();
        if((strcmp(x,"if")!=0)){cout<< "Error!"<<endl;return 0;}
    }
    //最终可能会遇到剩下 if then的情况，此时将if、then对一直出栈
    
    if(st.isEmpty())cout <<"Match!";
    //最终栈为空的话，就对了
    return 0;
}



