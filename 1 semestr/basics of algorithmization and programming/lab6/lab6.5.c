#include <stdio.h>
#define MAXLEN 10000


int getl(char *str)
{
    int len = 0;
    char c;
    while ( (c = getchar()) != EOF && len < MAXLEN)
    {
        if (c == '\n')
            break;
        *str++ = c;
        len++;
    }
    *str = '\0';
    return len;
}


int main()
{

    char str[MAXLEN];
    int len = getl(str);
    int count_1 = 0;
    int total = 0;
    int len_1 = 0;

    str[len++] = ' ';
    str[len++] = '2';

    for (int i=0; i < len + 2; i++)
    {
        if (str[i] == '1')
        {
            count_1++;
            len_1++;
        }
        if (str[i] == '0')
        {
            len_1++;
        }
        if (str[i] == ' ')
        {
           len--;
           if (len_1 % 2 == 1)
           {
               total = total + count_1;
               len_1 = 0;
               count_1 = 0;
           }
           else
           {
               count_1 = 0;
               len_1 = 0;
           }
        }
    }

    printf("Total = %d\n",total);
}