// UVA:     348
// Name:    Nayra Adel Hamed

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int p[11]; // the dimensions of matrices

int T[11][11]; // T[a][b]=the optimal number of multiplication of p[a]...p[b]
int D[11][11]; // D[a][b]=the decision (value of k) that gets T[a][b]

// Top down version
int MatChain(int a, int b) // Recursive, cost of multiplying the b-a matrices with indexes: a...b-1
{
    if(a+1 == b)
    {
        T[a][b] = 0;
        return 0;
    }

    if(T[a][b] >= 0)
    {
        return T[a][b];
    }

    int k;
    T[a][b] = 0X7FFFFFFF;
    for(k = a+1; k < b; k++)
    {
        int v = MatChain(a, k) + MatChain(k, b) + (p[a]*p[k]*p[b]);

        if(v < T[a][b])
        {
            T[a][b] = v;
            D[a][b] = k;
        }
    }
    return T[a][b];
}

void MatChainTopDown(int n) // Initialize T then call MatChain(0,n)
{
    for(int i=0; i<11; i++)
    {
        for(int j=0; j<11; j++)
        {
            T[i][j] = -1;
        }
    }

    MatChain(0, n);
}
// BottomUp version
void MatChainBottomUp(int n)
{
    int j;
    int k;

    for(int s=1; s <= n; ++s)
    {
        for(int i=0; i+s <= n; ++i)
        {
            j = i + s;
            if(i+1 == j)
            {
                T[i][j] = 0;
                continue;
            }

            T[i][j] = 0X7FFFFFFF;
            for(k = i+1; k < j; k++)
            {
                int v = T[i][k] + T[k][j] + (p[i]*p[k]*p[j]);

                if(v < T[i][j])
                {
                    T[i][j] = v;
                    D[i][j] = k;
                }
            }
        }
    }
}

// Recursive to output the solution for both versions
void MatChainSol(int a, int b)
{
    if(a+1 == b)
    {
        cout << "A" << a+1;
    }
    else
    {
        int k = D[a][b];
        cout << "(";
        MatChainSol(a, k);
        cout << " x ";
        MatChainSol(k, b);
        cout << ")";
    }

}

void Compute()
{
    int n, k, i, r=1;
    while (true)
    {
        cin >> n;

        if(n == 0) break;

        for(i=0; i<n; i++)
        {
            cin >> p[i] >> k;
        }
        p[i] = k;

        //MatChainTopDown(n);
        MatChainBottomUp(n);
        cout << "Case " << r << ": ";
        MatChainSol(0, n);
        cout << endl;
        r++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //freopen("input_assign10_00348.txt", "r", stdin);
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
