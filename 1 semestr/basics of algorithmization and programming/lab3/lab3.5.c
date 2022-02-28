#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double a = 0.1 , b = 1 , x ,y , s , h, fact;
    int i = 0, n = 140;
    h = (b-a)/10;

    for (x=a; x<=b + (h/2); x+=h)
    {
        s=fact=1;
        for (int i=1; i<=n; i++)
        {
            fact = fact * i;
            s=s + (2*i+1)/fact * pow(x,2*i);
        }
        y = (1+2*pow(x,2))*exp(pow(x,2));

        printf("Result x = %10lf   Result y = %10lf   Result s = %10lf  Result |S(x)-f(y)| = %10lf\n " , x , y , s, fabs(s-y));
    }
    return 0;
}