#include "Funs.h"

double fun(double x)
{
    return exp(-x*x);
}

double lagrange(double* wez, double* wart, int st, double x)
{
    double w = 0.;
    double omega = 1.;
    for(int j=0; j<st+1; j++)
    {
        for(int i=0; i<st+1; i++)
        {
            if(i != j)
                omega *= (x - wez[i]) / (wez[j] - wez[i]);
        }
        w += wart[j] * omega;
        omega = 1.;
    }
    return w;

}

void set(double *xn, double *yn, int size, double xmin, double xmax, int option)
{
    for(int i=0;i<size+1;i++)
    {
        if(option==1)
            xn[i] = xmin + ((xmax-xmin)/static_cast<double>(size)*i);
        else
            xn[i] = czebyszew(xmin, xmax, i, size);

        yn[i] = fun(xn[i]);

        std::cout << xn[i] << " " << yn[i] << std::endl;
    }
    std::cout << std::endl;
}

double czebyszew(double min, double max, int m, int n)
{
    return 0.5 * ((max - min) * cos(M_PI * ((2.0 * static_cast<double>(m) + 1.0) / (2.0 * static_cast<double>(n) + 2.0))) +
           (min + max));
}


void calculate_and_save(double*xn, double*yn, int size, double x, std::fstream &file)
{

    for(int i = 0; i <= 100; i++)
    {
        double wn = lagrange(xn, yn, size, x);

        file << x << " " << wn <<"\n";
        x += 0.1;
    }
    file << "\n\n";
}