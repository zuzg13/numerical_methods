#include <stdio.h>

#include "nrutil.c" //functions from Numerical Recipes in C library
#include "gaussj.c"

#define N 300// matrix size

int main(void)
{
	float **A, **b;
	double a =1.0;
	double v0=0.;
	double h=0.1;
	double w=1.0;
	double wh=w*w*h*h-2.;
	//	creating matrixes

	A = matrix(1, N, 1, N);
	b = matrix(1, N, 1, 1);

	// 	assigning values to matrices
	for (int i = 1; i <= N; ++i)
	{
		b[i][1] = 0.0;
		for (int j = 1; j <= N; ++j)
			A[i][j] = 0.0;
	}
	b[1][1] = a;
	b[2][1] = v0 * h;
	A[2][1] = -1.0;

	for(int i=1; i<=N; i++)
    {
	    A[i][i]=1.0;
    }
	for(int i=3;i<=N;i++)
    {
	    A[i][i-1]=wh;
	    A[i][i-2]=1.0;
    }

	//	Solving quation Mx=b :
	gaussj(A, N, b, 1);

	FILE *f;
	f = fopen("results.dat", "w");


	for (int i = 1; i <= N; ++i)
		fprintf(f, "%f %g\n", (i-1)*h, b[i][1]);
    fclose(f);

	free_matrix(A, 1, N, 1, N);
	free_matrix(b, 1, N, 1, 1);

	return 0;
}
