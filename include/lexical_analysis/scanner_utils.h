#ifndef TIGER_LEX_ANALYSIS_SCANNER_UTILS_H
#define TIGER_LEX_ANALYSIS_SCANNER_UTILS_H

/**
 * \union YYSTYPE include/lexical_analysis/tokens.h
 * \brief YYSTYPE declaration used by (F)LEX.
 * 
 * YYSTYPE is the type of yylval variable in which the token value is stored
 */
typedef union {
  int pos;
  int ival;
  char *sval;
} YYSTYPE;

/** \brief Variable to store value of the processed token */
YYSTYPE yylval;



/**
 * \brief Writes a given string to the end of the file.
 *
 * Writes a given string to the end of the file.
 *
 * \param[in] file_name Destination file.
 * \param[in] str String to be written.
 *
 * \returns On success returns 0. Otherwise outputs an error message to stderr
 * and returns a value different from 0.
 */
int dump_to_file(char *file_name, char *str);

/**
 *
 */
int dump_token_to_file(char *file, int tok);
int dump_string_to_file(char *file_name, YYSTYPE val);
int dump_num_to_file(char *file_name, YYSTYPE val);
int dump_id_to_file(char *file_name, YYSTYPE val);
#endif
