
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Predifed function
double func(double x)
{
    return (x * x * x) + (3 * x * x) - 2;
}

// find the differentiation of any function passed
double dfunc(double x, double (*f)(double))
{
    double dx = 0.000001;
    double dy1 = (*f)(x + (dx / 2));
    double dy2 = (*f)(x - (dx / 2));
    return (dy1 - dy2) / dx;
}


double recursiveNewtonRapson(double (*f)(double), double x)
{
    double x_prev = (*f)(x);

    while(fabs(x - x_prev) > 0.000001)
    {
        x_prev = x;
        x = x - ((*f)(x) / dfunc(x, (*f)));
    }

    return x;
}


int main(int argc, char **argv)
{
    double x = atof(argv[1]);
    double f1 = func(x), df1 = dfunc(x, func);
    double root = recursiveNewtonRapson(func, x);
    printf("Root of function %f \n", root);
    printf("At x = %f, function value %f and differentiate at %f \n", x, f1, df1);
}
