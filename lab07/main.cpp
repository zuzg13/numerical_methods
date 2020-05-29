#include <iostream>
#include "Funs.h"

int main() {

    double xmin = -5.;
    double xmax = 5.;

    int n[] = {5, 10, 15, 20};

    double *xn1 = new double[n[0]+1];
    double *yn1 = new double[n[0]+1];
    double *xn2 = new double[n[1]+1];
    double *yn2 = new double[n[1]+1];
    double *xn3 = new double[n[2]+1];
    double *yn3 = new double[n[2]+1];
    double *xn4 = new double[n[3]+1];
    double *yn4 = new double[n[3]+1];

    set(xn1, yn1, n[0], xmin, xmax, 1);
    set(xn2, yn2, n[1], xmin, xmax, 1);
    set(xn3, yn3, n[2], xmin, xmax, 1);
    set(xn4, yn4, n[3], xmin, xmax, 1);

    double x = xmin;

    std::fstream f1;
    std::fstream f2;
    f1.open("zad_1.dat", std::ios::out);
    f2.open("zad_2.dat", std::ios::out);

    calculate_and_save(xn1, yn1, n[0], x, f1);
    calculate_and_save(xn2, yn2, n[1], x, f1);
    calculate_and_save(xn3, yn3, n[2], x, f1);
    calculate_and_save(xn4, yn4, n[3], x, f1);

    set(xn1, yn1, n[0], xmin, xmax, 0);
    set(xn2, yn2, n[1], xmin, xmax, 0);
    set(xn3, yn3, n[2], xmin, xmax, 0);
    set(xn4, yn4, n[3], xmin, xmax, 0);

    calculate_and_save(xn1, yn1, n[0], x, f2);
    calculate_and_save(xn2, yn2, n[1], x, f2);
    calculate_and_save(xn3, yn3, n[2], x, f2);
    calculate_and_save(xn4, yn4, n[3], x, f2);

    f1.close();
    f2.close();

    delete [] xn1;
    delete [] yn1;
    delete [] xn2;
    delete [] yn2;
    delete [] xn3;
    delete [] yn3;
    delete [] xn4;
    delete [] yn4;


    return 0;

}