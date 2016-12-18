#ifndef TIGER_LEX_ANALYSIS_UTILS_H
#define TIGER_LEX_ANALYSIS_UTILS_H

#include <stdio.h>

#include "scanner_utils.h"

/**
 * \brief Outputs an error message to stderr.
 *
 * Outputs an error message to stderr. The resulting string's format is 
 * defined inside the function.
 *
 * \param[in] msg The memory to be output.
 * \retval 0  String was printed succesfully.
 * \retval -1 String could not be printed.
 */
int lex_error(char *msg);

/**
 * \brief Outpus an error message prodcued because of a bad token found in the
 * scanned file.
 *
 * Outputs an error message about a bad token that occurs in the scanned file.
 * The message contains the token starting position. The message is written to
 * stderr.
 *
 * \param[in] explanation String that is appended to the error message.
 * \param[in] line_num  Number of line in the file on which the bad token 
 *            was found
 * \param[in] char_pos  Position of the bad token in the line on which it was
 *            found.
 *
 * \returns 0 if the error has been succesfully output. Other value in case of
 *            an error.
 */
int lex_token_error(char *explanation, int line_num, int char_pos);

/**
 * \brief Prints a message to the opened file.
 *
 * Prints a given message to the opened file.
 *
 * \param[in] msg A message to be printed.
 * \param[in] f   A pointer to the destination file.
 *
 * \returns 0   If message was printed succesfully; -1 otherwise.
 */
int lex_log(char *msg, FILE*);

/**
 * \brief Wrapper around fopen() that displays errors.
 *
 * Tries to open a file. If the file opens succesfully, returns a FILE pointer. 
 * Otherwise, outputs an error message to stderr and returns NULL.
 *
 * \param[in] file  Name of file to open.
 * \param[in] mode  File open mode.
 *
 * \returns If file opens succesfully a pointer to FILE structure. Otherwise, 
 * an error message is printed to stderr and NULL is returned.
 */
FILE *fopen_err(char *file, char *mode);

/**
 * \brief Returns a string composed by insertion of a string into a given 
 * template.
 *
 * A wrapper around sprintf function. Returns a newly allocated string 
 * composed by inserting a given string into a provided template.
 *
 * \param[in] result_template A template that contains a singles %s token.
 * \param[in] str String that will be inserted into the %s token position.
 *
 * \returns Pointer to a newly allocated string. If an error occurred returns
 * a NULL pointer.
 */
char *insert_into_string(char *result_template, char *str);

#endif
