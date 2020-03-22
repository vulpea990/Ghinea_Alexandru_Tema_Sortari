#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

ifstream f ("Numbers.in");
ofstream g ("Time.out");

long long max_value,max_lenght, max_i,k, v[10000000],a[10000000],b[10000000],n;
double start_bubble, stop_bubble, start_count ,stop_count, start_radix, stop_radix, start_merge, stop_merge, start_quick, stop_quick ;



int verify(long long v[])
{
     for(long long i=0; i<n-1; i++)
        if(v[i]>v[i+1])
            return 0;

     return 1;
}

void generator()
{
    ofstream g("Numbers.in");
    long long len,x;
    srand(time(NULL));
    len=max_lenght;
    for(long long i = 1; i <= len; i++)
        {
            x = rand() % max_value ;
                g << x << " ";
                if(i%10==0)
                    g<<endl;
        }
    g.close();

}

void read()
{
     for(long long i=0; i<n; i++)
     {
         f>>v[i];
         a[i]=v[i];
         if(v[i]>max_i)
            max_i=v[i];
         k=max_i;

     }
}
void bubblesort(long long v[], long long n)
{
    long long aux,i,j;
    for(i=0; i<n-1; i++)
        for(j=i+1; j<n; j++)
            if(v[i]>v[j])
            {
                aux=v[i];
                v[i]=v[j];
                v[j]=aux;
            }
}

void countsort()
{
    long long j=0;
    for(long long i=0;i<n;i++)
        b[v[i]]++;
    for(long long i=0;i<=k;i++)
            while(b[i])
            {
                v[j]=i;
                j++;
                b[i]--;
            }

}

int getmax(long long v[], long long n)
{
    long long maxim = v[0];
    for (long long i = 1; i < n; i++)
        if (v[i] > maxim)
            maxim = v[i];
    return maxim;
}
void countradix(long long v[], long long n, long long p)
{
    long long maxx = 10;
    long long o[100000];
    long long c[maxx];

    for (long long i = 0; i < maxx; ++i)
        c[i] = 0;

    for (long long i = 0; i < n; i++)
        c[(v[i] / p) % 10]++;
    for (long long i = 1; i < maxx; i++)
        c[i] += c[i - 1];

    for (long long i = n - 1; i >= 0; i--)
    {
        o[c[(v[i] / p) % 10] - 1] = v[i];
        c[(v[i] / p) % 10]--;
    }

    for (long long i = 0; i < n; i++)
        v[i] = o[i];
}
void radixsort(long long v[], long long n)
{
    long long maxim1= getmax(v, n);

    for (long long p = 1; maxim1 / p > 0; p *= 10)
        countradix(v, n, p);
}
void mergee(long long v[], long long li, long long mij, long long ls)
{
    long long i, j, k;
    long long nr1 = mij - li + 1;
    long long nr2 =  ls - mij;
    long long L[nr1], R[nr2];
    for (i = 0; i < nr1; i++)
        L[i] = v[li + i];
    for (j = 0; j < nr2; j++)
        R[j] = v[mij + 1+ j];
    i = 0;
    j = 0;
    k = li;
    while (i < nr1 && j < nr2)
    {
        if (L[i] <= R[j])
        {
            v[k] = L[i];
            i++;
        }
        else
        {
            v[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < nr1)
    {
        v[k] = L[i];
        i++;
        k++;
    }
    while (j < nr2)
    {
        v[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(long long v[], long long l, long long r)
{
    if (l < r)
    {
        long long m = l+(r-l)/2;

        mergesort(v, l, m);
        mergesort(v, m+1, r);

        mergee(v, l, m, r);
    }
}

int part(long long v[], int li, int ls)
{
    long long piv = v[ls];
    long long i = (li - 1);
    long long aux,j;

    for (j = li; j <= ls - 1; j++)
    {

        if (v[j] < piv)
        {
            i++;
             aux=v[i];
             v[i]=v[j];
             v[j]=aux;
        }
    }
     aux=v[i+1];
     v[i+1]=v[ls];
     v[ls]=aux;
    return (i + 1);
}


void quicksort(long long v[], long long li, long long ls)
{
    if (li < ls)
    {
        long long piv= part(v,li,ls);
        quicksort(v, li, piv - 1);
        quicksort(v, piv + 1, ls);
    }
}
int main()
{

    cin>>max_lenght>>max_value;
    n=max_lenght;
    generator();
    read();

    for(long long i=0; i<n; i++)
        v[i]=a[i];
        auto start_bubble= high_resolution_clock::now();
        bubblesort(v,n);
        auto stop_bubble = high_resolution_clock::now();
        auto duration_bubble= duration_cast<microseconds>(stop_bubble-start_bubble);
        if(verify(v))
        {
            g<<"Bubblesort works ^_^  ";
            g<<"Time: "<< duration_bubble.count()<<endl;
        }
        else
            g<<"Bubblesort doesn't work #_#";



    auto start_count= high_resolution_clock::now();
    countsort();
    auto stop_count = high_resolution_clock::now();
    auto duration_count= duration_cast<microseconds>(stop_count-start_count);
    if(verify(v))
    {
        g<<"CountSort works ^_^  ";
        g<<"Time: "<< duration_count.count()<<endl;
    }
    else
        g<<"CountSort doesn't work #_#";

    for(long long i=0; i<n; i++)
        v[i]=a[i];
        auto start_radix= high_resolution_clock::now();
        radixsort(v,n);
        auto stop_radix = high_resolution_clock::now();
        auto duration_radix= duration_cast<microseconds>(stop_radix-start_radix);
        if (verify(v))
        {
             g<<"Radixsort works ^_^  ";
             g<<"Time: "<<duration_radix.count()<<endl;
        }
        else
            g<<"Radixsort doesn't work #_#";


    for(long long i=0; i<n; i++)
        v[i]=a[i];
        auto start_merge= high_resolution_clock::now();
        mergesort(v,0,n-1);
        auto stop_merge= high_resolution_clock::now();
        auto duration_merge= duration_cast<microseconds>(stop_merge-start_merge);
     if(verify(v))
   {
        g<<"Mergesort works ^_^ ";
        g<<"Time: "<< duration_merge.count()<<endl;
    }
        else
        g<<"Mergesort doesn't work #_#";


    for(long long i=0; i<n; i++)
        v[i]=a[i];
    auto start_quick= high_resolution_clock::now();
    quicksort(v, 0, n-1);
    auto stop_quick= high_resolution_clock::now();
    auto duration_quick = duration_cast<microseconds>(stop_quick-start_quick);
        if(verify(v))
            {
            g<<"Quicksort works ^_^ ";
            g<<"Time: "<<duration_quick.count() << endl;
        }
        else
            g<<"Quicksort doesn't work #_#";

    return 0;

}
