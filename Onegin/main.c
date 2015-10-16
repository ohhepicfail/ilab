#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include "onegin.h"

struct Strings_t
{
    char **lines;
    size_t *len;
    size_t number;
};

int cmp_rhy (const void *first, const void *second);
int cmp_ruch (char ch1, char ch2);
int cmp_ench (char ch1, char ch2);
int cmp_enc (const void *first, const void *second);

int main()
{
    char *filename = "original.txt";
    char *text = NULL;
    size_t strings_number = 0;
    char **strings = NULL;
    char **str_encyclopedia = NULL;

    struct Strings_t original_str;
    struct Strings_t encyclopedia_str;
    struct Strings_t rhyme_str;

    errno = 0;
    size_t text_size = get_size (filename);

    if (errno == -1)
    {
        printf ("ERROR: Could not open file in get_size()");
        return 1;
    }

    text = (char *) calloc (text_size, sizeof (char));
    if (!text)
        printf ("ERROR: out of memory");

    errno = 0;
    fread_file (text, text_size, filename);
    if (errno == -1)
    {
        printf ("ERROR: Could not open file in fread_file()");
        return 1;
    }

    errno = 0;
    original_str.number = count_lines (text);
    if (errno == -2)
    {
        printf ("ERROR: text is empty");
        return 2;
    }

    original_str.lines = (char **) calloc (original_str.number, sizeof(char *));

    errno = 0;
    split_strings (text, original_str.lines);
    switch (errno)
    {
    case -2:
        printf ("ERROR: text is empty");
        return 2;

    case -3:
        printf ("ERROR: strings is NULL");
        return 3;

    default:
        break;
    }

    encyclopedia_str.lines = (char **) calloc (original_str.number, sizeof (char *));
    encyclopedia_str.number = original_str.number;
    memmove (encyclopedia_str.lines, original_str.lines, sizeof (char *) * encyclopedia_str.number);
    qsort (encyclopedia_str.lines, encyclopedia_str.number, sizeof (char *), cmp_enc);

    if (print_in_file ("encyclopedia.txt", encyclopedia_str.lines, encyclopedia_str.number) != 0)
    {
        printf ("ERROR: cannot write in file encyclopedia.txt");
        return 1;
    }

    free (encyclopedia_str.lines);

    rhyme_str.number = original_str.number;
    rhyme_str.lines = (char **) calloc (rhyme_str.number, sizeof (char *));
    memmove (rhyme_str.lines, original_str.lines, sizeof (char *) * rhyme_str.number);
    rhyme_str.len = (size_t *) calloc (rhyme_str.number, sizeof (size_t *));

    if (count_len (rhyme_str.lines, rhyme_str.number, rhyme_str.len) != 0)
    {
        printf ("ERROR: cannot count strings len");
        return 4;
    }

    qsort (rhyme_str.lines, rhyme_str.number, sizeof (char *), cmp_rhy);

    if (print_in_file ("rhyme.txt", rhyme_str.lines, rhyme_str.number) != 0)
    {
        printf ("ERROR: cannot write in file encyclopedia.txt");
        return 1;
    }

    free (original_str.lines);
    free (rhyme_str.lines);
    free (rhyme_str.len);
    free (text);

    return 0;
}

int cmp_rhy (const void *first, const void *second)
{
    assert (first);
    assert (second);

    char* line1 = *(char**)first;
    char* line2 = *(char**)second;
    line1 = &line1[strlen (line1) -1];
    line2 = &line2[strlen (line2) -1];

    while (*line1 && *line2)
    {
        if (*line1 >= 0 && *line2 >= 0)
        {
            if (cmp_ench(*line1, *line2))
                return cmp_ench (*line1, *line2);
        }
        else if (*line1 < 0 && *line2 < 0)
        {
            if (cmp_ruch(*line1, *line2))
                return cmp_ruch (*line1, *line2);
        }
        else if (*line1 > 0)
            return -1;
        else
            return 1;

        line1--;
        line2--;
    }

    return 0;
}

int cmp_ench (char ch1, char ch2)
{
    assert (ch1 >= 0);
    assert (ch2 >= 0);

    if (ch1 > ch2)
        return 1;
    else if (ch1 < ch2)
        return -1;
    else
        return 0;
}

int cmp_ruch (char ch1, char ch2)
{
    return cmp_ench (ch1 - 2 * ch1, ch2 - 2 * ch2);
}

int cmp_enc (const void *first, const void *second)
{
    assert (first);
    assert (second);

    return strcmp (*(char **)first, *(char **)second);
}


