//
//  main.cpp
//  1204
//  Created on 15/9/27.
#include <iostream>
#include <cstring>
using namespace std;

struct node{
    char data[2001];
    node*next;
};
class edit
{
public:
    node*head;
    int len;
    edit(){head=new node;head->next=NULL;len=0;}
    ~edit(){clear();delete head;}
    void clear(){
        node*p = head->next,*tmp;
        while(p!=NULL)
        {
            tmp = p;
            p = p->next;
            delete tmp;
        }
    }
    
    void list(int left,int right);
    void ins(int i,int j,char*a);
    void del(int i,int j,int num);
    void quit();
};

//edit::edit()
//{
//    node*head = new node;
//    node*tmp = head,*p;
//    len = 0;
//    char x[2000];
//    while(true)
//    {
//        cin.getline(x,2000);
//        if(strcmp(x,"******")!=0){
//            p = new node;
//            strcpy(p->data,x);
//            tmp->next = p;
//            tmp = p;
//            ++ len;
//        }
//        else{tmp->next = NULL;break;}
//    }
//}
istream& operator>>(istream& is,edit& t)//直接从input内容输入构造,在离开构造函数后出了问题
{                                     //这里请教了5140309022，直接用了他的重载函数
    node *p=t.head->next,*tmp;
    while (p!=NULL) {
        tmp = p;
        p = p->next;
        delete tmp;
    }
    t.len = 0;
    p = t.head;
    char data[2001];
    char a[]={"******"};
    while (is.getline(data,2001)) {
        if (strlen(data)==6&&strncmp(data,a,6)==0) break;
        tmp = new node;
        strcpy(tmp->data,data);
        p->next = tmp;
        p = tmp;
        ++t.len;
    }
    p->next = NULL;
    return is;
}

void edit::list(int left,int right)
{
    if(left > right || right > len || left < 1){cout<< "Error!"<<endl;return;}
    node*p = head->next;
    int i=1;
    while(p!=NULL){
        if(i>=left && i<=right)cout << p->data <<endl;
        if(i>right) break;
        p = p->next;
        ++ i;
    }
}


void edit::ins(int i,int j,char *a)
{
    if (i<1 || i>len || j<1) {cout << "Error!" << endl;return;}
    int k;
    node *p = head;
    for (k=0;k<i;++k) p = p->next;
    
    if (j>strlen(p->data)+1) {cout << "Error!" << endl;return;}
    
    char tmp[2000]={'\0'};
    strcpy(tmp,p->data+j-1);
    p->data[j-1] = '\0';
    strcat(p->data,a);
    strcat(p->data,tmp);
}

void edit::del (int i,int j,int num)
{
    if (i<1 || i>len || j<1) {cout << "Error!" << endl;return;}
    
    int k;
    node *p=head;
    for (k=0;k<i;++k) p = p->next;
    
    if (j+num-1>strlen(p->data)) {cout << "Error!" << endl;return;}
    
    char tmp[2000]={'\0'};
    strcpy(tmp,p->data+j+num-1);
    p->data[j-1] = '\0';
    strcat(p->data,tmp);
}
void edit::quit()
{
    list(1,len);
}

int main()
{
    edit text;
    cin>> text;
    char command[5];
    while(true)
    {
        cin>> command;
        if(command[0]=='l')
        {
            int left,right;
            cin>> left >> right;
            text.list(left,right);
        }
        if(command[0]=='i')
        {
            int i,j;
            char str[101];
            cin >> i >> j;
            cin.get();
            cin.getline(str,101);
            text.ins(i,j,str);
        }
        if(command[0]=='d')
        {
            int i,j,num;
            cin>> i >> j >>num;
            text.del(i,j,num);
        }
        if(command[0]=='q')
        {
            text.quit();
            break;
        }
    }
    
    return 0;
}





