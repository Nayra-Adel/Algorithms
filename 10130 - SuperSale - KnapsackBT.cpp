// UVA:     10130
// Name:    Nayra Adel Hamed

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
using namespace std;

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

struct Obj
{
	int v;
	int w;
};

int n;       // number of objects (input)
Obj a[1000]; // objects (input)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBefore(Obj& a, Obj& b) // return true if unit value of a is greater than unit value of b
{
    return (double) a.v/a.w > (double) b.v/b.w;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int best_val; // the best total value found until now

int Bound(int i, int w) // upper bound on the total value of items [i..n-1] that can fit in w
{
    double bound = 0;
    double remaining = w;
    int b;

    for(b = i; b < n; ++b)
    {
        if(a[b].w <= remaining)
        {
            remaining -= a[b].w;
            bound += a[b].v;
        }
        else
        {
            bound += ( (double) a[b].v / a[b].w ) * remaining;
            break;
        }
    }

    return bound;
}

void BackTrack(int i, int w, int cur_val) // starting from item i, remaining weight w, cur_value of objects[0..i-1]
{
    if (i == n)
    {
        if(cur_val > best_val)
        {
            best_val = cur_val;
        }
        return ;
    }

    if(cur_val + Bound(i, w) < best_val) return;

    if(a[i].w <= w)
    {
        BackTrack(i+1, w - a[i].w, cur_val + a[i].v);
    }

    BackTrack(i+1, w, cur_val);
}

int ComputeKnapsack(int N, int W)
{
    best_val = 0;
    BackTrack(0, W, 0);
    return best_val;
}

void Compute()
{
    int T, G, MW, sum;
	cin >> T;
    for(int i=0; i<T; ++i){

        cin >> n;

        for (int i = 0; i < n; i++)
        {
            cin >> a[i].v >> a[i].w;
        }

        MergeSort(a,n, IsBefore);

        cin >> G;
        sum = 0;

        for (int i = 1; i <= G; i++)
        {
            cin >> MW;
            sum += ComputeKnapsack(0, MW);
        }
        cout << sum << endl;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign12_10130.txt", "r", stdin);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
