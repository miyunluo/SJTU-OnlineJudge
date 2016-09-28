//
//  main.cpp
//  1518
//
//  Created on 15/11/5.
#include <iostream>
using namespace std;

struct node
{
    int data;
    node *left,*right;
    node(){left = NULL;right = NULL;}
    node(int d){data = d;left = NULL;right = NULL;}
};


node* build(int *preorder,int *inorder,int lenght)
{
    if(lenght == 0) return NULL;
    node *rt = new node(*preorder); //前序遍历第一个元素是 root
    int rtindex;                //中序遍历 root 的下标
    for(rtindex = 0;rtindex<lenght;++rtindex)
    {if(inorder[rtindex] == rt->data) break;}
    
    rt->left = build(preorder+1, inorder, rtindex); //中序遍历 root前的是左子树  后是右子数
    rt->right = build(preorder + rtindex + 1, inorder + rtindex + 1, lenght - 1 - rtindex);
    cout << rt->data<<' ';
    return rt;
}

void postOrder(node*t)   // 后序遍历
{                        //可以在build函数里完成
    if(t!=NULL)
    {
        postOrder(t->left);
        postOrder(t->right);
        cout << t->data<<' ';
    }
}

int main()
{
    int n,*preorder,*inorder;
    cin >> n;
    preorder = new int[n];
    inorder = new int[n];
    
    int i;
    for(i=0;i<n;++i) cin >> preorder[i];
    for(i=0;i<n;++i) cin >> inorder[i];
    
    //node *root = build(preorder,inorder,n);
    //postOrder(root);
    
    build(preorder,inorder,n);
    
    return 0;
}

/* 
 3
 -23432134 90687980 1
 90687980 -23432134 1
*/
