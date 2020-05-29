#include <iostream>
#include <cmath>
#include <time.h>

#include "nrutil.c"
#include "gaussj.c"


#define n 1000
#define m 5
#define max(X,Y) ((X)>(Y)? (X):(Y))
#define min(X,Y) ((X)<(Y)? (X):(Y))
#define abs(X) ((X)>0? (X):-(X))

void matrixvector(double**A, double*x, double*y);
double scalar(double *a, double *b, bool flagt=false);
void addvector(double *a, double *b, double *d, double c);


int main(){

    double **A = new double *[n];
    double *b = new double[n];
    double *x = new double[n];
    double *r = new double[n];
    double *tmp = new double[n];
    double *tmp2 = new double[n];
    double alpha =0.;

    clock_t start, end;
    double time;

    FILE *f1 = fopen("zad_a.dat", "w");
    FILE *f2 = fopen("zad_b.dat", "w");


//######################################################################################################
// X0 = 0

    for(int i=0;i<n;i++)
        A[i] = new double[n];

    for(int i=0;i<n;i++)
    {
        b[i]=i+1;
        x[i]=0.;
        r[i]=0.;
        tmp[i]=0.;
        for(int j=0;j<n;j++)
        {
            if(abs(i-j)<=m)
                A[i][j]=1./(1.+ abs(i-j));
            else
                A[i][j]=0.;
        }
    }

    int k=1;
    double norma1=0.;
    double norma2=0.;

    start=clock();

    do{

        matrixvector(A, x, tmp); //tp=A*x
        addvector(b, pom, r, -1); //r = b - tmp = b - A*x
        matrixvector(A, r, tmp2); // tmp = A *r = A *( b-A*x)
        alpha = scalar(r,r,true) / scalar(r, tmp2, true);
        addvector(x, r, x, alpha); // x = xx + alpha*r

        norma1 = sqrt(scalar(r,r,true));
        norma2 = sqrt(scalar(x,x,true));
        fprintf(f1, "%d %lf %lf %lf\n", k, norma1, alpha, norma2);

        k++;


    }while(norma1>1e-6);

    end=clock();
    time= static_cast<double>(end-start)/ static_cast<double>(CLOCKS_PER_SEC);
    printf("time 1: %lf\n", time);

    delete [] tmp;
    delete [] tmp2;

//######################################################################################################
// X0 = 1


    tmp=new double[n];
    tmp2=new double[n];

    for(int i=0;i<n;i++)
    {
        x[i]=1.;
        r[i]=0.;
        tmp[i]=0.;
    }

    k=1;
    norma1=0.;
    norma2=0.;

    start=clock();

    do{

        matrixvector(A, x, tmp); //tmp=A*x
        addvector(b, tmp, r, -1); //r = b - tmp = b - A*x
        matrixvector(A, r, tmp2); // tmp = A *r = A *( b-A*x)
        alpha = scalar(r,r,true) / scalar(r, tmp2, true);
        addvector(x, r, x, alpha); // x = xx + alpha*r

        norma1 = sqrt(scalar(r,r,true));
        norma2 = sqrt(scalar(x,x,true));
        fprintf(f2, "%d %lf %lf %lf\n", k, norma1, alpha, norma2);
        k++;


    }while(norma1>1e-6);

    end=clock();

    time = static_cast<double>(end-start)/ static_cast<double>(CLOCKS_PER_SEC);
    printf("time 2: %lf\n", time);


//######################################################################################################
// gaussjc


    float **a = matrix(1, n, 1, n);
    float **d = matrix(1, n, 1, 1);


    for(int i=1;i<n+1;i++)
        d[i][0]=i+1;

    for(int i=1;i<n+1;i++)
    {
        for(int j=1;j<n+1;j++)
        {
            if(abs(i-j)<=m)
                a[i][j]=1./(1.+(abs(i-j)));
            else
                a[i][j]=0.;
        }
    }

    start=clock();

    gaussj(a,n,d,1);

    end=clock();
    time= static_cast<double>(end-start)/static_cast<double>(CLOCKS_PER_SEC);

    printf("time 3: %lf\n", time);




    for(int i=0;i<n;i++)
    {
        delete[] A[i];
    }
    delete[] A;
    delete[] x;
    delete[] b;
    delete[] r;
    delete[] tmp;
    delete[] tmp2;

    free_matrix(a, 1,n,1,n);
    free_matrix(d, 1,n,1,1);
}

void matrixvector(double**A, double*x, double*y)
{   int jmin, jmax;
    for(int i=0;i<n;i++){
        jmin=max(0,i-m);
        jmax=min(i+m,n-1);
        y[i]=0;
        for(int j=jmin;j<=jmax;j++)
            y[i]+=A[i][j]*x[j];
    }
}
double scalar(double *a, double *b, bool flagt=false)
{
    double s=0.;
    if(flagt)
    {
        for(int i=0;i<n;i++)
            s+=a[i]*b[i];
    }
    else
    {
        for(int i=0;i<n;i++)
            s+=b[i]*a[n-1-i];
    }

    return s;

}
void addvector(double *a, double *b, double *d, double c)
{
    for(int i=0;i<n;i++)
    {
        d[i] = a[i] + c*b[i];
    }
}
