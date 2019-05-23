// UVA:     10245
// Name1:   Nayra Adel Hamed

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>     // please use the built-in sqrt() function
#include <limits>
#include <iomanip>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = n/2, i=0, k, j=mid;
    if(n<=1) return;
    Type *t = new Type [n];

    for(k=0; k<n; ++k)
    {
        if(j==n || (i < mid && IsBefore(a[i], a[j])))
            t[k] = a[i++];
        else
            t[k] = a[j++];
    }
    for(i=0; i<n; ++i)
        a[i] = t[i];

    delete[] t;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int mid = n/2;
    if(n <= 1) return;

    MergeSort<Type>(a, mid, IsBefore);
    MergeSort<Type>(a+mid, n-mid, IsBefore);
    Merge<Type>(a, n, IsBefore);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point
{
	double x,y;
};

bool IsBeforeX(Point& a, Point& b)
{
    return a.x < b.x;
}
bool IsBeforeY(Point& a, Point& b)
{
    return a.y < b.y;
}

double dist(Point& a, Point& b)
{
    return sqrt(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y))) ;
}

double Min(double x, double y)
{
	return (x < y)? x : y;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Sort the points p according to x before calling this function
double ClosestPair(Point* p, int n)
{
    double m, minDistance = numeric_limits<double>::infinity();

    if(n <= 3)
    {
        for(int i=0; i<n; ++i)
            for(int j=i+1; j<n; ++j)
                m = Min(m, dist(p[i], p[j]));

        return minDistance;
    }

    int mid = n/2;
    double a = ClosestPair(p, mid);
    double b = ClosestPair(p + mid, n-mid);

    m = Min(a, b);

    double xMidLine = (p[mid-1].x + p[mid].x) / 2;
    double maxRangeXPoint = xMidLine + m;
    double minRangeXPoint = xMidLine - m;

    Point *strip = new Point[n];
    int counter = 0;

    for(int i=0; i<n; ++i)
        if(p[i].x <= maxRangeXPoint && p[i].x >= minRangeXPoint)
            strip[counter++] = p[i];

    MergeSort<Point>(strip, counter, IsBeforeY);

    for (int i = 0; i < counter; ++i)
        for (int j = i+1; j < counter && (strip[j].y - strip[i].y) < m; ++j)
                m = Min(m, dist(strip[i], strip[j]));

    return m;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int N;
    while(cin >> N && N!=0)
    {
        Point *arr = new Point[N];
        for(int i = 0; i < N; i++)
            cin >> arr[i].x >> arr[i].y;

        MergeSort<Point>(arr, N, IsBeforeX);

        double res = ClosestPair(arr, N);

        if(res >= 10000)
            cout << "INFINITY" << endl;
        else
            cout << fixed << setprecision(4) << res << endl;
    }

	return 0;
}
