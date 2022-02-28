#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int main()
{
    int *a;
    int n;
    
    printf("Enter size of array");
    scanf("%d",&n);
    a = (int*) malloc (n *sizeof(int));
    for (int i=0; i<n; i++)
    {
        printf("Enter a[%d] ",i);
        scanf("%d", &a[i]);
    }
    for (int i = 0;i < n; i++){
      for (int j = i+1; j < n; j++){
          if(a[i] == a[j]) printf("%d\n",a[i]);
      }
    }
    free(a);
    return 0;
}
