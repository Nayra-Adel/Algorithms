// UVA:     924
// Name:    Nayra Adel Hamed

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
	int  n, sz;
	Value* arr;


    void Initialize()
    {
        n = 0;
        sz = 1;
        arr = new Value [sz];
    }

    void Destroy()
    {
        delete []arr;
    }

    void AddLast(Value v)
    {
        if(n == sz)
        {
            sz*=2;
            Value *new_arr = new Value[sz];
            for(int i=0; i < n; i++)
            {
                new_arr[i] = arr[i];
            }
            new_arr[n++] = v;
            Destroy();
            arr = new_arr;
        }
        else
        {
            arr[n++] = v;
        }
    }

    void RemoveLast()
    {
        n--;

        if( n < sz/2 && n!=0)
        {
            sz/=2;
            Value *new_arr = new Value[sz];
            for(int i=0; i < n; i++)
            {
                new_arr[i] = arr[i];
            }
            Destroy();
            arr = new_arr;
        }
    }

    Value& operator[](int i)
    {
        return arr[i];
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node
{
	Array<int> adj;

	void Initialize()
	{
	    adj.Initialize();
	}

	void Destroy()
	{
	    adj.Destroy();
	}
};

struct Graph
{
	int n;
	Node* nodes;

	void Initialize(int _n)
	{
	    n = _n;
	    nodes = new Node[n];
	    for(int i=0;i<n;i++) nodes[i].Initialize();
	}

	void Destroy()
	{
	    for(int i=0;i<n;i++) nodes[i].Destroy();
	    delete[] nodes;
	}

	void add(int src, int dst)
	{
	    nodes[src].adj.AddLast(dst);
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Type>
struct Queue
{
	int f, n;
	Type* elems;

	void Initialize(int size)
	{
	    n = 0;
	    f = 0;
	    elems = new Type[size];
	}

	void Destroy()
	{
	    delete []elems;
	}

	void Add(Type t)
	{
	    elems[n++] = t;
	}

	Type Pop()
	{
	    Type t = elems[f];
	    f++;
	    return t;
	}

	Type Peek()
	{
	    return elems[f];
	}

	int Num()
	{
	    return n-f;
	}
};

int *BFS(Graph& g, int s)
{
    Queue<int> q;
    q.Initialize(g.n);
    int* vis=new int[g.n];
    int* dst=new int[g.n];
    int* pre=new int[g.n];

    for(int i=0; i<g.n; i++)
    {
      dst[i] = g.n;
      vis[i] = 0;
      pre[i] = -1;
    }

    vis[s]=1;
    dst[s]=0;
    q.Add(s);
    while(q.Num())
    {
        int cur=q.Pop();
        for(int i=0; i<g.nodes[cur].adj.n; i++)
        {
            int x=g.nodes[cur].adj[i];
            if(!vis[x])
            {
                vis[x]=1;
                pre[x]=cur;
                dst[x]=dst[cur]+1;
                q.Add(x);
            }
        }
    }
    return dst;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Graph g;
    int Employees, numOfFriends, employee, testCases, source, counter, maxDailyBoomSize, firstBoomDay;
    int *arr;

    cin >> Employees;
    g.Initialize(Employees);

    for(int i=0; i<Employees; i++)
    {
        cin >> numOfFriends;
        for(int j=0; j < numOfFriends; j++)
        {
            cin >> employee;
            g.add(i, employee);
        }
    }

    cin >> testCases;
    for(int i=0; i<testCases; i++)
    {
        cin >> source;
        arr = BFS(g, source);
        maxDailyBoomSize = 0;
        for(int v=0; v<Employees; v++)
        {
            counter = 0;
            for(int c=0; c<Employees; c++)
            {
                if(arr[c] == v && c != source) counter++;
            }
            if(counter > maxDailyBoomSize)
            {
                maxDailyBoomSize = counter;
                firstBoomDay = v;
            }
        }
        if(maxDailyBoomSize == 0)
        {
            cout << maxDailyBoomSize << endl;
        }
        else
        {
            cout << maxDailyBoomSize << " " << firstBoomDay << endl;
        }
    }
    g.Destroy();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
