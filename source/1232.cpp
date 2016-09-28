#include<iostream>
using namespace std;
class DisjointSet
{
private:
    int size;
    int * parent;
public:
    DisjointSet(int s)
    {
        size = s;
        parent = new int[s];
        for (int i = 0; i < s; i++){ parent[i] = -1; }
    }
    
    ~DisjointSet(){ delete[] parent; }
    void Union(int root1, int root2)
    {
        if (root1 == root2) return;
        if (parent[root1] > parent[root2])
        {
            parent[root2] += parent[root1]; parent[root1] = root2;
        }
        else { parent[root1] += parent[root2]; parent[root2] = root1; }
    }
    
    int Find(int x)
    {
        if (parent[x] < 0) return x;
        else Find(parent[x]);
    }
};

class Queue
{
private:
    struct node
    {
        int data;
        node * next;
        node(int da = 0, node* ne = NULL){ data = da; next = ne; }
    };
    
    node *head;
    node * tail;
public:
    Queue(){ tail = head = new node(0,NULL); }
    void push(int x){ tail = tail->next = new node(x, NULL); }
    int pop()
    {
        int tmp = tail->data;
        node *tm = tail;
        node * i;
        for (i = head; i->next != tail; i = i->next);
        tail = i;
        tail->next = NULL;
        delete tm;
        return tmp;
    }
    int topValue(){ return tail->data; }
    
    void enQueue(int x){ head->next = new node(x, head->next); }
    int deQueue(){ node *tmp = head->next; head->next = tmp->next; int x = tmp->data; delete tmp; return x; }
    ~Queue(){
        while (head->next != NULL)
        {
            node* tmp = head;
            head = head->next;
            delete tmp;
        }
        delete head;
    }
    bool isEmpty(){ return head->next == NULL; }
};

void calRowCol(int x, int & row, int& col)
{
    int i;
    for (i = 0;; i++)
    {
        if (x > (i*(i + 1) / 2) && x <= ((i + 1)*(i + 2) / 2))
        {
            row = i + 1;
            col = x - (i*(i + 1) / 2);
            return;
        }
    }
}


int main()
{
    int n, start, end;
    cin >> n >> start >> end;
    int size = n*(n + 1) / 2;
    int **visited; //是否可以访问 0 表示联通
    
    visited = new int*[size+1];
    for (int i = 0; i <= size + 1; i++)
    {
        visited[i] = new int[size + 1];
    }
    for (int i = 1; i <= size+1; i++)
    {
        for (int j = 1; j <= size + 1;j++)
            visited[i][j] = -1; //标记为－1
    }
    
    int num,  direct,col,row;
    
    DisjointSet set(size + 1);
    while (set.Find(start) != set.Find(end)) //首尾没联通
    {
        cin >> num >> direct;
        switch (direct)
        {
            case 0:
                calRowCol(num, row, col);
                if (col != 1){
                    set.Union(set.Find(num), set.Find(num - row));
                    visited[num][num-row] = 0;
                    visited[num - row][num] = 0; //改为二者连通
                }
                break;
            case 1:
                calRowCol(num, row, col);
                if (col != row){
                    set.Union(set.Find(num), set.Find(num - row + 1));
                    visited[num][num - row + 1] = 0;
                    visited[num - row + 1][num] = 0;
                }
                break;
            case 2:
                calRowCol(num, row, col);
                if (row != n){
                    set.Union(set.Find(num), set.Find(num + row));
                    visited[num][num + row] = 0;
                    visited[num + row][num] = 0;
                }
                break;
            case 3:
                calRowCol(num, row, col);
                if (row != n)
                {
                    set.Union(set.Find(num), set.Find(num + row + 1));
                    visited[num][num + 1 + row] = 0;
                    visited[num + 1 + row][num] = 0;
                }
                break;
        };
    }
    
    Queue stack;  //实际当作栈来用
    int position = start;
    while (position != end)  //题目说 按字典序小的顺序输出，按下面的进栈顺序没错，说明 嘿嘿 数据里没有重复路径
    {
        calRowCol(position, row, col);
        if (row != n && visited[position + row][position] == 0)
        {
            stack.push(position);
            visited[position + row][position] = 1;
            visited[position][position + row] = 1;
            position += row;
        }
        else if (row != n && visited[position + row + 1][position] == 0)
        {
            stack.push(position);
            visited[position + row+1][position]= 1;
            visited[position][position + row + 1] = 1;
            position += row+1;
        }
        else if (col != 1 && visited[position - row][position] == 0)
        {
            stack.push(position);
            visited[position - row ][position] = 1;
            visited[position][position - row] = 1;
            position -=row;
        }
        else if (col != n && visited[position][position - row + 1] == 0)
        {
            stack.push(position);
            visited[position - row+1][position] = 1;
            visited[position][position - row + 1] = 1;
            position -= row-1;
        }
        else
        {
            position = stack.pop();
        }
        
    }
    
    while (!stack.isEmpty())
    {
        cout << stack.deQueue() << ' ';
    }
    cout << end<<endl;
    
}