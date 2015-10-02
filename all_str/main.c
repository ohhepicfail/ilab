#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <errno.h>

#define SIZE 10
#define MAXFORUL 4294967295
#define DIGIT (double) (*str - '0')
#define GOOD_SYMBOL ('0' <= *str && *str <= '9' || *str == '.' || *str == 'e' || *str == 'E')
#define PEND_INITIALIZATION if (*str != '\0') \
                                *pend = str; \
                            else \
                                *pend = NULL;
#define MAX_POWER 305

char *strcat (char first_str[], const char second_str[]);
unsigned long long strlen (const char str[]);
char *strstr (const char first_str[], const char second_str[]);
double my_strtod (const char str[], char **pend);

int main()
{
    char first_s[SIZE];
    char second_s[SIZE];
    char *p;
    double from_my_strtod;

    gets (first_s);
    //gets (second_s);

    //printf ("%s",   strcat (first_s, second_s));

    //printf ("First entry = %d", strstr(first_s, second_s) != NULL ? strstr(first_s, second_s) - first_s + 1 : -1);

    errno = 0;

    from_my_strtod = my_strtod (first_s, &p);

    if (errno == 0)
        printf ("%lg\n", from_my_strtod);
    else
    {
        if (errno == -1)
            printf ("ERROR: There is no number\n");
        else if (errno == -2)
            printf ("ERROR: Too large power\n");
        else if (errno == -3)
            printf ("ERROR: No numbers after 'e'\n");
    }

    if (p != NULL)
        printf ("%c\n", *p);
    else
        printf ("pointer is NULL\n");

    return 0;
}

char *strstr (const char first_str[], const char second_str[])
{
    assert (first_str);
    assert (second_str);

    int i = 0, j = 0;
    unsigned long long stop = strlen (second_str) - 1;
    char *enter = &first_str[0];

    while (first_str[i] != '\0')
    {
        assert (first_str[i]);

        if (first_str[i] != second_str[j])
        {
            j = -1;
            enter = &first_str[i+1];
            assert (enter);
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

char *strcat (char first_str[], const char second_str[])
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

double my_strtod (const char str[], char **pend)
{
    assert (str);

    double result = 0;
    int sign = 1;
    int after_dot = 0;
    int power;

    while (*str == '\t' || *str == ' ' || *str == '\n')
    {
        str++;
        assert (*str);
    }

    if (*str == '-')
    {
        sign = -1;
        ++str;
        assert (*str);
    }

    else if (*str == '+')
    {
        ++str;
        assert (*str);
    }

    if (!GOOD_SYMBOL)
    {
        errno = -1;
        return 0;
    }

    while (GOOD_SYMBOL)
    {

        assert (*str);

        switch (*str)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if (after_dot > 0)
            {
                result += sign * DIGIT / after_dot;
                after_dot *= 10;
            }
            else
                result = result * 10 + sign * DIGIT;

            break;
        case '.':
            if (after_dot == 0)
                after_dot = 10;
            else
            {
                PEND_INITIALIZATION
                return result;
            }

            break;
        case 'e':
        case 'E':

            ++str;

            if (*str == '\0')
            {
                errno = -3;
                *pend = NULL;
                return 0;
            }

            if (*str == '-')
            {
                sign = -1;
                ++str;
            }
            else if (*str == '+')
            {
                sign = 1;
                ++str;
            }
            else
                sign = 1;

            power = DIGIT;

            if (*str == '\0')
            {
                errno = -3;
                *pend = NULL;
                return 0;
            }

            ++str;

            while ('0' <= *str && *str <= '9')
            {
                power = power * 10 + DIGIT;
                ++str;
                assert (*str || *str == '\0');
            }

            PEND_INITIALIZATION

            power *= sign;

            if (abs (power) > MAX_POWER)
            {
                errno = -2;
                return 0;
            }

            result *= pow (10, power);

            return result;
            break;
        }

        ++str;
    }

    PEND_INITIALIZATION

    return result;

}

