#ifndef TIGER_LEX_ANALYSIS_UTILS_H
#define TIGER_LEX_ANALYSIS_UTILS_H

#include <stdio.h>

int lex_error(char *msg);
int lex_token_error(char *msg_template, int line_num, int char_pos);
int lex_log(char *msg, FILE*);

/**
 * \brief Wrapper around fopen() that displays errors.
 *
 * Tries to open a file. If the file opens succesfully, returns a FILE pointer. 
 * Otherwise, outputs an error message to stderr and returns NULL.
 */
FILE *fopen_err(char *file, char *mode);

int dump_token_to_file(char *file, int tok);

/**
 * \brief Writes a given string to the end of the file.
 *
 * Writes a given string to the end of the file. On success returns 0. 
 * Otherwise outputs an error message to stderr and returns a value different from 0.
 */
int dump_to_file(char *file_name, char *str);

#endif
