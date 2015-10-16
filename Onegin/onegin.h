#ifndef ONEGIN_H_INCLUDED
#define ONEGIN_H_INCLUDED

/*!
 * @file onegin.h
 * @brief module that contains all functions to work with text
 * @author Sidorenko Anton
 */

size_t get_size (const char *filename);
/*!
* @fn size_t get_size (const char *filename)
* @brief Getting size of the text
* @warning You can set zero in errno and running the function to check that file opens with no errors. If errno = -1 it's mean, that file can't be opened.
* @warning File must be in directory with program
* @param Name of file
* @return Text size
*/

int fread_file (char *text, const size_t text_size, const char *filename);
/*!
* @fn int fread_file (char *text, const size_t text_size, const char *filename);
* @brief Read all text using fread()
* @warning You can set zero in errno and running the function to check that file opens with no errors. If errno = -1 it's mean, that file can't be opened
* @warning File must be in directory with program
* @param Pointer to a block of memory, text size from correct_text_size, name of file
* @return Size of the file
*/

size_t count_lines (const char *text);
/*!
* @fn size_t count_lines (const char *text)
* @brief Counting lines in text
* @warning You can set zero in errno and running the function to check that file opens with no errors. If errno = -2 it's mean, that file is empty
* @param Pointer on the text
* @return Number of lines
*/

int split_strings (const char *text, char **strings);
/*!
* @fn int split_strings (const char *text, char **strings)
* @brief Divides the text on the lines
* @param Pointer on the text, array of strings
* @return Zero if no errors
*/

int print_in_file (char *filename, const char **strings, const size_t strings_number);
/*!
* @fn int print_in_file (char *filename, const char **strings, const size_t strings_number)
* @brief print text into a file with name "filename"
* @param name of the file, pointer on the strings array, number of strings
* @return Zero if no errors, and 1 of function cannot open the file
*/

int count_len (const char **strings, size_t strings_number, size_t *strings_len);
/*!
* @fn int count_len (const char **strings, size_t strings_number, size_t *strings_len)
* @brief Count len of the strings that stored in array of strings
* @param array of strings, number of strings, array to write the len
* @return Zero if no errors
*/

#endif // ONEGIN_H_INCLUDED
