#include<iostream>
using namespace std;

template<class T>
void quickSort(int low,int high, T d[])  //用quick sort 代替最小化堆
{
    if (low >= high)return;
    int k = divide(low, high,d);
    quickSort(low, k - 1, d);
    quickSort(k + 1, high, d);
}

template<class T>
int divide(int low, int high,T d[])
{
    T tmp = d[low];
    do
    {
        while (low <high && tmp< d[high]) high--;
        if (low <high) { d[low] = d[high]; low++; }
        while (low <high&& d[low] < tmp) low++;
        if (low <high) { d[high] = d[low]; high--; }
    } while (low < high);
    d[low] = tmp;
    return low;
}


class DisjointSet
{
private:
    int * parent;
    int size;
public:
    DisjointSet(int si)
    {
        size = si;
        parent = new int[size];
        for (int i = 0; i < size; i++)
            parent[i] = -1;
    }
    ~DisjointSet(){ delete[] parent; }
    int Find(int x)
    {
        if (parent[x] < 0)return x;
        return parent[x] = Find(parent[x]);
    }
    void Union(int root1, int root2)
    {
        if (root1 == root2)return;
        if (parent[root1] > parent[root2])
        {
            parent[root2] += parent[root1]; parent[root1] = root2;
        }
        else
        {
            parent[root1] += parent[root2];
            parent[root2] = root1;
        }
    }
    
};

struct node
{
    int beg;
    int end;
    int weight;
    node(int b=0, int e=0, int w=0){ beg = b; end = e; weight = w; }
    bool operator<(node a)
    {
        return weight < a.weight;
    }
};



int main()
{
    int m, n;
    cin >> n >> m;
    node* p = new node[m + 1];
    DisjointSet ds(n + 1);
    for (int i = 0; i < m; i++)
    {
        cin >> p[i + 1].beg >> p[i + 1].end >> p[i + 1].weight;
    }
    quickSort<node>(1, m, p);
    int acceptEdge = 0;
    int position = 1;
    node e;
    int u, v,totalWeight=0;
    while (acceptEdge < n - 1)
    {
        e = p[position];
        position++;
        u = ds.Find(e.beg);
        v = ds.Find(e.end); 
        if (u != v)
        {
            acceptEdge++;
            ds.Union(u, v);
            totalWeight += e.weight;
        }
    }
    
    cout << totalWeight << endl;
    return 0;
}