#include <stdio.h>
#include <math.h>
#include "nrutil.c" //functions from
#include "ludcmp.c" //Numerical Recipes in C
#include "lubksb.c" // library
#define N 4 // size of matrix

void print(float **mx, int size);
void set(float **A);
void fprint(float **m, FILE *f);


int main() {

    float **A;
    float d, e;
    int *indxA=ivector(1,N);
    FILE *f = fopen("result.txt", "w");
    A=matrix(1, N, 1, N);

    set(A);
    printf("A:\n");
    print(A, N);

    ludcmp(A, N, indxA, &d);
    float **AL, **AU;
    AL=matrix(1,N, 1, N);
    AU=matrix(1,N, 1, N);

    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            if(i==j)
            {
                AU[i][j]=A[i][j];
                AL[i][j]=1;
            }
            else if(i>j)
            {
                AL[i][j]=A[i][j];
                AU[i][j]=0;
            }
            else
            {
                AU[i][j]=A[i][j];
                AL[i][j]=0;
            }
        }
    }
    fprintf(f,"Matrix L\n");
    fprint(AL, f);
    fprintf(f,"\nMatrix U\n");
    fprint(AU, f);


    for(int j=1;j<=N;j++) d *= A[j][j];
    printf("detA = %g\n", d);
    fprintf(f, "detA = %g\n", d);


    float **Ai=matrix(1,N,1,N);
    float *x=vector(1, N);
    printf("A^-1: \n");
    for (int j = 1; j <= N; j++) {
        for (int i = 1; i <= N; i++)
            x[i] = 0.0;
        x[j] = 1.0;
        lubksb(A, N, indxA, x);
        for (int i = 1; i <= N; i++)
            Ai[i][j]=x[i];
    }
    print(Ai, N);
    fprintf(f, "\nA^-1: \n");
    fprint(Ai, f);
    float **C=matrix(1,N,1,N);
    set(A);
    printf("A*A^-1=\n");
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            C[i][j]=0.;
            for(int k=1;k<=N;k++)
            {
                C[i][j]+=A[i][k]+Ai[k][j];
            }
        }
    }
    print(C, N);
    fprintf(f,"A*A^-1=\n");
    fprint(C, f);

    float maxA=fabs(A[1][1]);
    float maxAI=fabs(Ai[1][1]);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            if(fabs(A[i][j])>maxA)
                maxA=fabs(A[i][j]);
            if(fabs(Ai[i][j])>maxAI)
                maxAI=fabs(Ai[i][j]);

        }
    }
    float cos=maxA*maxAI;
    printf("\nMatrix A conditioning indicator = %f\n", cos);
    fprintf(f, "\nMatrix A conditioning indicator = %f\n", cos);

    fclose(f);
    free_vector(x, 1, N);
    free_ivector(indxA, 1, N);
    free_matrix(A, 1, N, 1, N);
    free_matrix(Ai, 1, N, 1, N);
    free_matrix(C, 1, N, 1, N);
    free_matrix(AL, 1, N, 1, N);
    free_matrix(AU, 1, N, 1, N);





}

void print(float **mx, int size)
{
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            printf("%3.2f ", mx[i][j]);
        }
        printf("\n");
    }
}

void set(float **A){

    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            A[i][j]=1./(i+j);
        }
    }

}

void fprint(float **m, FILE *f)
{
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            fprintf(f, "%3.2f ", m[i][j]);
        }
        fprintf(f, "\n");
    }
}
