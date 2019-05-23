// UVA:     11631
// Name:    Nayra Adel Hamed

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DisjointSets
{
    int n;
	int* parent;
	int* num_nodes;

	void Initialize(int _n)
	{
	    n = _n;
	    parent  = new int [n];
	    num_nodes = new int [n];
	    for(int i=0; i< n; i++){
            parent[i] = -1;
            num_nodes[i] = 1;
	    }
	}

	void Destroy()
	{
	    delete[]parent;
	    delete []num_nodes;
	}

	int Find(int i)
	{
	    int k = i;
	    while(true){
            if(parent[k] != -1)
                k = parent[k];
            else
                return k;
	    }
	}

	bool Union(int i, int j)
	{
	    int find_i = Find(i);
	    int find_j = Find(j);
	    if(find_i == find_j) return false;
	    else
        {
            if(num_nodes[find_i] >= num_nodes[find_j])
            {
                num_nodes[find_i]+= num_nodes[find_j];
                num_nodes[find_j] = 0;

                parent[find_j] = find_i;
            }
            else
            {
                num_nodes[find_j]+= num_nodes[find_i];
                num_nodes[find_i] = 0;
                parent[find_i] = find_j;
            }
            return true;
	    }
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = n/2;

    if(n<=1) return;

    int i=0, k, j=mid;

    Type *t = new Type [n];

    for(k=0; k<n; k++)
    {
        if(j==n || (i < mid && IsBefore(a[i], a[j])))
        {
            t[k] = a[i++];
        }
        else
        {
            t[k] = a[j++];
        }
    }
    for(i=0; i<n; i++)
    {
        a[i] = t[i];
    }

}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = n/2;
    if(n <= 1) return;

    MergeSort(a, mid, IsBefore);
    MergeSort(a+mid, n-mid, IsBefore);
    Merge(a, n, IsBefore);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
    int u, v;
    int w;
};

bool IsBeforeEdge(Edge& a, Edge& b)
{
    return a.w<b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{

    long long numOfJunctions, numOfRoads, Min, total;

    Edge *arr, edge;
	DisjointSets ds;

	while (cin >> numOfJunctions >> numOfRoads && numOfJunctions!=0 && numOfRoads!=0)
    {
        Min=0, total=0;
        arr = new Edge [numOfRoads];

        for(long long i=0; i<numOfRoads; i++)
        {
            cin >> edge.u >> edge.v >> edge.w;
            arr[i] = edge;
        }

        MergeSort(arr, numOfRoads, IsBeforeEdge);
        ds.Initialize(numOfJunctions);

        for(long long i=0; i<numOfRoads; i++)
        {
           if(ds.Find(arr[i].u) != ds.Find(arr[i].v)){
            ds.Union(arr[i].u, arr[i].v);
            Min+=arr[i].w;
           }
           total+=arr[i].w;
        }

        delete [] arr;
        cout << total - Min << endl;
    }

    ds.Destroy();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
