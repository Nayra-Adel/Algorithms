// UVA:     10130
// Name:    Nayra Adel Hamed

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Obj
{
	int v; // value (price) of object
	int w; // weight of object
};

Obj a[1000];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[1001][31];
int Knapsack1(int N, int W)
{
    if(N == 0)
    {
        T1[N][W] = 0;
        return 0;
    }

    if(T1[N][W] >= 0) return T1[N][W];

    int res = Knapsack1(N-1, W);

    int CV = a[N-1].v;  // CV = currentValue
    int CW = a[N-1].w;  // CW = currentWeight

    if(CW <= W)
    {
        int r = CV + Knapsack1(N-1, W-CW);
        if (r > res) res = r;
    }

    T1[N][W] = res;
    return res;

}

int ComputeKnapsack1(int N, int W) // Recursive - memoization - initialize T then call Knapsack1(N,W);
{

    for(int i=0; i<1001; i++)
        for(int j=0; j<31; j++)
            T1[i][j] = -1;

    return Knapsack1(N, W);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[1001][31];
int ComputeKnapsack2(int N, int W) // Bottom-up, do not save space
{
    for(int n=0; n<=N; n++)
    {
        for(int w=0; w<=W; w++)
        {
            if(n == 0)
            {
                T2[n][w] = 0;
                continue;
            }

            int res = T2[n-1][w];
            int CV = a[n-1].v;  // CV = currentValue
            int CW = a[n-1].w;  // CW = currentWeight

            if(CW <= w)
            {
                int r = CV + T2[n-1][w-CW];
                if (r > res)
                {
                    res = r;
                }
            }
        T2[n][w] = res;
        }
    }
    return T2[N][W];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][31];
int ComputeKnapsack3(int N, int W) // Bottom-up, use two rows only
{
    int cur = 0;
    for(int n=0; n<=N; n++)
    {
        for(int w=0; w<=W; w++)
        {
            if(n == 0)
            {
                T3[cur][w] = 0;
                continue;
            }

            T3[cur][w] = T3[1-cur][w];

            int CV = a[n-1].v;  // CV = currentValue
            int CW = a[n-1].w;  // CW = currentWeight

            if(CW <= w)
            {
                int r = CV + T3[1-cur][w-CW];
                if (r > T3[cur][w])
                {
                    T3[cur][w] = r;
                }
            }
        }
        cur = 1 - cur;
    }
    return T3[1-cur][W];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[31];
int ComputeKnapsack4(int N, int W) // Bottom-up, save maximum space
{
    for(int n=0; n<=N; n++)
    {
        for(int w=W; w>=0; w--)
        {
            if(n == 0)
            {
                T4[w] = 0;
                continue;
            }

            int CV = a[n-1].v;  // CV = currentValue
            int CW = a[n-1].w;  // CW = currentWeight

            if(CW <= w)
            {
                int r = CV + T4[w-CW];
                if (r > T4[w])
                {
                    T4[w] = r;
                }
            }
        }
    }
    return T4[W];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeKnapsack(int N, int W) // Here we can choose the method
{
	//return ComputeKnapsack1(N,W);
	//return ComputeKnapsack2(N,W);
	return ComputeKnapsack3(N,W);
	//return ComputeKnapsack4(N,W);
}

void Compute() // Get input and call ComputeKnapsack() whenever needed
{
    int T, N, G, MW, sum;
	cin >> T;
    for(int i=0; i<T; i++){
        cin >> N;
        for (int i = 0; i < N; i++)
        {
            cin >> a[i].v >> a[i].w;
        }

        cin >> G;
        sum = 0;

        for (int i = 1; i <= G; i++){
            cin >> MW;
            sum += ComputeKnapsack(N, MW);
        }
        cout << sum << endl;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//freopen("input_assign09_10130.txt", "r", stdin);
	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
