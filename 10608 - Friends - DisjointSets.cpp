// UVA:     10608
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
            parent[i] = i;
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
	    if(i > n || i < 0) return -1;

	    int k = i;
	    while(true)
        {
            if(parent[k] == k)
            {
                return k;
            }

            k = parent[k];
	    }
	}

	bool Union(int i, int j)
	{
	    int find_i = Find(i-1);
	    int find_j = Find(j-1);
	    if(find_i == find_j) return false;
	    else
        {
            if (num_nodes[find_j]!=0 && num_nodes[find_i]!=0)
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
            return false;
	    }
	}

	int max_ ()
	{
	    int m = num_nodes[0];
	    for(int i=1; i<n; i++)
        {
            if(num_nodes[i] > m)
            {
                m = num_nodes[i];
            }
        }
	    return m;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    DisjointSets d;
    int num_testCases, citizens, people, x, y;
    cin >> num_testCases;
    for(int i=0; i<num_testCases; i++)
    {
        cin >> citizens >> people;
        d.Initialize(citizens);

        for(int j=0; j<people; j++)
        {
            cin >> x >> y;
            d.Union(x, y);
        }

        cout << d.max_() << endl;
        d.Destroy();
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
