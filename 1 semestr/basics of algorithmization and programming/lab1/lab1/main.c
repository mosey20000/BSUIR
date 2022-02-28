#include <stdio.h>
#include <math.h>

int main() {
    double x,y,z,sum,a,b,c;
    
    printf("Enter: \n");
    scanf("%lf%lf%lf", &x,&y,&z);
    a = log ( pow (y,-1*sqrt(fabs(x))));
       b = (x-y/2);
       c = pow(sin(atan(z)),2);
    sum = (a*b+c);
    printf("Result: %9.3lf\n", sum);
    return 0;
}
