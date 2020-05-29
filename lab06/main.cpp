#include <iostream>
#include <cmath>


double fun(double x)
{
    return (x - 1.2)*(x - 2.3)*(x-3.3)*(x-3.3);
}

double derivative(double x, double dx)
{
    return (fun(x +dx) - fun(x - dx))/(2*dx);
}

double ufun(double x, double dx)
{
    return fun(x)/derivative(x, dx);
}

int main() {

    double x0, x1, x2;

    //niemodyfikowalna metoda siecznych

    //x0 = 0.9;
    //x1 = 1.0;

    //x0 = 1.7;
    //x1 = 1.75;

    x0 = 3.7;
    x1 = 3.65;

    for(int k = 1; k<=10000; ++k)
    {
        x2 = x1 - fun(x1)*(x1-x0)/(fun(x1)- fun(x0));

        std :: cout << "iteracja " << k << ", x_(k+1)= " << x2;
        std :: cout << ", epsilon = " << fabs(x2-x1);
        std :: cout << ", f(x_(k+1)) = "<< fun(x2) << std::endl;
        /*
        std :: cout << k << " & ";
        std :: cout << x2 << " & ";
        std :: cout << abs(x2-x1) << " & ";
        std :: cout << fun(x2) << " \\" << "\\" << std :: endl;*/


        if(fabs(x2 - x1) < 1e-6)
            break;
        x0 = x1;
        x1 = x2;

    }

    std ::  cout << std :: endl;

    //modyfikowna metoda siecznych

    //x0 = 0.9;
    //x1 = 1.0;

    //x0 = 1.7;
    //x1 = 1.75;

    x0 = 3.7;
    x1 = 3.65;

    double dx = 0.1;

    for(int k = 1; k<=10000; ++k)
    {
        x2 = x1 - ufun(x1, dx)*(x1-x0)/(ufun(x1, dx)- ufun(x0, dx));
        std :: cout << "iteracja " << k << ", x_(k+1)= " << x2;
        std :: cout << ", epsilon = " << fabs(x2-x1);
        std :: cout << ", f(x_(k+1)) = "<< fun(x2) << std::endl;
        /*
        std :: cout << k << " & ";
        std :: cout << x2 << " & ";
        std :: cout << abs(x2-x1) << " & ";
        std :: cout << fun(x2) << " \\" << "\\" << std :: endl;*/

        if(fabs(x2 - x1) < 1e-6)
            break;

        x0 = x1;
        x1 = x2;

    }
    std ::  cout << std :: endl;

    dx = 0.001;

    //x0 = 1.7;
    //x1 = 1.75;

    //x0 = 0.9;
    //x1 = 1.0;

    x0 = 3.7;
    x1 = 3.65;

    for(int k = 1; k<=10000; ++k)
    {
        x2 = x1 - ufun(x1, dx)*(x1-x0)/(ufun(x1, dx)- ufun(x0, dx));

        std :: cout << "iteracja " << k << ", x_(k+1)= " << x2;
        std :: cout << ", epsilon = " << fabs(x2-x1);
        std :: cout << ", f(x_(k+1)) = "<< fun(x2) << std::endl;
        /*
        std :: cout << k << " & ";
        std :: cout << x2 << " & ";
        std :: cout << abs(x2-x1) << " & ";
        std :: cout << fun(x2) << " \\" << "\\" << std :: endl;*/

        if(fabs(x2 - x1) < 1e-6)
            break;

        x0 = x1;
        x1 = x2;

    }



}