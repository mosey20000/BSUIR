#include <math.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
    double x,y,f,e;
    int k;
      printf("Enter X: \n");
      scanf("%lf", &x);
      printf("Enter Y: \n");
      scanf("%lf", &y);
      printf("Choose function 1-sh(x),2-x^2,3–exp(x)\n");
      scanf("%d", &k);
    switch(k){
            
        case 1:
            f=sinh(x);
            printf("Chosen f=sh(x)\n");
            break;
        
        case 2:
            f=pow(x,2);
            printf("Chosen f=x^2\n");
            break;
        
        case 3:
            f=exp(x);
            printf("Chosen f=exp(x)\n");
            break;
        
        default:
            printf("Error\n");
           // a=0;
            return 0;
            break;
    }
    if
        ((x - fabs(y)) > 0)
        e = y*sqrt(f)+3*sin(x);
    
        else
            
    if
        ((x - fabs(y)) < 0)
        e = x * sqrt(fabs(f));
        else
            
            e = pow((fabs(f) + (pow(x,3)/y)),1.0/3.0);
        printf("Result : %lf\n", e);
        return 0;
    }

