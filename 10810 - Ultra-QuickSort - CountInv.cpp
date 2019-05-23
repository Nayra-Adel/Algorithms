// UVA:     10810
// Name:    Nayra Adel Hamed

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBeforeInt(long long& a, long long& b)
{
	return a<=b;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

long long CountInvMerge(long long* a, int n, bool (*IsBefore)(long long& , long long& ))
{
    int mid = n/2;

    if(n<=1) return 0;

    int i=0, k, j=mid;
    long long val=0;
    int *t = new int [n];

    for(k=0; k<n; k++)
    {
        if(j==n || (i < mid && IsBefore(a[i], a[j])))
        {
            t[k] = a[i++];
        }else
        {
            val += mid - i;
            t[k] = a[j++];
        }
    }
    for(i=0; i<n; i++)
    {
        a[i] = t[i];
    }

    return val;
}
long long CountInv(long long* a, int n, bool (*IsBefore)(long long& , long long& ))
{
    int mid = n/2;
    if (n <=1) return 0;
    return CountInv(a, mid, IsBefore) + CountInv(a+mid, n-mid, IsBefore) + CountInvMerge(a, n, IsBefore);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int n;
    long long *arr;
	while (cin >> n && n!=0)
    {
        arr = new long long [n];
        for(int i=0; i<n; i++)
        {
            cin >> arr[i];
        }
        cout << CountInv(arr, n, IsBeforeInt) << endl;
        delete [] arr;
    }
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
