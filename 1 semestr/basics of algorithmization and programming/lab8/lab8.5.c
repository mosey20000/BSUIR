#include <stdio.h>
#include <math.h>


double y(double x)
{
    return (1+2*x*x)*exp(x*x);
}


double s(double x, double y, int *k)
{
    double r = 1;
    double sum = 1;
    for ((*k) = 1; fabs(fabs(sum) - fabs(y)) >= 0.001; (*k)++)
    {
        r *= 1./(*k)*x*x;
        sum += r * (2*(*k)+1);
    }
    *(k)--;
    return sum;
}


int main()
{
    double a,b;
    double e;
    scanf("%lf%lf", &a, &b);

    for(double i = a; i <= b; i += 0.1)
    {
        int k;
        printf("%lf\t%lf\t%lf\t%d\n", i, y(i), s(i, y(i), &k), k);
    }
    return 0;
}
