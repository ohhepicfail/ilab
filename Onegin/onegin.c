#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include "onegin.h"


size_t get_size (const char *filename)
{
    setlocale (0, "");

    assert (filename);

    FILE *file = fopen (filename, "rb");

    if (!file)
    {
        errno = -1;
        return 1;
    }

    size_t size = 0;
    char *text = NULL;

    fseek (file, 0, SEEK_END);
    assert (file);
    size = ftell (file);

    text = (char *) calloc (size, sizeof (char));

    fseek (file, 0, SEEK_SET);
    assert (file);

    fread (text, size, 1, file);
    assert (text);

    fclose (file);
    return size;
}


int fread_file (char *text, const size_t text_size, const char *filename)
{
    setlocale (0, "");

    assert (text);
    assert (filename);

    FILE *text_stream = fopen (filename, "rb");

    if (!text_stream)
    {
        errno = -1;
        return 1;
    }

    size_t size = fread ((char *) text, sizeof (char), text_size, text_stream);
    assert (text);
    assert (size > 0);

    fclose (text_stream);

    return size;
}

size_t count_lines (const char *text)
{
    if (!text)
    {
        errno = -2;
        return 2;
    }

    size_t counter = 1;
    while (*text)
    {
        if (*text == '\n')
            ++counter;

        ++text;
    }
    return counter;
}

int split_strings (const char *text, char **strings)
{
    if (!text)
    {
        errno = -2;
        return 2;
    }
    else if (!strings)
    {
        errno = -3;
        return 3;
    }

    char * str = strtok (text, "\n");
    int i = 0;

    while (str)
    {
        strings[i] = str;
        str = strtok (NULL, "\n");
        i++;
    }
    i--;
    strings[i][strlen (strings[i])-1] = strings[i-1][strlen (strings[i-1])-1];

    return 0;
}

int print_in_file (char *filename, const char **strings, const size_t strings_number)
{
    assert (filename);
    assert (strings);

    FILE *f = fopen (filename, "w");

    if (!f)
        return 1;

    int i = 0;
    for (i = 0; i < strings_number; i++)
        fprintf (f, "%s", strings[i]);

    close (f);

    return 0;
}

int count_len (const char **strings, size_t strings_number, size_t *strings_len)
{
    assert (strings);
    assert (strings_number > 0);
    assert (strings_len);

    strings_number--;

    while (1)
    {
        unsigned counter = 0;
        while (*strings[strings_number] != '\0')
        {
            strings_len[strings_number]++;
            strings[strings_number]++;
            counter++;
        }

        strings[strings_number] -= counter;

        if (strings_number > 0)
            strings_number--;
        else
            return 0;
    }
}
