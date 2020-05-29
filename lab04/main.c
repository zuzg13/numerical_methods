#include <stdio.h>
#include <math.h>

#include "nrutil.h"
#include "nrutil.c"
#include "tred2.c"
#include "tqli.c"
#include "pythag.c"

#define n 5

void print(float ** m)
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            printf("%f ", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printVector(float * v)
{
    for(int i=1;i<=n;i++)
    {
        printf("%g ", v[i]);
    }
    printf("\n");
    printf("\n");
}


void fprint(float ** m, FILE * f)
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            fprintf(f, "%f ", m[i][j]);
        }
        fprintf(f, "\n");
    }
}

void multiplyMatrix(float**a, float **b, float **c)
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            c[i][j]=0.;
            for(int k=1;k<=n;k++)
                c[i][j] += a[i][k]*b[k][j];
        }
    }
}

void transponeMX(float **a)
{
    float ** pom =matrix(1,n,1,n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            pom[i][j]=a[j][i];
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            a[i][j]=pom[i][j];
        }
}

float scalar(float *a, float*b)
{
    float x=0.;

    for(int i=1;i<=n;i++)
        x+= a[i] * b[i];
    return x;
}

int main() {

    //zakomentowane linie w kodzie dotycza sposoby, ktory wymaga obliczenia wektorow wlasnych macierzy T

    float **A = matrix(1,n,1,n);
    float **Y = matrix(1,n,1,n);
    float *d = vector(1,n);
    float *e = vector(1,n);
    float *d1 = vector(1,n);
    float *e1 = vector(1,n);

    FILE * f = fopen("result.txt", "w+");

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            A[i][j] = (float)(sqrt(i+j));
            if(i==j)
                Y[i][j]=1.;
            else
                Y[i][j]=0.;

        }

    tred2(A, n, d, e);

    print(A);
    fprint(A, f);

    float **A2 = matrix(1,n,1,n);
    for(int i=1;i<=n;i++)
    {
        d1[i]=d[i];
        e1[i]=e[i];
        for(int j=1;j<=n;j++)
        {
            A2[i][j] = A[i][j];
        }

    }

    //tqli(d,e,n,Y);
    tqli(d1,e1,n,A2);

    print(A2);
    //printVector(d);
    printVector(d1);
    /*
    for(int i=1;i<=n;i++)
    {
        printf("Wektor wlasny y%d: ", i);
        for(int j=1;j<=n;j++)
        {
            printf("%g ", Y[j][i]);
        }
        printf("\n\n");
    }*/

    //float **X = matrix(1,n,1,n);

    //multiplyMatrix(A,Y,X);

    for(int i=1;i<=n;i++)
    {
        printf("Wektor wlasny x%d: ", i);
        for(int j=1;j<=n;j++)
        {
            printf("%g ", A2[j][i]);
        }
        printf("\n\n");
    }

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            A[i][j] = (float)(sqrt(i+j));

    float *beta = vector(1,n);
    float **Z = matrix(1,n,1,n);
    multiplyMatrix(A, A2, Z);
    transponeMX(A2);
    transponeMX(Z);
    for(int i=1;i<=n;i++)
    {
        beta[i] = scalar(A2[i], Z[i])/scalar(A2[i], A2[i]);
        printf("beta %d = %g \n", i, beta[i]);
    }


    free_matrix(Z, 1,n,1,n);
    free_matrix(A, 1,n,1,n);
    free_matrix(A2, 1,n,1,n);
    free_matrix(Y, 1,n,1,n);
    free_vector(beta, 1,n);
    free_vector(d, 1,n);
    free_vector(e, 1,n);
    free_vector(d1, 1,n);
    free_vector(e1, 1,n);




}