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
 * \retval 0  String was ouput succesfully.
 * \retval -1 String could not be output.
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
 * \brief Prints a given 
 */
int lex_log(char *msg, FILE*);

/**
 * \brief Wrapper around fopen() that displays errors.
 *
 * Tries to open a file. If the file opens succesfully, returns a FILE pointer. 
 * Otherwise, outputs an error message to stderr and returns NULL.
 */
FILE *fopen_err(char *file, char *mode);

int dump_token_to_file(char *file, int tok);
int dump_string_to_file(char *file_name, YYSTYPE val);
int dump_num_to_file(char *file_name, YYSTYPE val);
int dump_id_to_file(char *file_name, YYSTYPE val);

/**
 * \brief Writes a given string to the end of the file.
 *
 * Writes a given string to the end of the file. On success returns 0. 
 * Otherwise outputs an error message to stderr and returns a value different from 0.
 */
int dump_to_file(char *file_name, char *str);

#endif
