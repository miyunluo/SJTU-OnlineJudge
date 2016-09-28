#include <iostream>
#include <cstdio>
using namespace std;

template<class T>
class BinarySearchTree
{
private:
    struct binaryNode{
        T data;
        binaryNode *left,*right;
        binaryNode(const T&d,binaryNode *lf = NULL,binaryNode *rt = NULL)
        {data = d,left = lf,right = rt;}
    };
    
    binaryNode *root;
    
public:
    BinarySearchTree(binaryNode *t = NULL){root = t;}
    ~BinarySearchTree(){deleteTree(root);}
    
    bool find(const T&x)  {return find(x,root);}
    void insert(const T&x)  {insert(x,root);}
    void remove(const T&x)  {remove(x,root);}
    void delete_less_than(const T&x)  {delete_less_than(x,root);}
    void delete_greater_than(const T&x)  {delete_greater_than(x,root);}
    void delete_interval(const T&a,const T&b)  {delete_interval(a,b,root);}
    bool find_ith(const T&i)  {return find_ith(i,root);}
    
    int pointsize(binaryNode*t);   //结点规模
    
private:
    void deleteTree(binaryNode *&t); //析构函数调用
    
    bool find(const T&x,binaryNode *t);
    void insert(const T&x,binaryNode *&t);
    void remove(const T&x,binaryNode *&t);
    void delete_less_than(const T&x,binaryNode *&t);
    void delete_greater_than(const T&x,binaryNode *&t);
    void delete_interval(const T&a,const T&b,binaryNode *&t);
    bool find_ith(const T&i,binaryNode *&t);
};

template<class T>
int BinarySearchTree<T>::pointsize(binaryNode*t)
{
    if(t == NULL) return 0;
    else return (pointsize(t->left) + pointsize(t->right) + 1);
}


template<class T>
void BinarySearchTree<T>::deleteTree(binaryNode *&t)
{
    if(t == NULL) return;
    if(t->left != NULL) deleteTree(t->left);
    if(t->right != NULL) deleteTree(t->right);
    delete t;
}

template<class T>
bool BinarySearchTree<T>::find(const T&x,binaryNode *t)
{
    if(t == NULL) return false;
    else if(x < t->data) {return find(x,t->left);}
    else if(x > t->data) {return find(x,t->right);}
    else return true;
}

template<class T>
void BinarySearchTree<T>::insert(const T&x,binaryNode *&t)
{
    if(t == NULL) {t = new binaryNode(x);}
    else if(x <= t->data) insert(x,t->left);
    else insert(x,t->right);
}

template<class T>
void BinarySearchTree<T>::remove(const T&x,binaryNode *&t)
{
    if(t == NULL) return;
    
    if(x < t->data) remove(x,t->left);
    else if(x > t->data) remove(x,t->right);
    
    else if(t->left != NULL && t->right != NULL)
    {
        binaryNode *tmp = t->right;
        while(tmp ->left != NULL) tmp = tmp->left;
        t->data = tmp->data;
        remove(t->data,t->right);
    }
    else{
        binaryNode *old = t;
        t = (t->left != NULL)? t->left:t->right;
        delete old;
    }
}

template<class T>
void BinarySearchTree<T>::delete_less_than(const T&x,binaryNode *&t)
{
    if(t == NULL) return;
    
    if(x < t->data) delete_less_than(x,t->left);
    else if(x == t->data) {deleteTree(t->left);t->left = NULL;return;}
    else{
        binaryNode *tmp = t;
        t = t->right;
        delete tmp;
        
        delete_less_than(x,t);
    }
}

template<class T>
void BinarySearchTree<T>::delete_greater_than(const T&x,binaryNode *&t)
{
    if(t == NULL) return;
    
    if(x > t->data) delete_greater_than(x,t->right);
    else if(x == t->data) {deleteTree(t->right);t->right = NULL;return;}
    else{
        binaryNode *tmp = t;
        t = t->left;
        delete tmp;
        
        delete_greater_than(x,t);
    }
}

template<class T>
void BinarySearchTree<T>::delete_interval(const T&a,const T&b,binaryNode *&t)
{
    
    if(t == NULL) return;
    if(a >= t->data) delete_interval(a,b,t->right);
    else if(b <= t->data) delete_interval(a,b,t->left);
    else {
        delete_greater_than(a,t->left);
        delete_less_than(b,t->right);
        remove(t->data,t);
    }
    
}

template<class T>
bool BinarySearchTree<T>::find_ith(const T&i,binaryNode *&t)
{
    if(t == NULL) return false;
    int lfsize = pointsize(t->left);
    
    if(i <= lfsize) return find_ith(i,t->left);
    else if(i == lfsize+1) {cout <<t->data<<'\n';return true;}
    else return find_ith(i - lfsize -1,t->right);
}



int main()
{
    BinarySearchTree<int> tree;
    int n,a,b;
    scanf("%d",&n);
    char command[30];
    for(int i=0;i<n;++i)
    {
        cin >> command;
        switch(command[0])
        {
            case 'i':
                scanf("%d",&a);
                tree.insert(a);
                break;
            case 'd':
                if(command[6] == '\0'){scanf("%d",&a);tree.remove(a);}
                else
                    switch(command[7])
                {
                    case 'l':
                    {scanf("%d",&a);tree.delete_less_than(a);break;}
                    case 'g':
                    {scanf("%d",&a);tree.delete_greater_than(a);break;}
                    case 'i':
                    {scanf("%d%d",&a,&b);tree.delete_interval(a, b);break;}
                }
                break;
            case 'f':
                if(command[4]!='\0')
                {
                    scanf("%d",&a);
                    bool flag = tree.find_ith(a);
                    if(!flag) cout <<'N'<<endl;
                }
                else{
                    scanf("%d",&a);
                    bool flag = tree.find(a);
                    if(flag)cout<<'Y'<<endl;
                    else cout<<'N'<<endl;
                }
        }
    }
    return 0;
}


/*
 40
 insert 97591
 find_ith 1
 find 75173
 delete_less_than 97592
 insert 83466
 delete 83466
 insert 1221
 delete_less_than 1222
 insert 57371
 find 34749
 delete_less_than 57372
 insert 92200
 find 92200
 insert 85718
 delete_greater_than 85717
 insert 1028
 insert 27902
 find_ith 1
 insert 60499
 find 1028
 insert 52563
 delete_less_than 1029
 insert 49506
 insert 21377
 find 21377
 insert 65325
 delete 52563
 find 27902
 find 27902
 delete_interval 27901 49507
 insert 78360
 insert 84526
 delete_interval 60498 65326
 insert 90725
 delete_greater_than 78359
 delete 21377
 insert 68828
 find_ith 2
 find 56925
 delete_less_than 68829
 */





