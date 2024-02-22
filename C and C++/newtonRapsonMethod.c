
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define PRECISION 0.000001


// Predifed function
double func(double x)
{
    // return (x * x * x) - (2 * x) + 2;
    return 1 / x;
    // return (x * x * x) - (3 * x * x) + 2;
    // return 1 - (x * x);
    // return pow(x, 0.3333333333);
}


// find the differentiation of any function passed
double dfunc(double x, double (*f)(double))
{
    double dx = 0.00000001;
    double dy1 = (*f)(x + (dx / 2));
    double dy2 = (*f)(x - (dx / 2));
    return (dy1 - dy2) / dx;
}


double newtonRapson(double (*f)(double), double x)
{
    double root = x, dx = 1.0, fVal = 0.0, dfVal = 0.0;

    while(fabs(dx) > 0)
    {
        fVal = (*f)(root);
        dfVal = dfunc(root, (*f));

        if(fabs(fVal) < 0 | fabs(dfVal) < 0)
            break;
        
        dx = fVal / dfVal;

        printf("At x = %f, dx = %f ; function value = %f and slope = %f \n", x, dx, fVal, dfVal);
        
        root -= dx;
    }

    return root;
}


int main(int argc, char **argv)
{
    double x = atof(argv[1]);
    double f1 = func(x), df1 = dfunc(x, func);
    double root = newtonRapson(func, x);
    printf("Root of function %f \n", root);
    printf("At x = %f, function value = %f and slope = %f \n", x, f1, df1);
}
