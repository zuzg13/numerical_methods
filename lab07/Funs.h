#include <iostream>
#include <fstream>
#include <cmath>

double fun(double x);
double lagrange(double* wez, double* wart, int st, double x);

void set(double *xn, double *yn, int size, double xmin, double xmax, int option=1);

double czebyszew(double min, double max, int m, int n);

void calculate_and_save(double*xn, double*yn, int size, double x, std::fstream &file);