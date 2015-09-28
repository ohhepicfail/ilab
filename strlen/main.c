#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

unsigned long long strlen (const char str[]);

int main ()
{
    char *str;

    gets (str);

    printf ("size str = %llu\n", strlen(str));

    return 0;
}

unsigned long long strlen (const char str[])
{
    assert (str);

    unsigned long long counter = 0;

    while (*str++ != '\0')
    {
        ++counter;
    }

    return counter;
}
