#include <stdlib.h>
#include <math.h>
#include <stdio.h>

int main()
{
    int **a;
    int i,j,n,m,sum;
    
    sum=0;
    
    printf("Enter size of array NxM\n");
    scanf("%d%d",&n,&m);
    
    a = (int**) malloc (n *sizeof(int*));
    for (i=0; i<n; i++)
    {
        a[i] = (int*) malloc (m *sizeof(int));
    }
    
    for ( i = 0; i < n; ++i )
    {
        for ( j = 0; j < m; ++j )
        {
            a[i][j] = rand()%50;
        }
    }
    
    for (j=1; j<n; j++)
    {
        for (i=1; i<m; i++)
        {
            if ((a[i][j-1] < a[i][j]) && (a[i][j]<a[i][j+1]))
                sum++;
        }
    }

    for (i=0; i<n; i++)
    {
        for (j=0; j<m; j++)
            printf("%d  ",a[i][j]);
            printf ("\n");
    }
    printf("%d\n",sum);
    
    for (int i=0; i<n; i++)
    {
        free(a[i]);
    }
    
    free(a);
    
    return 0;
}
