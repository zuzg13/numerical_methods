#include <iostream>
#include <cmath>
#define max(X,Y) ((X)>(Y)? (X):(Y))
#define min(X,Y) ((X)<(Y)? (X):(Y))
#define N 7
#define IT_MAX 12


void multiplyMatrix(double**a, double **b, double **c, int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            c[i][j]=0.;
            for(int k=0;k<n;k++)
                c[i][j] += a[i][k]*b[k][j];
        }
    }
}

double scalar(double *a, double *b, int n)
{
    double x=0.;

    for(int i=0;i<n;i++)
        x+= a[i] * b[i];
    return x;
}

void matrixvector(double**A, double*x, double*y, double m, double n)
{   int jmin, jmax;
    for(int i=0;i<n;i++){
        jmin=max(0,i-m);
        jmax=min(i+m,n-1);
        y[i]=0;
        for(int j=jmin;j<=jmax;j++)
            y[i]+=A[i][j]*x[j];
    }
}

void vectornumber(double *v1, double *v2, double val, int n)
{
    for(int i=0;i<n;i++) v2[i] = v1[i]*val;
}

void Hotteling(double **W, double *xk, double lambdak)
{
    for(int i=0;i<N; i++)
        for(int j=0;j<N;j++)
            W[i][j] = W[i][j] - lambdak * xk[i] *xk[j];
}

void printMX(double **m)
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
            printf("%g ", m[i][j]);
        std :: cout << std :: endl;
    }

}

void printV(double *v)
{
    for(int i=0;i<N;i++)
        std :: cout << v[i] << " ";
    std :: cout << std :: endl;
}



void transposeMX(double **a)
{
    double **pom = new double*[N];
    int i, j;
    for(i=0;i<N;i++)
    {
        pom[i] = new double[N];
        for (j = 0; j < N; j++) {
            pom[i][j] = a[j][i];
        }
    }
    for(i=0;i<N;i++)
        for(j=0;j<N;j++)
        {
            a[i][j]=pom[i][j];
        }
}

int main() {

    FILE *f1 = fopen("lambda.dat", "w+");

    double **A = new double*[N];
    double **W = new double*[N];
    double **X = new double*[N];
    double *L = new double[N];
    for(int i=0;i<N;i++)
    {
        A[i] = new double[N];
        W[i] = new double[N];
        X[i] = new double[N];
    }

    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
        {
            A[i][j] = 1./(sqrt(2. + fabs(i-j)));
            W[i][j] = 1./(sqrt(2. + fabs(i-j)));
        }


    int Kval = N;
    double *xp1 = new double [N];
    double *xp2 = new double [N];
    double lambda=0.;

    for(int k=0;k<Kval;k++)
    {
        for(int i=0;i<N;i++)
            xp1[i]=1;

        for(int i=1;i<=IT_MAX;i++)
        {
            matrixvector(W, xp1, xp2, N, N);
            lambda = scalar(xp2, xp1, N)/scalar(xp1, xp1, N);
            fprintf(f1, "%d %g \n", i, lambda);
            vectornumber(xp2, xp1, 1./sqrt(scalar(xp2, xp2, N)), N);
        }
        fprintf(f1, "\n \n");
        //wartosci wlasne wpisuje wierszami, by pozniej dokonac transpozycji macierzy
        for(int i=0;i<N;i++)
            X[k][i] = xp1[i];

        L[k] = lambda;
        Hotteling(W, xp1, lambda);

    }

    transposeMX(X);
    printMX(X);
    std :: cout << std::endl;
    printV(L);

    double **D = new double*[N];
    double **pom = new double*[N];
    for(int i=0;i<N;i++)
    {
        D[i] = new double[N];
        pom[i] = new double[N];
    }
    transposeMX(X);

    multiplyMatrix(X, A, pom, N);
    transposeMX(X);
    multiplyMatrix(pom, X, D, N);

    std :: cout << std::endl;
    printMX(D);

    for(int i=0;i<N;i++)
    {
        delete [] D[i];
        delete [] A[i];
        delete [] pom[i];
        delete [] X[i];
        delete [] W[i];
    }

    delete [] D;
    delete [] A;
    delete [] pom;
    delete [] X;
    delete [] W;
    delete [] xp1;
    delete [] xp2;
    delete [] L;

    fclose(f1);






}