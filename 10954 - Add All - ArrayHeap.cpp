// UVA:     10954
// Name:    Nayra Adel Hamed

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
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

    void print()
    {
        for(int i=0; i < n; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Elem>
struct Heap
{
    Array<Elem> a;
    bool (*IsBefore)(Elem &, Elem &);

    void Initialize(bool (*_IsBefore)(Elem &, Elem &))
    {
        IsBefore = _IsBefore;
        a.Initialize();
    }

    void Destroy()
    {
        a.Destroy();
    }

    int Child(int i)
    {
        return (i*2) + 1;
    }

    int Parent(int i)
    {
        return floor((i-1)/2);
    }

    void MoveUp(int ind)
    {
        int _parent = Parent(ind);
        while(_parent >= 0)
        {
            if(IsBefore(a[ind], a[_parent]))
            {
                // swap(a[Parent(ind)], a[ind]);
                Elem temp = a[Parent(ind)];
                a[Parent(ind)] = a[ind];
                a[ind] = temp;

                ind = _parent;
                _parent = Parent(_parent);
            }
            else
            {
                break;
            }
        }
    }

    /*
    void MoveUp(int ind)
    {
        if(IsBefore(a[ind], a[Parent(ind)]))
        {
            swap(a[Parent(ind)], a[ind]);
            MoveUp(Parent(ind));

        }
    }
    */

    void MoveDown(int ind)
    {
        int arrSize = a.n - 1, firstChild;

        while(true)
        {
            firstChild = Child(ind);

            if(firstChild > arrSize) break;

            if(firstChild + 1 <= arrSize)
            {
                if((a[firstChild] <= a[firstChild + 1]) && (a[firstChild] < a[ind]))
                {
                    // swap(a[firstChild], a[ind]);
                    Elem temp = a[firstChild];
                    a[firstChild] = a[ind];
                    a[ind] = temp;
                    ind = firstChild;
                }
                else if((a[firstChild + 1] <= a[firstChild]) && (a[firstChild + 1] < a[ind]))
                {
                    // swap(a[firstChild + 1], a[ind]);
                    Elem temp = a[firstChild + 1];
                    a[firstChild + 1] = a[ind];
                    a[ind] = temp;
                    ind = firstChild + 1;
                }
                else
                {
                    break;
                }
            }
            else
            {
                if(a[firstChild] < a[ind])
                {
                    // swap(a[firstChild], a[ind]);
                    Elem temp = a[firstChild];
                    a[firstChild] = a[ind];
                    a[ind] = temp;
                    ind = firstChild;
                }
                else
                {
                    break;
                }
            }
        }
    }

    /*
     void MoveDown(int ind)
    {
        int arrSize = a.n - 1, firstChild;

        while(true)
        {
            firstChild = Child(ind);

            if(firstChild > arrSize) break;

            if(firstChild + 1 <= arrSize)
            {
                if(min(a[firstChild], a[firstChild + 1]) < a[ind])
                {
                    if(a[firstChild] <= a[firstChild + 1])
                    {
                        swap(a[firstChild], a[ind]);
                        MoveDown(firstChild);
                    }
                    else
                    {
                        swap(a[firstChild + 1], a[ind]);
                        MoveDown(firstChild + 1);
                    }

                }
            }
            else
            {
                if(a[firstChild] < a[ind])
                {
                    swap(a[firstChild], a[ind]);
                    MoveDown(firstChild);
                }
            }
        }
    }
    */

    void Add(Elem e)
    {
        a.AddLast(e);
        MoveUp(a.n-1);
    }

    Elem GetFirst()
    {
        return a[0];
    }

    Elem RetrieveFirst()
    {
        Elem x = GetFirst();
        a[0] = a[a.n - 1];
        a.RemoveLast();
        MoveDown(0);
        return x;
    }

    void AddAll(Elem n)
    {
        Elem cost = 0, sum = 0;
        while(a.n != 1)
        {
            sum = RetrieveFirst();
            sum += RetrieveFirst();

            cost+=sum;

            Add(sum);
        }
        cout << cost << endl;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBeforeInt(int& a, int& b)
{
    return a < b;
}

int main()
{
    int n, num;
    Heap<int> h;

    while(cin>>n && n!=0)
    {
        h.Initialize(IsBeforeInt);

        for(int i=0; i<n; i++)
        {
            cin >> num;
            h.Add(num);
        }
        h.AddAll(n);
        h.Destroy();
    }
    return 0;
}
