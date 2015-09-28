#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 10

char *strcat (char first_str[], const char second_str[]);
unsigned long long strlen (const char str[]);
char *strstr (const char first_str[], const char second_str[]);

int main()
{
    char first_s[SIZE];
    char second_s[SIZE];

    gets (first_s);
    gets (second_s);

    //printf ("%s",   strcat (first_s, second_s));

    printf ("First entry = %d", strstr(first_s, second_s) != NULL ? strstr(first_s, second_s) - first_s + 1 : -1);

    return 0;
}

char *strstr (const char first_str[], const char second_str[])
{
    int i = 0, j = 0;
    unsigned long long stop = strlen (second_str) - 1;
    char *enter = &first_str[0];

    while (first_str[i] != '\0')
    {
        if (first_str[i] != second_str[j])
        {
            j = -1;
            enter = &first_str[i+1];
        }
        if (j == stop)
            return enter;

        ++i;
        ++j;
    }

    return NULL;
}

unsigned long long strlen (const char str[])
{
    assert (str);

    unsigned long long counter = 0;

    while (*str++ != '\0')
        ++counter;

    return counter;
}

char *strcat (char *first_str, const char *second_str)
{
    assert (first_str);
    assert (second_str);

    char *str_begin = first_str;

    while (*first_str)
        ++first_str;
    while (*second_str)
        *first_str++ = *second_str++;
    *first_str = '\0';

    return str_begin;
}


