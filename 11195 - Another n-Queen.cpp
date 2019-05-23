// UVA:     11195
// Name:    Nayra Adel Hamed

#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MAX_QUEENS 15

int		n; // number of queens (input)
bool board[MAX_QUEENS][MAX_QUEENS];

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool col_Taken[MAX_QUEENS];
bool fdiag_taken[(2*MAX_QUEENS)-1];
bool bdiag_taken[(2*MAX_QUEENS)-1];

int num_sol = 0;
int cur_sol[MAX_QUEENS];

void Backtrack1(int r)
{
    if (r == n)
    {
        num_sol++;
        return;
    }

    for(int c=0; c<n; c++)
    {
        if(!col_Taken[c] && !fdiag_taken[r-c+(n-1)] && !bdiag_taken[r+c] &&  board[r][c])
        {
            cur_sol[r] = c;

            col_Taken[c] = true;
            fdiag_taken[r-c+(n-1)] = true;
            bdiag_taken[c+r] = true;

            Backtrack1(r+1);

            col_Taken[c] = false;
            fdiag_taken[r-c+(n-1)] = false;
            bdiag_taken[c+r] = false;
        }

    }
}

void Compute1() // do necessay initializations and call Backtrack1()
{
    for(int i=0; i<n; i++)
    {
        col_Taken[i] = false;
    }

    for(int i=0; i<(2*n)-1; i++)
    {

        fdiag_taken[i] = false;
        bdiag_taken[i] = false;
    }

    Backtrack1(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Dancing Links:

int F[MAX_QUEENS + 1]; // head=F[0], elements are indexed from 1 to n, F[n]=0
int B[MAX_QUEENS + 1]; // B[0]=n, B[1]=0
void Remove(int i) {F[B[i]]=F[i]; B[F[i]]=B[i];}
void Restore(int i) {B[F[i]]=i; F[B[i]]=i;}
void InitDancingLinks(int n)
{
	int i;
	for(i=0;i<n;i++) F[i]=i+1; F[n]=0;
	for(i=n;i>0;i--) B[i]=i-1; B[0]=n;
}
// for(i=F[0];i!=0;i=F[i]) iterate on available list indexes

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Backtrack2(int i) // backtrack using dancing links
{
    if (i == n)
    {
        num_sol++;
        return;
    }

    for(int j=F[0]; j!=0; j=F[j])
    {
        if(board[i][j-1] && !fdiag_taken[i-j+(n-1)] && !bdiag_taken[j+i])
        {
            cur_sol[i] = j-1;

            fdiag_taken[i-j+(n-1)] = true;
            bdiag_taken[i+j] = true;
            Remove(j);

            Backtrack2(i+1);

            fdiag_taken[i-j+(n-1)] = false;
            bdiag_taken[i+j] = false;
            Restore(j);

        }
    }
}

void Compute2() // do necessay initializations and call Backtrack2()
{
    InitDancingLinks(n);

    for(int i=0; i<(2*n)-1; i++)
    {
        fdiag_taken[i] = false;
        bdiag_taken[i] = false;
    }

    Backtrack2(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ComputeCore()
{
	 //Compute1();
	 Compute2();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Compute() // get input and then call ComputeCore(); then print output
{
    char ch;
	int Counter = 0;

	while (true)
    {
        cin >> n;

        if(n == 0) break;

        num_sol = 0;

		Counter++;

		for (int i = 0; i < n; i++)
        {
			for (int j = 0; j < n; j++)
            {
				cin >> ch;

                if(ch == '.')
                    board[i][j] = 1 ;
                else
                    board[i][j] = 0 ;
			}
		}

		ComputeCore();
		cout << "Case " << Counter << ": " << num_sol << endl;
	}

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	// freopen("input_assign13_00216.txt", "r", stdin);
    // freopen("output_assign13_00216.txt", "w", stdout);

	Compute();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
