#include <stdio.h>
#include <math.h>

#define DBL_EPSILON 0.000000000000001e-16

int sqr_solver (double a, double b, double c, double *x1, double *x2)
{
    int number_decisions;
    double discriminant;

    if (fabs (a) <= DBL_EPSILON)
    {
        *x1 = -c / b;

        number_decisions = 1;
    }
    else if (fabs (b) <= DBL_EPSILON)
    {
        if ((c <= DBL_EPSILON) || (a <= DBL_EPSILON))
        {
            *x1 = sqrt (-c / a);
            *x2 = -*x1;

            number_decisions = 2;
        }
        else
            number_decisions = 0;
    }
    else if (fabs (c) <= DBL_EPSILON)
    {
        *x1 = 0.0;
        *x2 = -b / a;

        number_decisions = 2;
    }
    else
    {
        discriminant = b*b - 4*a*c;

        if (discriminant >= DBL_EPSILON)
        {
            *x1 = (-b + sqrt (discriminant)) / (2*a);
            *x2 = (-b - sqrt (discriminant)) / (2*a);

            number_decisions = 2;
        }
        else if ( fabs (discriminant) <= DBL_EPSILON)
        {
            *x1 = -b / (2*a);

            number_decisions = 1;
        }
        else
            number_decisions = 0;

    }

    return number_decisions;
}
